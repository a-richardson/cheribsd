/*-
 * Copyright (c) 2002 Jonathan Mini <mini@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "libc_private.h"
#include "thr_private.h"

extern int		__vfprintf(FILE *, locale_t, const char *, __va_list);

/* XXXAR:  use a simple spinlock here to allow printfs/PANIC in umutex code */
static struct umutex	_thr_printf_umutex = DEFAULT_UMUTEX;
static const char	_sys_thr_self_failed[] = "__sys_thr_self() failed!\n";

void
_thread_printf(FILE *fp, const char *fmt, ...)
{
	va_list	 ap;
	int err;
	long tid = 0;

	va_start(ap, fmt);

	/* Don't call _get_curthread() to allow printf debugging TLS issues */
	err = __sys_thr_self(&tid);
	if (err != 0) {
		/* Can't use PANIC() here as that calls _thread_printf() */
		__sys_write(STDERR_FILENO, _sys_thr_self_failed,
		    strlen(_sys_thr_self_failed));
		abort();
	}
	/*
	 * Call the printf implementation that doesn't lock to allow calls
	 * to _thread_printf() from mutex code and before libthr initialization
	 * has completed.
	 *
	 * XXXAR: use a simple spinlock here to allow printfs/PANIC in umutex code
	 */
	_thr_umutex_lock(&_thr_printf_umutex, (uint32_t)tid);
	__vfprintf(fp, NULL, fmt, ap);
	_thr_umutex_unlock(&_thr_printf_umutex, (uint32_t)tid);
	va_end(ap);
}
