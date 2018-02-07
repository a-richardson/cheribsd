# $FreeBSD$

PROG=	services_mkdb
MAN=	services_mkdb.8
SRCS=	services_mkdb.c uniq.c extern.h

# This is needed to bootstrap on a Linux host:
LDADD+=	${FREEBSD_LIBDB}

.include <bsd.prog.mk>
