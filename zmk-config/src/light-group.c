#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

#include <zephyr/logging/log.h>
#include <zmk/keymap.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/hid_indicators_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/workqueue.h>

#include <stdlib.h>

#include <color-effect.h>

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

#define DT_PHA_BY_IDX_HSV(node_id, pha, idx) {.raw = DT_PHA_BY_IDX(node_id, pha, idx, hsv)}

#define DEFINE_COLOR_GROUP(name, min_len)                                                          \
    BUILD_ASSERT(DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors) >= min_len,                     \
                 "colorgroup/" #name "s must have at least " #min_len " colors");                  \
    static const uint8_t name##_num = DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors);           \
    static const hsv_t name[DT_PROP_LEN(DT_PATH(colorgroup, name##s), colors)] = {                 \
        DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, name##s), colors, DT_PHA_BY_IDX_HSV, (,)) };      \
    uint8_t name##_value = 0;

DEFINE_COLOR_GROUP(battery, 2)
DEFINE_COLOR_GROUP(background, 1)
DEFINE_COLOR_GROUP(desktop, 1)
DEFINE_COLOR_GROUP(endpoint, 1)
DEFINE_COLOR_GROUP(hid, 2)
DEFINE_COLOR_GROUP(layer, 1)
DEFINE_COLOR_GROUP(profile, 2)
DEFINE_COLOR_GROUP(volume, 2)

static const struct device *led_strip;

static struct led_rgb pixels[STRIP_NUM_PIXELS];

static struct pixel_state state[STRIP_NUM_PIXELS];

static int cmd_desktop(const struct shell *sh, size_t argc, char **argv)
{
    desktop_value = atoi(argv[1]) % desktop_num;
    updated_groups |= (1 << LG_DESKTOP);

    return 0;
}

static int cmd_volume(const struct shell *sh, size_t argc, char **argv)
{
    volume_value = atoi(argv[1]);
    updated_groups |= (1 << LG_VOLUME);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_lightgroup,
                               SHELL_CMD_ARG(desktop, NULL, "Set desktop value", cmd_desktop, 2, 0),
                               SHELL_CMD_ARG(volume, 0, "Set volume value", cmd_volume, 2, 0),
                               SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(lightgroup, &sub_lightgroup, "Light group values", NULL);

static void light_group_range_select(struct pixel_state *current, const hsv_t *group,
                                     uint8_t group_max, uint8_t value)
{
    value %= group_max;
    pixel_effect_init_hold(current, &group[value]);
}

static void light_group_continuous(struct pixel_state *current, const hsv_t *group,
                                   uint8_t group_max, fract8_t percentage)
{
    uint8_t bucket_size = UINT8_MAX / (group_max - 1);
    uint8_t start_index = (percentage / bucket_size);
    fract8_t mix = (uint16_t)(UINT8_MAX * (percentage % bucket_size)) / bucket_size;
    hsv_t target;

    if (start_index == (group_max - 1)) {
        pixel_effect_init_hold(current, &group[start_index + 1]);
    } else {
        hsv_transition(group[start_index], group[start_index + 1], mix, &target);
        pixel_effect_init_hold(current, &target);
    }
}

static void apply_ledlayout_for_group(uint8_t group)
{
    zmk_keymap_layer_index_t layer_value = zmk_keymap_highest_layer_active();
    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        /* Partial update if requested */
        if ((lightgroup[layer_value][i] != group) && (group != LG_ALL)) {
            continue;
        }

        struct pixel_state *current = &state[ledlayout[i]];
        switch (lightgroup[layer_value][i]) {
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

static bool handle_layer_change(const zmk_event_t *eh)
{
    const struct zmk_layer_state_changed_event *ev =
        (const struct zmk_layer_state_changed_event *)eh;
    if (ev->data.state && ev->data.layer != layer_value) {
        layer_value = ev->data.layer;
        updated_groups |= (1 << LG_LAYER);
    }
    return false;
}

ZMK_LISTENER(light_group_layer, handle_layer_change);
ZMK_SUBSCRIPTION(light_group_layer, zmk_layer_state_changed);

static bool handle_endpoint_change(const zmk_event_t *eh)
{
    const struct zmk_endpoint_changed_event *ev = (const struct zmk_endpoint_changed_event *)eh;
    uint8_t new_endpoint = (ev->data.endpoint.transport == ZMK_TRANSPORT_USB) ? 0 : 1;
    if (new_endpoint != endpoint_value) {
        endpoint_value = new_endpoint;
        updated_groups |= (1 << LG_ENDPOINT);
    }
    return false;
}

ZMK_LISTENER(light_group_endpoint, handle_endpoint_change);
ZMK_SUBSCRIPTION(light_group_endpoint, zmk_endpoint_changed);

static bool handle_hid_change(const zmk_event_t *eh)
{
    const struct zmk_hid_indicators_changed *ev = (const struct zmk_hid_indicators_changed *)eh;
    if (ev->indicators != hid_value) {
        hid_value = ev->indicators;
        updated_groups |= (1 << LG_HID);
    }
    return false;
}

ZMK_LISTENER(light_group_hid, handle_hid_change);
ZMK_SUBSCRIPTION(light_group_hid, zmk_hid_indicators_changed);

static bool handle_profile_change(const zmk_event_t *eh)
{
    const struct zmk_ble_active_profile_changed_event *ev =
        (const struct zmk_ble_active_profile_changed_event *)eh;
    if (ev->data.profile != profile_value) {
        profile_value = ev->data.profile;
        updated_groups |= (1 << LG_PROFILE);
    }
    return false;
}

ZMK_LISTENER(light_group_profile, handle_profile_change);
ZMK_SUBSCRIPTION(light_group_profile, zmk_ble_active_profile_changed);

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

K_WORK_DEFINE(light_group_tick_work, zmk_light_group_tick);

static void zmk_light_group_tick_handler(struct k_timer *timer)
{
    /* TODO: bail out here when usb is not connected */

    k_work_submit_to_queue(zmk_workqueue_lowprio_work_q(), &light_group_tick_work);
}

K_TIMER_DEFINE(light_group_tick, zmk_light_group_tick_handler, 0);

static int zmk_light_group_init(void)
{
    led_strip = DEVICE_DT_GET(STRIP_CHOSEN);

    memset(pixels, sizeof(pixels), 0);
    memset(state, sizeof(state), 0);
    apply_ledlayout_for_group(LG_ALL);

    k_timer_start(&light_group_tick, K_NO_WAIT, K_MSEC(50));

    return 0;
}

SYS_INIT(zmk_light_group_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
