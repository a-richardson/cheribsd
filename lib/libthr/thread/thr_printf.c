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
#include <unistd.h>
#include <pthread.h>

#include "libc_private.h"
#include "thr_private.h"

static void	pchar(int fd, char c);
static void	pstr(int fd, const char *s);

static volatile uint32_t _thread_printf_spinlock = 0;

// static inline char*
// atomic_flag_str(volatile uint32_t* val)
// {
// 	return atomic_load_acq_32(val) ? "true" : "false";
// }

static inline void
_thread_printf_spinlock_acquire(void)
{
// 	pstr(2, "_thread_printf_spinlock_acquire(): _thread_printf_spinlock = ");
// 	pstr(2, atomic_flag_str(&_thread_printf_spinlock));
// 	pchar(2, '\n');
	while(atomic_cmpset_acq_32(&_thread_printf_spinlock, 0, 1)) {
		/* XXX: sleep? */
// 		pstr(2, "looping: _thread_printf_spinlock = ");
// 		pstr(2, atomic_flag_str(&_thread_printf_spinlock));
// 		pchar(2, '\n');
	}
// 	pstr(2, "got lock: _thread_printf_spinlock = ");
// 	pstr(2, atomic_flag_str(&_thread_printf_spinlock));
// 	pchar(2, '\n');
}

static inline void
_thread_printf_spinlock_release(void)
{
// 	pstr(2, "about to release lock: _thread_printf_spinlock = ");
// 	pstr(2, atomic_flag_str(&_thread_printf_spinlock));
// 	pchar(2, '\n');
	THR_ASSERT(atomic_load_acq_32(&_thread_printf_spinlock) == 1, "Spinlock must be held!");
	atomic_set_rel_32(&_thread_printf_spinlock, 0);
	// WTF does this always print true???
// 	pstr(2, "released lock: _thread_printf_spinlock = ");
// 	pstr(2, atomic_flag_str(&_thread_printf_spinlock));
// 	pchar(2, '\n');
}


/*
 * Write formatted output to stdout, in a thread-safe manner.
 *
 * Recognises the following conversions:
 *	%c	-> char
 *	%d	-> signed int (base 10)
 *	%s	-> string
 *	%u	-> unsigned int (base 10)
 *	%x	-> unsigned int (base 16)
 *	%p	-> unsigned int (base 16)
 */
void
_thread_printf(int fd, const char *fmt, ...)
{

	static const char digits[16] = "0123456789abcdef";
	va_list	 ap;
	/* XXX_AR: we should print capabilities not vaddr_t -> increase size */
	char buf[40];
	char *s;
	uint64_t r, u;
	int c;
	int64_t d;
	int islong;
	int isptr;
	void* pointer;

	va_start(ap, fmt);
	/* Make sure that we don't get mixed [stderr/stdout]_debug messages */
	_thread_printf_spinlock_acquire();
	while ((c = *fmt++)) {
		islong = 0;
		isptr = 0;
		if (c == '%') {
next:			c = *fmt++;
			if (c == '\0')
				goto out;
			switch (c) {
			case 'c':
				pchar(fd, va_arg(ap, int));
				continue;
			case 's':
				pstr(fd, va_arg(ap, char *));
				continue;
			case 'l':
				islong = 1;
				goto next;
			case 'p':
				isptr = 1;
			case 'd':
			case 'u':
			case 'x':
				r = ((c == 'u') || (c == 'd')) ? 10 : 16;
				if (c == 'd') {
					if (islong)
						d = va_arg(ap, int64_t);
					else
						d = va_arg(ap, int);
					if (d < 0) {
						pchar(fd, '-');
						u = (uint64_t)(d * -1);
					} else
						u = (uint64_t)d;
				} else {
					/*
					 * XXX-AR: Is this ifdef needed?
					 * Doesn't casting to vaddr_t always work?
					 * (Code is based on the libc printf)
					 */
					if (isptr) {
						pointer = va_arg(ap, void*);
#ifdef __CHERI_PURE_CAPABILITY__
						u = cheri_getbase(pointer) +
						    cheri_getoffset(pointer);
#else
						u = (vaddr_t)pointer;
#endif
					} else if (islong) {
						u = va_arg(ap, uint64_t);
					} else {
						u = va_arg(ap, unsigned);
					}
				}
				s = buf;
				do {
					*s++ = digits[u % r];
				} while (u /= r);
				while (--s >= buf)
					pchar(fd, *s);
				continue;
			}
		}
		pchar(fd, c);
	}
out:	
	_thread_printf_spinlock_release();
	va_end(ap);
}

/*
 * Write a single character to stdout, in a thread-safe manner.
 */
static void
pchar(int fd, char c)
{

	__sys_write(fd, &c, 1);
}

/*
 * Write a string to stdout, in a thread-safe manner.
 */
static void
pstr(int fd, const char *s)
{

	__sys_write(fd, s, strlen(s));
}

