/*
  $Id: pthread_join.c,v 1.00 2022-07-18 12:09:49 clib4devs Exp $

  Copyright (C) 2014 Szilard Biro
  Copyright (C) 2018 Harry Sintonen
  Copyright (C) 2019 Stefan "Bebbo" Franke - AmigaOS 3 port

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _TIME_HEADERS_H
#include "time_headers.h"
#endif /* _TIME_HEADERS_H */

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

#include "common.h"
#include "pthread.h"

int
pthread_join(pthread_t thread, void **value_ptr) {
    ThreadInfo *inf = GetThreadInfo(thread);
    struct Task *task = FindTask(NULL);

    if (inf == NULL || inf->parent == NULL)
        return ESRCH;

    if (inf->detached)
        return EINVAL;

    if ((struct Task *) inf->task == task) {
        return EDEADLK;
    }

    pthread_testcancel();

    while (inf->status != THREAD_STATE_DESTRUCT) {
        Wait(SIGF_PARENT);
    }

    if (value_ptr)
        *value_ptr = inf->ret;

    ObtainSemaphore(&thread_sem);
    _pthread_clear_threadinfo(inf);
    ReleaseSemaphore(&thread_sem);

    return 0;
}
