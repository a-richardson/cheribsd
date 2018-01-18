#pragma once
/*
 * glibc shipped with Ubuntu 16.04 doesn't include a definition of
 * struct timespec when sys/stat.h is included
 * */
#define __need_timespec
#include <time.h>
#include_next <sys/stat.h>
