/* We can't use #pragma once here since at least the version of time.h
 * shipped with glibc must be included more than once with different
 * defines set */
/* #pragma once*/

#include_next <time.h>
/* On Linux utimes() is not defined in time.h */
#include <utime.h>
#include <sys/time.h>
