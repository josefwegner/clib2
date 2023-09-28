/*
 * $Id: math_e_remainderf.c,v 1.4 2023-07-19 12:04:24 clib4devs Exp $
 */

#ifndef _MATH_HEADERS_H
#include "math_headers.h"
#endif /* _MATH_HEADERS_H */

static const float zero = 0.0;

float
__ieee754_remainderf(float x, float p) {
    int32_t hx, hp;
    uint32_t sx;
    float p_half;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hp, p);
    sx = hx & 0x80000000;
    hp &= 0x7fffffff;
    hx &= 0x7fffffff;

    /* purge off exception values */
    if (hp == 0) return (x * p) / (x * p);        /* p = 0 */
    if ((hx >= 0x7f800000) ||            /* x not finite */
        ((hp > 0x7f800000)))            /* p is NaN */
        return ((long double) x * p) / ((long double) x * p);


    if (hp <= 0x7effffff) x = __ieee754_fmodf(x, p + p);    /* now x < 2p */
    if ((hx - hp) == 0) return zero * x;
    x = fabsf(x);
    p = fabsf(p);
    if (hp < 0x01000000) {
        if (x + x > p) {
            x -= p;
            if (x + x >= p) x -= p;
        }
    } else {
        p_half = (float) 0.5 * p;
        if (x > p_half) {
            x -= p;
            if (x >= p_half) x -= p;
        }
    }
    GET_FLOAT_WORD(hx, x);
    if ((hx & 0x7fffffff) == 0) hx = 0;
    SET_FLOAT_WORD(x, hx ^ sx);
    return x;
}
