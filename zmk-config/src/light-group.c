#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

#include <zephyr/logging/log.h>
#include <zmk/keymap.h>
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

/* TODO: see if these similar stanzas can be rewritten as cpp statements */
/* TODO: for the continuous types: assert that we have at least 2 values */
static const uint8_t battery_num = DT_PROP_LEN(DT_PATH(colorgroup, batterys), colors);
static const hsv_t battery[DT_PROP_LEN(DT_PATH(colorgroup, batterys), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, batterys), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t battery_value = 0;

static const uint8_t background_num = DT_PROP_LEN(DT_PATH(colorgroup, backgrounds), colors);
static const hsv_t background[DT_PROP_LEN(DT_PATH(colorgroup, backgrounds), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, backgrounds), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t background_value = 0;

static const uint8_t desktop_num = DT_PROP_LEN(DT_PATH(colorgroup, desktops), colors);
static const hsv_t desktop[DT_PROP_LEN(DT_PATH(colorgroup, desktops), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, desktops), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t desktop_value = 0;

static const uint8_t endpoint_num = DT_PROP_LEN(DT_PATH(colorgroup, endpoints), colors);
static const hsv_t endpoint[DT_PROP_LEN(DT_PATH(colorgroup, endpoints), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, endpoints), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t endpoint_value;

static const uint8_t hid_num = DT_PROP_LEN(DT_PATH(colorgroup, hids), colors);
static const hsv_t hid[DT_PROP_LEN(DT_PATH(colorgroup, hids), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, hids), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t hid_value;

static const uint8_t layer_num = DT_PROP_LEN(DT_PATH(colorgroup, layers), colors);
static const hsv_t layer[DT_PROP_LEN(DT_PATH(colorgroup, layers), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, layers), colors, DT_PHA_BY_IDX_HSV, (,)) };

static const uint8_t profile_num = DT_PROP_LEN(DT_PATH(colorgroup, profiles), colors);
static const hsv_t profile[DT_PROP_LEN(DT_PATH(colorgroup, profiles), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, profiles), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t profile_value;

static const uint8_t volume_num = DT_PROP_LEN(DT_PATH(colorgroup, volumes), colors);
static const hsv_t volume[DT_PROP_LEN(DT_PATH(colorgroup, volumes), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, volumes), colors, DT_PHA_BY_IDX_HSV, (,)) };
uint8_t volume_value;

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

static void light_group_range_select(struct pixel_state *current, const hsv_t (*group)[],
                                     uint8_t group_max, uint8_t value)
{
    value %= group_max;
    pixel_effect_init_hold(current, &(*group)[value]);
}

static void light_group_continuous(struct pixel_state *current, const hsv_t (*group)[],
                                   uint8_t group_max, fract8_t percentage)
{
    uint8_t bucket_size = UINT8_MAX / (group_max - 1);
    uint8_t start_index = (percentage / bucket_size);
    fract8_t mix = (uint16_t)(UINT8_MAX * (percentage % bucket_size)) / bucket_size;
    hsv_t target;

    if (start_index == (group_max - 1)) {
        pixel_effect_init_hold(current, &(*group)[start_index + 1]);
    } else {
        hsv_transition((*group)[start_index], (*group)[start_index + 1], mix, &target);
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
            light_group_continuous(current, &battery, battery_num, battery_value);
            break;

        case LG_DESKTOP:
            light_group_range_select(current, &desktop, desktop_num, desktop_value);
            break;

        case LG_ENDPOINT:
            light_group_range_select(current, &endpoint, endpoint_num, endpoint_value);
            break;

        case LG_HID:
            light_group_range_select(current, &hid, hid_num, hid_value);
            break;

        case LG_LAYER:
            light_group_range_select(current, &layer, layer_num, layer_value);
            break;

        case LG_PROFILE:
            light_group_range_select(current, &profile, profile_num, profile_value);
            break;

        case LG_VOLUME:
            light_group_continuous(current, &volume, volume_num, volume_value);
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
