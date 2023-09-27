/*
 * $Id: ctype_tolower.c,v 1.5 2006-01-08 12:04:22 clib4devs Exp $
*/

#ifndef _CTYPE_HEADERS_H
#include "ctype_headers.h"
#endif /* _CTYPE_HEADERS_H */

int
tolower(int c) {
    DECLARE_LOCALEBASE();
    int result;
    struct _clib4 *__clib4 = __CLIB4;

    __locale_lock(__clib4);

    if (__clib4->__locale_table[LC_CTYPE] != NULL) {
        assert(LocaleBase != NULL);

        /* The parameter must be either EOF or in the range of an
           'unsigned char'. If it's not, then the behaviour is
           undefined. */
        if (c != EOF && ((0 <= c && c <= UCHAR_MAX) || ((c + 256) <= UCHAR_MAX)))
            result = ConvToLower(__clib4->__locale_table[LC_CTYPE], (ULONG)(c & 255));
        else
            result = c;
    } else {
        result = ('A' <= c && c <= 'Z') ? (c + ('a' - 'A')) : c;
    }

    __locale_unlock(__clib4);

    return (result);
}
