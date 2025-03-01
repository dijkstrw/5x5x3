#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>

#include <color.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define LED_GPIO_NODE_ID DT_COMPAT_GET_ANY_STATUS_OKAY(gpio_leds)

BUILD_ASSERT(DT_NODE_EXISTS(DT_PATH(ledlayout)), "ledlayout not found for LIGHT_GROUP");

static const u_int8_t ledlayout_num = DT_PROP_LEN(DT_PATH(ledlayout), bindings);
static const u_int8_t ledlayout[DT_PROP_LEN(DT_PATH(ledlayout), bindings)] =
        DT_PROP(DT_PATH(ledlayout), bindings);

static const hsv_t background[DT_PROP_LEN(DT_PATH(colorgroup, backgrounds), colors)] = {
        DT_FOREACH_PROP_ELEM_SEP(DT_PATH(colorgroup, backgrounds), colors, DT_PROP_BY_IDX, (,)) };
