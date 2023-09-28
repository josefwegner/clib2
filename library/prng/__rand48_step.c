/*
 * $Id: stdlib___rand48_step.c,v 1.0 2022-08-06 10:36:26 clib4devs Exp $
*/

#ifndef _STDLIB_HEADERS_H
#include "../stdlib/stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

#include "rand48.h"

uint64_t
__rand48_step(unsigned short *xi, unsigned short *lc) {
    uint64_t a, x;
    x = xi[0] | xi[1] + 0U << 16 | xi[2] + 0ULL << 32;
    a = lc[0] | lc[1] + 0U << 16 | lc[2] + 0ULL << 32;
    x = a * x + lc[3];
    xi[0] = x;
    xi[1] = x >> 16;
    xi[2] = x >> 32;
    return x & 0xffffffffffffull;
}
