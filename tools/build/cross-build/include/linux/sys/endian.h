#pragma once
#include_next <sys/endian.h>

#ifndef bswap32
#define bswap32(a) __builtin_bswap32(a)
#endif
