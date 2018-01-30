#pragma once
#include_next <_types.h>

/* The MacOS definition of __strftimelike is incompatible */
#undef __strftimelike
#define	__strftimelike(fmtarg, firstvararg) \
	    __attribute__((__format__ (__strftime__, fmtarg, firstvararg)))
