#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

#include <zmk/activity.h>
#include <zmk/endpoints.h>
#include <zmk/events/activity_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/hid_indicators_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/keymap.h>
#include <zmk/usb.h>
#include <zmk/workqueue.h>

#include <stdlib.h>

#include <color-effect.h>

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_EXT_POWER)
#include <drivers/ext_power.h>
#endif

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_CHOSEN(zmk_underglow)
#error "zmk,underglow is incompatible with zmk,light-group"
#endif

BUILD_ASSERT(DT_NODE_EXISTS(DT_PATH(ledlayout)), "ledlayout not found for LIGHT_GROUP");

#define STRIP_CHOSEN     DT_CHOSEN(zmk_light_group)
#define STRIP_NUM_PIXELS DT_PROP_LEN(DT_PATH(ledlayout), bindings)

#define BINDINGS_ARRAY_AND_COMMA(node)                                                             \
    COND_CODE_1(DT_NODE_HAS_PROP(node, bindings), (DT_PROP(node, bindings)), ({})),

static const uint8_t ledlayout[STRIP_NUM_PIXELS] = DT_PROP(DT_PATH(ledlayout), bindings);
static const uint8_t lightgroup[ZMK_KEYMAP_LAYERS_LEN][STRIP_NUM_PIXELS] = {
    DT_FOREACH_CHILD(DT_PATH(lightgroup), BINDINGS_ARRAY_AND_COMMA)};

static uint8_t updated_groups = LG_ALL;
static bool light_group_enabled = true;

#define DT_PHA_BY_IDX_HSV(node_id, pha, idx) {.raw = DT_PHA_BY_IDX(node_id, pha, idx, hsv)}

#define DEFINE_COLOR_GROUP(name, min_len)                                                          \
    BUILD_ASSERT(DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors) >= min_len,                     \
                 "colorgroup/" #name "s must have at least " #min_len " colors");                  \
    static const uint8_t name##_num = DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors);           \
    static const hsv_t name[DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors)] = {                 \
        DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, name##s), colors, DT_PHA_BY_IDX_HSV, (,)) };      \
    uint8_t name##_value = 0;

DEFINE_COLOR_GROUP(background, 1)
DEFINE_COLOR_GROUP(battery, 2)
DEFINE_COLOR_GROUP(desktop, 1)
DEFINE_COLOR_GROUP(endpoint, 1)
DEFINE_COLOR_GROUP(hid, 2)
DEFINE_COLOR_GROUP(layer, 1)
DEFINE_COLOR_GROUP(profile, 2)
DEFINE_COLOR_GROUP(volume, 2)

static const struct device *led_strip;
#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_EXT_POWER)
static const struct device *const ext_power = DEVICE_DT_GET(DT_INST(0, zmk_ext_power_generic));
#endif

static struct led_rgb pixels[STRIP_NUM_PIXELS];

static struct pixel_state state[STRIP_NUM_PIXELS];

/*
 * Work loop:
 *
 * Put light_group_tick_work onto the lowprio_work queue when the timer
 * ticks. Defined here, so it can be referenced by both the ext_power routines
 * (that can disable the timer) and the main init routine at the end of this
 * file.
 */
static void zmk_light_group_tick(struct k_work *work);

K_WORK_DEFINE(light_group_tick_work, zmk_light_group_tick);

static void zmk_light_group_tick_handler(struct k_timer *timer)
{
    if (!light_group_enabled) {
        return;
    }

    k_work_submit_to_queue(zmk_workqueue_lowprio_work_q(), &light_group_tick_work);
}

K_TIMER_DEFINE(light_group_tick, zmk_light_group_tick_handler, 0);

/*
 * Shell commands
 *
 * Only the desktop and battery endpoints really make sense. These must be fed
 * from the machine we are connecting to. The rest of the endpoints are here for
 * completion and to allow debugging of different groups via serial.
 */
static int cmd_battery(const struct shell *sh, size_t argc, char **argv)
{
    battery_value = atoi(argv[1]);
    updated_groups |= (1 << LG_BATTERY);

    return 0;
}

static int cmd_desktop(const struct shell *sh, size_t argc, char **argv)
{
    desktop_value = atoi(argv[1]);
    updated_groups |= (1 << LG_DESKTOP);

    return 0;
}

static int cmd_endpoint(const struct shell *sh, size_t argc, char **argv)
{
    endpoint_value = atoi(argv[1]);
    updated_groups |= (1 << LG_ENDPOINT);

    return 0;
}

static int cmd_hid(const struct shell *sh, size_t argc, char **argv)
{
    hid_value = atoi(argv[1]);
    updated_groups |= (1 << LG_HID);

    return 0;
}

static int cmd_layer(const struct shell *sh, size_t argc, char **argv)
{
    layer_value = atoi(argv[1]);
    updated_groups |= (1 << LG_LAYER);

    return 0;
}

static int cmd_profile(const struct shell *sh, size_t argc, char **argv)
{
    profile_value = atoi(argv[1]);
    updated_groups |= (1 << LG_PROFILE);

    return 0;
}

static int cmd_volume(const struct shell *sh, size_t argc, char **argv)
{
    volume_value = atoi(argv[1]);
    updated_groups |= (1 << LG_VOLUME);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_lightgroup, SHELL_CMD_ARG(battery, NULL, "Set battery value", cmd_battery, 2, 0),
    SHELL_CMD_ARG(desktop, NULL, "Set desktop value", cmd_desktop, 2, 0),
    SHELL_CMD_ARG(endpoint, NULL, "Set endpoint value", cmd_endpoint, 2, 0),
    SHELL_CMD_ARG(hid, NULL, "Set hid value", cmd_hid, 2, 0),
    SHELL_CMD_ARG(layer, NULL, "Set layer value", cmd_layer, 2, 0),
    SHELL_CMD_ARG(profile, NULL, "Set profile value", cmd_profile, 2, 0),
    SHELL_CMD_ARG(volume, 0, "Set volume value", cmd_volume, 2, 0), SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(lightgroup, &sub_lightgroup, "Light group values", NULL);

/*
 * ZMK Event handlers
 *
 * Some of the light groups are showing zmk state, these handlers are listening
 * for battery / endpoint / layer / hid indicator / ble profile changes.
 */
static int handle_battery_change(const zmk_event_t *eh)
{
    const struct zmk_battery_state_changed *ev = (const struct zmk_battery_state_changed *)eh;
    if (ev->state_of_charge != battery_value) {
        /* Called with the computed state of charge in a percentage */
        battery_value = ev->state_of_charge;
        updated_groups |= (1 << LG_BATTERY);
    }
    return 0;
}

ZMK_LISTENER(light_group_battery, handle_battery_change);
ZMK_SUBSCRIPTION(light_group_battery, zmk_battery_state_changed);

static int handle_endpoint_change(const zmk_event_t *eh)
{
    const struct zmk_endpoint_changed_event *ev = (const struct zmk_endpoint_changed_event *)eh;
    uint8_t new_endpoint = zmk_endpoint_instance_to_index(ev->data.endpoint);
    if (new_endpoint != endpoint_value) {
        /* ENDPOINT_USB = 0 and ENDPOINT_BLE = [1..n], depending on current BLE profile */
        endpoint_value = new_endpoint;
        updated_groups |= (1 << LG_ENDPOINT);
    }
    return 0;
}

ZMK_LISTENER(light_group_endpoint, handle_endpoint_change);
ZMK_SUBSCRIPTION(light_group_endpoint, zmk_endpoint_changed);

static int handle_layer_change(const zmk_event_t *eh)
{
    const struct zmk_layer_state_changed_event *ev =
        (const struct zmk_layer_state_changed_event *)eh;
    if (ev->data.state && ev->data.layer != layer_value) {
        layer_value = ev->data.layer;
        updated_groups |= (1 << LG_LAYER);
    }
    return 0;
}

ZMK_LISTENER(light_group_layer, handle_layer_change);
ZMK_SUBSCRIPTION(light_group_layer, zmk_layer_state_changed);

static int handle_hid_change(const zmk_event_t *eh)
{
    const struct zmk_hid_indicators_changed *ev = (const struct zmk_hid_indicators_changed *)eh;
    if (ev->indicators != hid_value) {
        /* Indicators is an uint8_t with the HID indicators as per the standard report */
        hid_value = ev->indicators;
        updated_groups |= (1 << LG_HID);
    }
    return 0;
}

ZMK_LISTENER(light_group_hid, handle_hid_change);
ZMK_SUBSCRIPTION(light_group_hid, zmk_hid_indicators_changed);

static int handle_ble_profile_change(const zmk_event_t *eh)
{
    uint8_t profile = zmk_ble_active_profile_index();
    if (profile != profile_value) {
        /* Index into the ble profile array */
        profile_value = profile;
        updated_groups |= (1 << LG_PROFILE);
    }
    return 0;
}

ZMK_LISTENER(light_group_profile, handle_ble_profile_change);
ZMK_SUBSCRIPTION(light_group_profile, zmk_ble_active_profile_changed);

/*
 * Many leds = many milli amps of current draw. Make sure we can react to:
 *
 * - ext power disabling
 * - usb connection (yay), and disconnection (boo!)
 * - the keyboard being idle
 */
int zmk_light_group_on(void)
{
    if (!led_strip) {
        return -ENODEV;
    }

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_EXT_POWER)
    if (ext_power != NULL) {
        int rc = ext_power_enable(ext_power);
        if (rc != 0) {
            LOG_ERR("Unable to enable EXT_POWER: %d", rc);
        }
    }
#endif

    light_group_enabled = true;
    k_timer_start(&light_group_tick, K_NO_WAIT, K_MSEC(50));
    return 0;
}

static void zmk_light_group_off_handler(struct k_work *work)
{
    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        pixels[i] = (struct led_rgb){.r = 0, .g = 0, .b = 0};
    }
    led_strip_update_rgb(led_strip, pixels, STRIP_NUM_PIXELS);
}

K_WORK_DEFINE(light_group_off_work, zmk_light_group_off_handler);

int zmk_light_group_off(void)
{
    if (!led_strip) {
        return -ENODEV;
    }

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_EXT_POWER)
    if (ext_power != NULL) {
        int rc = ext_power_disable(ext_power);
        if (rc != 0) {
            LOG_ERR("Unable to disable EXT_POWER: %d", rc);
        }
    }
#endif

    light_group_enabled = false;
    k_work_submit_to_queue(zmk_workqueue_lowprio_work_q(), &light_group_off_work);
    k_timer_stop(&light_group_tick);
    return 0;
}

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_USB) ||                                             \
    IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_IDLE)

static int light_group_auto_state(bool target_wake_state)
{
    if (target_wake_state) {
        return zmk_light_group_on();
    } else {
        return zmk_light_group_off();
    }
}

static int handle_light_group_auto_off_events(const zmk_event_t *eh)
{
#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_IDLE)
    if (as_zmk_activity_state_changed(eh)) {
        return light_group_auto_state(zmk_activity_get_state() == ZMK_ACTIVITY_ACTIVE);
    }
#endif

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_USB)
    if (as_zmk_usb_conn_state_changed(eh)) {
        return light_group_auto_state(zmk_usb_is_powered());
    }
#endif
    return 0;
}

ZMK_LISTENER(light_group_auto_off, handle_light_group_auto_off_events);

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_IDLE)
ZMK_SUBSCRIPTION(light_group_auto_off, zmk_activity_state_changed);
#endif

#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_USB)
ZMK_SUBSCRIPTION(light_group_auto_off, zmk_usb_conn_state_changed);
#endif

#endif

/*
 * Light range functions;
 *
 * Map the last parameter (value, percentage) to a range of HSV values, and
 * store the result in the provided pixel_state.
 */
static void light_group_range_select(struct pixel_state *current, const hsv_t *group,
                                     uint8_t group_max, uint8_t value)
{
    value %= group_max;
    pixel_effect_init_hold(current, group[value]);
}

static void light_group_continuous(struct pixel_state *current, const hsv_t *group,
                                   uint8_t group_max, fract8_t percentage)
{
    uint8_t bucket_size = UINT8_MAX / (group_max - 1);
    uint8_t start_index = (percentage / bucket_size);
    fract8_t mix = (uint16_t)(UINT8_MAX * (percentage % bucket_size)) / bucket_size;
    hsv_t target;

    if (start_index == (group_max - 1)) {
        pixel_effect_init_hold(current, group[start_index + 1]);
    } else {
        hsv_transition(group[start_index], group[start_index + 1], mix, &target);
        pixel_effect_init_hold(current, target);
    }
}

static void apply_ledlayout_for_group(uint8_t group)
{
    zmk_keymap_layer_index_t layer_value = zmk_keymap_highest_layer_active();
    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        if ((lightgroup[layer_value][i] != group) && (group != LG_ALL)) {
            /* Current pixel group is not the one we are updating, skip */
            continue;
        }

        struct pixel_state *current = &state[ledlayout[i]];

        switch (lightgroup[layer_value][i]) {
        case LG_BACKGROUND:
            light_group_range_select(current, background, background_num, background_value);
            break;

        case LG_BATTERY:
            light_group_continuous(current, battery, battery_num, battery_value);
            break;

        case LG_DESKTOP:
            light_group_range_select(current, desktop, desktop_num, desktop_value);
            break;

        case LG_ENDPOINT:
            light_group_range_select(current, endpoint, endpoint_num, endpoint_value);
            break;

        case LG_HID:
            light_group_range_select(current, hid, hid_num, hid_value);
            break;

        case LG_LAYER:
            light_group_range_select(current, layer, layer_num, layer_value);
            break;

        case LG_PROFILE:
            light_group_range_select(current, profile, profile_num, profile_value);
            break;

        case LG_VOLUME:
            light_group_continuous(current, volume, volume_num, volume_value);
            break;

        default:
            pixel_effect_init_rainbow(current, i, STRIP_NUM_PIXELS);
            break;
        }
    }
}

static void zmk_light_group_tick(struct k_work *work)
{
    if (updated_groups) {
        if (updated_groups == LG_ALL) {
            apply_ledlayout_for_group(LG_ALL);
            updated_groups = 0;
        }
        if (updated_groups & (1 << LG_BATTERY)) {
            apply_ledlayout_for_group(LG_BATTERY);
        }
        if (updated_groups & (1 << LG_DESKTOP)) {
            apply_ledlayout_for_group(LG_DESKTOP);
        }
        if (updated_groups & (1 << LG_ENDPOINT)) {
            apply_ledlayout_for_group(LG_ENDPOINT);
        }
        if (updated_groups & (1 << LG_HID)) {
            apply_ledlayout_for_group(LG_HID);
        }
        if (updated_groups & (1 << LG_LAYER)) {
            apply_ledlayout_for_group(LG_LAYER);
        }
        if (updated_groups & (1 << LG_PROFILE)) {
            apply_ledlayout_for_group(LG_PROFILE);
        }
        if (updated_groups & (1 << LG_VOLUME)) {
            apply_ledlayout_for_group(LG_VOLUME);
        }
        updated_groups = 0;
    }

    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        switch (state[i].effect) {
        case EFFECT_OFF:
            pixel_effect_off(&state[i], i);
            break;

        case EFFECT_HOLD:
            pixel_effect_hold(&state[i], i);
            break;

        case EFFECT_FLASH:
            pixel_effect_flash(&state[i], i);
            break;

        case EFFECT_RAINBOW:
            pixel_effect_rainbow(&state[i], i);
            break;
        }

        hsv2rgb(&state[i].current, &pixels[i]);
    }

    int err = led_strip_update_rgb(led_strip, pixels, STRIP_NUM_PIXELS);
    if (err < 0) {
        LOG_ERR("Failed to update RGB strip (%d)", err);
    }
}

static int zmk_light_group_init(void)
{
    led_strip = DEVICE_DT_GET(STRIP_CHOSEN);
    memset(pixels, sizeof(pixels), 0);
    memset(state, sizeof(state), 0);
    apply_ledlayout_for_group(LG_ALL);

    light_group_enabled = IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_ON_START);
#if IS_ENABLED(CONFIG_ZMK_LIGHT_GROUP_AUTO_OFF_USB)
    light_group_enabled = zmk_usb_is_powered();
#endif

    if (light_group_enabled) {
        zmk_light_group_on();
    }

    return 0;
}

SYS_INIT(zmk_light_group_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
