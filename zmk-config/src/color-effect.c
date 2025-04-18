/*
 * Copyright (c) 2025 by Willem Dijkstra <wpd@xs4all.nl>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the auhor nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * color-effect
 *
 * Color effects and easings to go from one hue or state to another.
 */
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>

#include <stdint.h>
#include "color-effect.h"

#define STRIP_NUM_PIXELS DT_PROP_LEN(DT_PATH(ledlayout), bindings)

static uint8_t scale_u8(uint8_t i, fract8_t scale)
{
    return ((uint16_t)i * (uint16_t)(scale)) >> 8;
}

static int16_t scale_i16(int16_t i, fract8_t scale)
{
    return ((int32_t)i * (int32_t)(scale)) >> 8;
}

/*
 * Quadratic easing on t ∈ [0,1]:
 * f(t) = 2t²               when t < 0.5
 *      = 1 - 2(1-t)²       when t ≥ 0.5
 */
static uint8_t ease8_inoutquad(uint8_t x)
{
    uint8_t t = x;
    if (x & 0x80) {
        t = 0xff - t;
    }
    uint8_t xx = scale_u8(t, t);
    uint8_t xx2 = xx << 1;
    if (x & 0x80) {
        xx2 = 0xff - xx2;
    }
    return xx2;
}

void hsv_transition(hsv_t source, hsv_t target, fract8_t fraction, hsv_t *result)
{
    int16_t d;

    /* Hue is laid out in a circle, where 360° = 0°. We want to move
     * from one color to the other in the shortest path. So if our
     * distance is larger than half the circle, we want to go the
     * other way.
     */
    d = target.h - source.h;
    if (d >= HUE_HALF) {
        d = -1 * (HUE_MAX - d);
    } else if (d <= -HUE_HALF) {
        d += HUE_MAX;
    }

    d = source.h + scale_i16(d, fraction);
    if (d < 0) {
        d += HUE_MAX;
    }
    result->h = d % HUE_MAX;

    d = target.s - source.s;
    result->s = source.s + scale_i16(d, fraction);
    d = target.v - source.v;
    result->v = source.v + scale_i16(d, fraction);
}

static void increase_round_step(struct pixel_state *ps)
{
    uint16_t step;
    if (ps->step == STEP_MAX) {
        ps->round++;
        ps->step = 0;
        return;
    }
    step = ps->step + ps->speed;
    if (step >= STEP_MAX) {
        ps->step = STEP_MAX;
        return;
    } else {
        ps->step = step;
        return;
    }
}

/* hsv2rgb using integer arithmetic
 *
 * See https://www.vagrearg.org/content/hsvrgb for an excellent
 * explanation by B. Stultiens.
 */
void hsv2rgb(hsv_t *h, struct led_rgb *p)
{
    uint8_t sextant;
    uint8_t *r = &p->r;
    uint8_t *g = &p->g;
    uint8_t *b = &p->b;
    uint8_t *t;
    uint16_t bottom_level;
    uint8_t h_fraction;
    uint32_t slope;

#define swap(a, b)                                                                                 \
    do {                                                                                           \
        t = a;                                                                                     \
        a = b;                                                                                     \
        b = t;                                                                                     \
    } while (0)

    /* monochromatic test */
    if (!h->s) {
        *r = *g = *b = h->v;
        return;
    }

    sextant = h->h >> 8;
    sextant %= SEXTANT_MAX;

    /* Looking at the hsv to rgb picture:
     *
     *      1|
     *       |
     *      V|-r-.-g-.-g-.-b-.-b-.-r-.
     *       |  / \     / \     / \
     *       | g   r   b   g   r   b
     *       |/     \ /     \ /     \
     * V(1-S)|-b-.-b-.-r-.-r-.-g-.-g-.
     *       |
     *      0|_________________________
     *        0 60  120 180 240 300 360
     *
     * - one of the rgb colors is at h->v
     * - one of the rgb colors is at h->v * (1 - h->s)
     * - one of the rgb colors is enroute up or down
     *
     * Sextant one is our standard, and when in other sextants we
     * rearrange the pointers so that we can calculate like we were in
     * sextant one.
     */
    switch (sextant) {
    case 0:
        swap(r, g);
        break;
    case 1:
        break;
    case 2:
        swap(r, b);
        break;
    case 3:
        swap(r, g);
        swap(g, b);
        break;
    case 4:
        swap(g, b);
        break;
    case 5:
        swap(r, g);
        swap(r, b);
        break;
    }

    *g = h->v;

    bottom_level = h->v * (0xff - h->s);
    bottom_level += 1;
    bottom_level += bottom_level >> 8;

    *b = bottom_level >> 8;

    h_fraction = h->h & 0xff;

    if (sextant & 1) {
        /* slope down */
        slope = h->v * (uint32_t)((0xff << 8) - (uint16_t)(h->s * h_fraction));
    } else {
        /* slope up */
        slope = h->v * (uint32_t)((0xff << 8) - (uint16_t)(h->s * (0x100 - h_fraction)));
    }

    slope += slope >> 8;
    slope += h->v;
    *r = slope >> 16;
}

void pixel_effect_off(struct pixel_state *ps, int position)
{
    ps->target.v = 0;
}

void pixel_effect_init_hold(struct pixel_state *ps, hsv_t target)
{
    ps->effect = EFFECT_HOLD;
    ps->source = ps->current;
    ps->target = target;
    ps->round = ROUND_RAMPUP;
    ps->step = 0;
    ps->speed = SPEED_DEFAULT;
}

void pixel_effect_hold(struct pixel_state *ps, int position)
{
    /* There are two phases to a hold;
     * - ramp up towards color target from source
     * - dwell on color target
     */
    uint8_t scale;

    if (ps->round == ROUND_OFF) {
        return;
    }

    scale = ease8_inoutquad(ps->step);
    switch (ps->round) {
    case ROUND_RAMPUP:
        hsv_transition(ps->source, ps->target, scale, &ps->current);
        break;

    case ROUND_DWELL:
        ps->current = ps->target;
        break;
    }

    increase_round_step(ps);
    if (ps->round >= ROUND_OFF) {
        ps->round = ROUND_OFF;
    }
}

void pixel_effect_init_flash(struct pixel_state *ps, hsv_t target)
{
    ps->effect = EFFECT_FLASH;
    ps->source = ps->current;
    ps->target = target;
    ps->round = ROUND_RAMPUP;
    ps->step = 0;
    ps->speed = SPEED_DEFAULT;
}

void pixel_effect_flash(struct pixel_state *ps, int position)
{
    /* There are three phases to a flash;
     * - ramp up towards color target from source
     * - dwell on color target
     * - ramp down towards original source from flash target
     */
    uint8_t scale;

    if (ps->round == ROUND_OFF) {
        return;
    }

    scale = ease8_inoutquad(ps->step);
    switch (ps->round) {
    case ROUND_RAMPUP:
        hsv_transition(ps->source, ps->target, scale, &ps->current);
        break;

    case ROUND_DWELL:
        ps->current = ps->target;
        break;

    case ROUND_RAMP_DOWN:
        hsv_transition(ps->target, ps->source, scale, &ps->current);
        break;
    }

    increase_round_step(ps);
    if (ps->round >= ROUND_OFF) {
        ps->round = ROUND_OFF;
    }
}

void pixel_effect_init_rainbow(struct pixel_state *ps, int position, int max_position)
{
    ps->effect = EFFECT_RAINBOW;
    ps->current.h = (HUE_MAX / max_position) * position;
    ps->current.v = VAL_MAX;
    ps->current.s = SAT_MAX;
}

void pixel_effect_rainbow(struct pixel_state *ps, int position)
{
    ps->current.h += SPEED_DEFAULT;
    ps->current.h %= HUE_MAX;
}
