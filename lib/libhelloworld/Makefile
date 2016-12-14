# $FreeBSD$

LIB=	helloworld
SRCS=	helloworld.c
INCS=	helloworld.h

LIBADD=	cheri

INCSDIR=	${INCLUDEDIR}/cheri

NEED_CHERI?=hybrid

.ifndef LIBCHERI
SUBDIR=	compartment
.endif

# links against libcheri and libcheri has non-PIC relocations:
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/lib/libcheri/mips64/libcheri_classes.S:41: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '__cheri_enter_stack_sp' defined in /home/alr48/cheri/build/cheribsd-obj-256/mips.mips64/home/alr48/cheri/sources/cheribsd/tmp/usr/libcheri/libcheri.a(cheri_enter.o)
# CHERI_LLD_BROKEN=yes
NO_PIC=yes

.include <bsd.lib.mk>
