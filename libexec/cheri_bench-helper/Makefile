#
# $FreeBSD$
#
PROG=	cheri_bench-helper
SRCS=	cheri_bench-helper.c

INCS=	cheri_bench-helper.h

LDFLAGS+=	-Wl,-T,${.CURDIR}/../../lib/libc_cheri/sandbox.ld \
		-nostdlib
MAN=

LIBADD=	c_cheri

NEED_CHERI=	sandbox
WANT_DUMP=	yes

NO_SHARED=	yes

# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: warning: cannot find entry symbol __start; defaulting to 0x8800
# BFD: cheri_bench-helper.full: don't know how to handle processor specific section `.preinit_array' [0x7000000d]
# objdump: cheri_bench-helper.full: File format not recognized
CHERI_LLD_BROKEN=yes

.include <bsd.prog.mk>
