/*
 * $Id: complex_clogf.c,v 1.0 2021-01-30 11:33:52 clib2devs Exp $
*/

#ifndef _COMPLEX_HEADERS_H
#include "complex_headers.h"
#endif /* _COMPLEX_HEADERS_H */

float complex
clogf(float complex z) {
    return CMPLXF(logf(cabsf(z)), cargf(z));
}
