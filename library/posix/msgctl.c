/*
 * $Id: msg_msgctl.c,v 1.1 2021-01-26 13:59:43 clib2devs Exp $
*/

#ifndef _SHM_HEADERS_H
#include "shm_headers.h"
#endif /* _SHM_HEADERS_H */

int
_msgctl(int qid, int cmd, struct msqid_ds *buf) {
    DECLARE_SYSVYBASE();
    struct _clib2 *__clib2 = __CLIB2;

    ENTER();

    SHOWVALUE(qid);
    SHOWVALUE(cmd);
    SHOWPOINTER(buf);

    int ret = -1;
    if (__clib2->haveShm) {
        ret = msgctl(qid, cmd, buf);
        if (ret < 0) {
            __set_errno(GetIPCErr());
        }
    } else {
        __set_errno(ENOSYS);
    }

    RETURN(ret);
    return ret;
}
