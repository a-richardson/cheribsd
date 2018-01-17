# $FreeBSD$

PACKAGE=lib${LIB}
LIB=	openbsd
SRCS=	getdtablecount.c \
	imsg-buffer.c \
	imsg.c \
	ohash.c
INTERNALLIB=

.if (!empty(${.TARGETS:Mbuild-tools}) || defined(BOOTSTRAPPING)) && \
	${.MAKE.OS} == "Linux"
# libopenbsd won't compile during bootstrap for Linux, but it seems like we don't need
# any of the functions there so it is fine
SRCS:=${SRCS:Ngetdtablecount.c}
.endif


CFLAGS+= -I${.CURDIR}

WARNS=	3

.include <bsd.lib.mk>
