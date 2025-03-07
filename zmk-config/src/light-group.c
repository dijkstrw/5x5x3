#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
#include <zmk/workqueue.h>

#include <color-effect.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_CHOSEN(zmk_underglow)

#error "zmk,underglow is incompatible with zmk,light-group"

#endif

BUILD_ASSERT(DT_NODE_EXISTS(DT_PATH(ledlayout)), "ledlayout not found for LIGHT_GROUP");

#define STRIP_CHOSEN     DT_CHOSEN(zmk_light_group)
#define STRIP_NUM_PIXELS DT_PROP_LEN(DT_PATH(ledlayout), bindings)

static const uint8_t ledlayout[STRIP_NUM_PIXELS] = DT_PROP(DT_PATH(ledlayout), bindings);

#define DT_PHA_BY_IDX_HSV(node_id, pha, idx) {.raw = DT_PHA_BY_IDX(node_id, pha, idx, hsv)}

static const uint8_t background_num = DT_PROP_LEN(DT_PATH(colorgroup, backgrounds), colors);
static const hsv_t background[DT_PROP_LEN(DT_PATH(colorgroup, backgrounds), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, backgrounds), colors, DT_PHA_BY_IDX_HSV, (,)) };

static const uint8_t desktop_num = DT_PROP_LEN(DT_PATH(colorgroup, desktops), colors);
static const hsv_t desktop[DT_PROP_LEN(DT_PATH(colorgroup, desktops), colors)] = {
    DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, desktops), colors, DT_PHA_BY_IDX_HSV, (,)) };

static const struct device *led_strip;

static struct led_rgb pixels[STRIP_NUM_PIXELS];

static struct pixel_state state[STRIP_NUM_PIXELS];

static void zmk_light_group_tick(struct k_work *work)
{
    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        switch (state[i].effect) {
        case EFFECT_OFF:
            pixel_effect_off(&state[i], i);
            break;

        case EFFECT_HOLD:
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

    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        pixel_effect_init_rainbow(&state[i], i, STRIP_NUM_PIXELS);
    }

    k_timer_start(&light_group_tick, K_NO_WAIT, K_MSEC(50));

    return 0;
}

SYS_INIT(zmk_light_group_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
