# $FreeBSD$

PROG=	readpng-cheri-helper
SRCS=	readpng-cheri.c				\
	execve.S				\
	sysarch.S

NEED_CHERI=	sandbox
WANT_DUMP=	yes

# objdump -xrsSD readpng-cheri-helper.full > readpng-cheri-helper.dump
# BFD: readpng-cheri-helper.full: don't know how to handle processor specific section `.preinit_array' [0x7000000d]
# objdump: readpng-cheri-helper.full: File format not recognized
CHERI_LLD_BROKEN=yes

.PATH: ${.CURDIR}/../../lib/libimagebox
SRCS+=	decode_png.c

MAN=

LDFLAGS+=	-Wl,-T,${.CURDIR}/../../../lib/libc_cheri/sandbox.ld \
		-nostdlib
#STRIP=
CFLAGS+=	-I${.CURDIR}/../../lib/libimagebox
CFLAGS+=	-I${.CURDIR}/../../../lib/libc/${MACHINE}
CFLAGS+=	-I${.CURDIR}/../../../lib/libc/include
CFLAGS+=	-DIMAGEBOX_PNG_NO_FD
LIBADD+=	vuln_png c_cheri

NO_SHARED=	yes

WARNS=4

.PATH: ${.CURDIR}/${MACHINE_ARCH}

.include <bsd.prog.mk>

CFLAGS+=	${CFLAGS.${.IMPSRC:T}}
CFLAGS.zutil.c=         -Wno-incompatible-pointer-types-discards-qualifiers
CFLAGS.inffast.c=	-Wno-cast-qual -O0
CFLAGS.inflate.c=	-Wno-cast-qual
