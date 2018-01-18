#pragma once
#include_next <limits.h>

#define MAXBSIZE        65536   /* must be power of 2 */
#define OFF_MAX	((off_t)(sizeof(off_t) == sizeof(int8_t) ? INT8_MAX :	\
		sizeof(off_t) == sizeof(int16_t)  ? INT16_MAX   :	\
		sizeof(off_t) == sizeof(int32_t)  ? INT32_MAX   :	\
		sizeof(off_t) == sizeof(int64_t)  ? INT64_MAX   :	\
		sizeof(off_t) == sizeof(intmax_t) ? INTMAX_MAX  : 0));
#define QUAD_MAX INT64_MAX

#ifndef GID_MAX
#define GID_MAX ((gid_t)-1)
#endif


#ifndef UID_MAX
#define UID_MAX ((uid_t)-1)
#endif
