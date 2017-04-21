# $FreeBSD$

PAMDIR=		${.CURDIR}/../../../../contrib/openpam

MK_INSTALLLIB=	no
MK_PROFILE=	no

CFLAGS+= -I${PAMDIR}/include -I${.CURDIR}/../../libpam
CFLAGS+= -mxgot

SHLIB_NAME?=	${LIB}.so.${SHLIB_MAJOR}
LIBADD+=	pam

.include "../Makefile.inc"
