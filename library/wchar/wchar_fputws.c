/*
 * $Id: wchar_fputws.c,v 1.3 2006-01-08 12:04:27 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _WCHAR_HEADERS_H
#include "wchar_headers.h"
#endif /* _WCHAR_HEADERS_H */

wint_t
fputws(const wchar_t *ws, FILE *fp)
{
	char buf[BUFSIZ] = {0};
	int nwritten = 0;
	int nchars = (int)wcslen(ws);

	while (nchars > 0)
	{
		int nbytes = 0;
		char *ptr = (char *)&buf;
		while ((nbytes < (BUFSIZ - (MB_LEN_MAX * 2))) && (nchars))
		{
			int n = wctomb(ptr, *ws);
			if (n < 0)
			{
				__set_errno(EILSEQ);
				return 0;
			}
			ws++;
			ptr += n;
			nbytes += n;
			nchars--;
		}
		*ptr = '\0';
		if (fputs(buf, fp) < nbytes)
		{
			return 0;
		}
		nwritten += nbytes;
	}
	return (nwritten);
}
