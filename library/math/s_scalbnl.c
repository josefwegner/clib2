/*
 * $Id: math_s_scalbnl.c,v 1.0 2023-07-19 12:04:24 clib2devs Exp $
*/

#ifndef _MATH_HEADERS_H
#include "math_headers.h"
#endif /* _MATH_HEADERS_H */

long double
scalbnl(long double x, int n) {
    return scalbn(x, n);
}
