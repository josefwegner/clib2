/*
 * $Id: wait_wait.c,v 1.0 2023-06-09 12:04:27 clib2devs Exp $
*/

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

#include <sys/wait.h>

pid_t wait(int *status) {
    int32_t rc = WaitForChildExit(0);
}
