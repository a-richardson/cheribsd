#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

.PATH: ${SRCTOP}/lib/libc/gen		# for pw_scan.c

PROG=	pwd_mkdb
MAN=	pwd_mkdb.8
SRCS=	pw_scan.c pwd_mkdb.c
.if (!empty(${.TARGETS:Mbuild-tools}) || defined(BOOTSTRAPPING)) && \
	${.MAKE.OS} != "FreeBSD"
CFLAGS+=-DNEED_FREEBSD_STRUCT_PASSWD
.endif

CFLAGS+= -I${SRCTOP}/lib/libc/gen		# for pw_scan.h

.include <bsd.prog.mk>
