/*
  $Id: pthread_mutexattr_setpshared.c,v 1.00 2023-04-16 12:09:49 clib4devs Exp $
*/

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

int
pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared) {
    if (pshared > 1U)
        return EINVAL;
    attr->pshared &= ~128U;
    attr->pshared |= pshared << 7;
    return 0;
}
