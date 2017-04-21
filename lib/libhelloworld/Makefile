# $FreeBSD$

LIB=	helloworld
SRCS=	helloworld.c
INCS=	helloworld.h
NO_PIC=	yes

LIBADD=	cheri

INCSDIR=	${INCLUDEDIR}/cheri

NEED_CHERI?=hybrid

.ifndef LIBCHERI
# LLD crashes
# SUBDIR=	compartment
.endif

.include <bsd.lib.mk>
