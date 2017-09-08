#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

.include <src.opts.mk>

PROG=	find
SRCS=	find.c function.c ls.c main.c misc.c operator.c option.c \
	getdate.y
YFLAGS=
CFLAGS+=	-DHAVE_STRUCT_STAT_BIRTHTIME=1 -DHAVE_STRUCT_STAT_ST_FLAGS=1 \
		-DHAVE_STRUCT_STATFS_F_FSTYPENAME=1

NO_WMISSING_VARIABLE_DECLARATIONS=

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests

.include <bsd.prog.mk>
