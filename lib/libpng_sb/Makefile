# $FreeBSD$

LIB?=	png_sb
SHLIB_MAJOR= 15

CFLAGS+=	-I${.CURDIR} \
		-I${.CURDIR}/../../libexec/libpng_sb-helper \
		-I${.CURDIR}/../libpng \
		-I${.CURDIR}/../../contrib/libpng

SRCS=	libpng_sb.c
WARNS?=	6

.ifdef LIBCHERI
NEED_CHERI=pure
.else
NEED_CHERI=	hybrid
.endif

.include <bsd.lib.mk>

CFLAGS+=	-Wno-cast-align -Wno-cast-qual
# XXXAR: the casting here is weird, I'm not sure how to fix it
CFLAGS+=	-Wno-error=capability-to-integer-cast
