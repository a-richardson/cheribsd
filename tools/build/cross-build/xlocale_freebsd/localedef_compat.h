#pragma once

#define __BSD_VISIBLE           1
#define __XSI_VISIBLE           700
#define __POSIX_VISIBLE         200809
#define __ISO_C_VISIBLE         1999

#define _WINT_T_DECLARED 1

typedef unsigned int wint_t;
typedef int __ct_rune_t;
typedef __ct_rune_t __rune_t;

#ifdef __APPLE__
struct __sFILE;
typedef struct __sFILE FILE;
#else
/*
 * mbstate_t is an opaque object to keep conversion state during multibyte
 * stream conversions.
 */
typedef union {
    char            __mbstate8[128];
    __INT64_TYPE__  _mbstateL;      /* for alignment */
} __mbstate_t;
#endif
extern int __mb_cur_max;
extern int ___mb_cur_max(void);

#define _once pthread_once
