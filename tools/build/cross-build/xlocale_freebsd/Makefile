# in order to build localedef on Linux/Mac we need to build the FreeBSD xlocale code
LIB=	xlocale-freebsd
NO_SHARED=	yes

MK_SYMVER=	no
LIBC_SRCTOP=	${SRCTOP}/lib/libc/
MK_ICONV:=	no
.include "${LIBC_SRCTOP}/locale/Makefile.inc"

.PATH: ${LIBC_SRCTOP}/stdtime/
SRCS+=	timelocal.c

.include <bsd.lib.mk>

# Add this after bsd.lib.mk to get these includes first
CFLAGS+=	-I ${.CURDIR}/../libdb_freebsd -I ${.CURDIR}
CFLAGS+=	-I ${LIBC_SRCTOP}/locale
