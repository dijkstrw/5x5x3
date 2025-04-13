#pragma once

#include <stdint.h>

#include "color.h"
#include <dt-bindings/zmk/lightgroup.h>

#define LG_ALL 0xff

enum light_group_effect {
    EFFECT_OFF,
    EFFECT_HOLD,
    EFFECT_FLASH,
    EFFECT_RAINBOW,
};

typedef uint8_t fract8_t;

struct pixel_state {
    hsv_t source;
    hsv_t target;
    hsv_t current;
    uint8_t effect;
    uint8_t speed;
    uint8_t step;
    uint8_t round;
};

/*
 * Effects have rounds, and move forward in steps during those rounds.  Our
 * timer is fired every 50ms, so that means we have (1000 / 50) = 20 timer evals
 * in one second.
 *
 * Our total effect time depends on the number of rounds in the effect. Hold
 * just has a rampup away from current color to the next, so 1 round. Flash has
 * rampup, hold, rampdown, so 3.
 *
 * The speed of the effect is then ((rounds * (step_max / speed_default) ) / 20)
 * in seconds.
 *
 */

#define SPEED_DEFAULT 13
#define STEP_MAX      255

enum steps {
    ROUND_RAMPUP = 0,
    ROUND_DWELL,
    ROUND_RAMP_DOWN,
    ROUND_OFF,
};

void hsv2rgb(hsv_t *h, struct led_rgb *p);
void hsv_transition(hsv_t source, hsv_t target, fract8_t fraction, hsv_t *result);
void pixel_effect_off(struct pixel_state *ps, int position);
void pixel_effect_init_hold(struct pixel_state *ps, hsv_t *target);
void pixel_effect_hold(struct pixel_state *ps, int position);
void pixel_effect_init_flash(struct pixel_state *ps, hsv_t *target);
void pixel_effect_flash(struct pixel_state *ps, int position);
void pixel_effect_init_rainbow(struct pixel_state *ps, int position, int max_position);
void pixel_effect_rainbow(struct pixel_state *ps, int position);
