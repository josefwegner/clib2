/*
 * $Id: types.h,v 1.9 2006-01-08 12:06:14 obarthel Exp $
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
 *
 *****************************************************************************
 *
 * Documentation and source code for this library, and the most recent library
 * build are available from <https://github.com/afxgroup/clib2>.
 *
 *****************************************************************************
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <features.h>

#include <time.h>
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS

typedef char * caddr_t;
typedef unsigned int comp_t;
typedef unsigned long dev_t;
typedef unsigned int gid_t;
typedef unsigned int ino_t;
typedef unsigned int mode_t;
typedef unsigned int nlink_t;
typedef long int off_t;
#ifdef __USE_LARGEFILE64
typedef int64_t _off64_t;
typedef int64_t _fpos64_t;
#endif
typedef int pid_t;
typedef unsigned int rlim_t;
typedef int ssize_t;
typedef unsigned int uid_t;

#ifndef _BSDTYPES_DEFINED
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
#define _BSDTYPES_DEFINED
#endif

typedef unsigned long useconds_t;
typedef long suseconds_t;

__END_DECLS

#endif /* _SYS_TYPES_H */
