# $FreeBSD$

# Use the following command to build local debug version of dynamic
# linker:
# make DEBUG_FLAGS=-g DEBUG=-DDEBUG MK_TESTS=no all

.include <src.opts.mk>
MK_SSP=		no
MK_CHERI_SHARED_PROG:=yes

.PATH: ${.CURDIR}/../../lib/libmalloc_simple

PROG?=		ld-cheri-elf.so.1
SRCS=		rtld_start.S \
		reloc.c rtld.c rtld_lock.c rtld_printf.c map_object.c \
		heap.c malloc.c xmalloc.c debug.c libmap.c write.S
MAN=
NEED_CHERI=	pure
WANT_DUMP=yes
MK_CHERI_SHARED=yes
CSTD?=		gnu99
CFLAGS+=	-Wall -DFREEBSD_ELF -DIN_RTLD -ffreestanding
CFLAGS+=	-I${SRCTOP}/lib/csu/common \
		-I${SRCTOP}/lib/libc/${RTLD_ARCH}
.if exists(${.CURDIR}/${MACHINE_ARCH})
RTLD_ARCH=	${MACHINE_ARCH}
.else
RTLD_ARCH=	${MACHINE_CPUARCH}
.endif
CFLAGS+=	-I${.CURDIR}/${RTLD_ARCH} -I${.CURDIR}
LDFLAGS+=	-nostdlib -e .rtld_start
WARNS?=		2
INSTALLFLAGS=	-C -b
PRECIOUSPROG=
BINDIR=		/libexec
#SYMLINKS=	${BINDIR}/${PROG} ${LIBEXECDIR}/${PROG}

CFLAGS+=	-fpic
CFLAGS+=	-DPIC $(DEBUG)
LDFLAGS+=	-shared -Wl,-Bsymbolic
LIBADD=		c_pic

# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:69: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp9' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:69: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp9' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:69: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '$tmp9' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:77: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '_DYNAMIC' defined in (internal)
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:77: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '_DYNAMIC' defined in (internal)
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:77: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '_DYNAMIC' defined in (internal)
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:82: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '_rtld_relocate_nonplt_self' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:82: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '_rtld_relocate_nonplt_self' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:82: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '_rtld_relocate_nonplt_self' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:97: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '_rtld' defined in rtld.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:97: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '_rtld' defined in rtld.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:97: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '_rtld' defined in rtld.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:180: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp77' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:180: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp77' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:180: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '$tmp77' defined in rtld_start.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:185: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '_mips_rtld_bind' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:185: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '_mips_rtld_bind' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/mips/rtld_start.S:185: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '_mips_rtld_bind' defined in reloc.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/write.S:2: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp6' defined in write.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: /home/alr48/cheri/sources/cheribsd/libexec/rtld-cheri-elf/write.S:2: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp6' defined in write.o
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: too many errors emitted, stopping now (use -error-limit=0 to see all errors)
# LLD can't deal with the relocations in the .S files
CHERI_LLD_BROKEN=yes



.if defined(NOT_YET)
.if ${MK_SYMVER} == "yes"
VERSION_DEF=	${LIBCSRCDIR}/Versions.def
SYMBOL_MAPS=	${.CURDIR}/../rtld-elf/Symbol.map
VERSION_MAP=	Version.map
LDFLAGS+=	-Wl,--version-script=${VERSION_MAP}

${PROG}:	${VERSION_MAP}

.if exists(${.CURDIR}/${RTLD_ARCH}/Symbol.map)
SYMBOL_MAPS+=	${.CURDIR}/${RTLD_ARCH}/Symbol.map
.endif
.endif
.endif

#.sinclude "${.CURDIR}/${RTLD_ARCH}/Makefile.inc"

.PATH: ${.CURDIR}/${RTLD_ARCH}

.include <bsd.prog.mk>
.include <bsd.symver.mk>

#CFLAGS:=	${CFLAGS} -O0
