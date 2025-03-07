#pragma once

#include "color.h"

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
    uint16_t step;
    uint8_t round;
};

#define STEP_MAX 0xff

void hsv2rgb(hsv_t *h, struct led_rgb *p);
void pixel_effect_off(struct pixel_state *ps, int position);
void pixel_effect_hold(struct pixel_state *ps, int position);
void pixel_effect_flash(struct pixel_state *ps, int position);
void pixel_effect_init_rainbow(struct pixel_state *ps, int position, int max_position);
void pixel_effect_rainbow(struct pixel_state *ps, int position);
