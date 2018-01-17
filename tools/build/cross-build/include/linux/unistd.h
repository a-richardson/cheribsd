#pragma once

#include_next <unistd.h>
#include <stdlib.h>
#undef getopt

// Force POSIX compatibility in glibc getopt
static inline int getopt_real(int argc, char * const argv[], const char *optstring)
{
#ifdef __GLIBC__
	// If the first character of optstring is '+' or the environment variable
	// POSIXLY_CORRECT is set, then option processing stops as soon as a
	// nonoption argument is encountered.
	char* newoptstring = NULL;
	asprintf(&newoptstring, "+%s", optstring);
	int ret = bsd_getopt(argc, argv, newoptstring);
	free(newoptstring);
	return ret;
#else
	return bsd_getopt(argc, argv, optstring)
#endif
}

static inline int issetugid(void) {
	return 0;
}

#define getopt getopt_real
