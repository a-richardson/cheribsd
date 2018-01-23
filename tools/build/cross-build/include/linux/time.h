/* We can't use #pragma once here since at least the version of time.h
 * shipped with glibc must be included more than once with different
 * defines set */
/* #pragma once*/

#include_next <time.h>
/* GLIBC sets this when multiple-including time.h */
#ifndef __need_time_t
/* On Linux utimes() is not defined in time.h */
#include <utime.h>
/* sys/types.h is needed for opensolaris compat */
#include <sys/types.h>
#include <sys/time.h>
#endif
