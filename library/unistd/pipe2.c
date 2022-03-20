/*
 * $Id: unistd_pipe2.c,v 1.0 2020-01-14 12:35:27 clib2devs Exp $
*/

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

static int pipenum = 0;

int pipe2(int fd[2], int flags) {
    char pipe_name[1024] = {0};

    /* Check the supported flags.  */
    if ((flags & ~(O_NONBLOCK)) != 0) {
        __set_errno(EINVAL);
        RETURN(-1);
        return -1;
    }

    ENTER();
    DECLARE_UTILITYBASE();

#ifdef USE_TEMPFILES
    snprintf(pipe_name, sizeof(pipe_name), "T:%x.%08x", pipenum++, ((struct Process *)FindTask(NULL))->pr_ProcessID);
#else
    if (flags & O_NONBLOCK)
        snprintf(pipe_name, sizeof(pipe_name), "PIPE:%x%lu/32768/0/NOBLOCK", pipenum++,
                 ((struct Process *) FindTask(NULL))->pr_ProcessID);
    else
        snprintf(pipe_name, sizeof(pipe_name), "PIPE:%x%lu/32768/0", pipenum++,
                 ((struct Process *) FindTask(NULL))->pr_ProcessID);
#endif // USE_TEMPFILES

    fd[1] = open(pipe_name, O_WRONLY | O_CREAT);
    fd[0] = open(pipe_name, O_RDONLY);

    if (fd[0] == -1 || fd[1] == -1) {
        if (fd[0] != -1)
            close(fd[0]);
        if (fd[1] != -1)
            close(fd[1]);

        __set_errno(EINVAL);
        RETURN(-1);
        return -1;
    }

    RETURN(0);
    return 0;
}
