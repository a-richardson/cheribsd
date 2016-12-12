# $FreeBSD$

COMPARTMENT_NAME=	helloworld

# XXXBD: stuff below this line should come from a bsd.c9t.mk

LDFLAGS+=	-Wl,-T,${.CURDIR}/../../libc_cheri/sandbox.ld \
		-nostdlib

LIBADD=	c_cheri

NEED_CHERI=sandbox
WANT_DUMP=yes
PROG=	${COMPARTMENT_NAME}.co.0
SRCS=	${COMPARTMENT_NAME}.c
MAN=

BINDIR=	/usr/libcheri

# cheri-unknown-freebsd-ld.lld: error: helloworld.c:50: undefined symbol 'abort'
CHERI_LLD_BROKEN=yes

.include <bsd.prog.mk>
