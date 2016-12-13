# $FreeBSD$

LIB=	cheri_support
SRCS=	cheri_invoke_cabi.S \
	cheri_system_stub.c

NEED_CHERI=	sandbox

LIBCHERI_DIR=${.CURDIR}/../libcheri
.PATH: ${LIBCHERI_DIR}/${MACHINE_ARCH}

# cheri-unknown-freebsd-ld.lld: error: lib/libcheri_support/../libcheri/mips64/cheri_invoke_cabi.S:256: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol 'cherierrno' defined in cheri_invoke_cabi.pico
# cheri-unknown-freebsd-ld.lld: error: lib/libcheri_support/../libcheri/mips64/cheri_invoke_cabi.S:256: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol 'cherierrno' defined in cheri_invoke_cabi.pico
# cheri-unknown-freebsd-ld.lld: error: lib/libcheri_support/../libcheri/mips64/cheri_invoke_cabi.S:256: can't create dynamic relocation R_MIPS_HI16 (5) against symbol 'cherierrno' defined in cheri_invoke_cabi.pico
# cheri-unknown-freebsd-ld.lld: error: lib/libcheri_support/../libcheri/mips64/cheri_invoke_cabi.S:256: can't create dynamic relocation R_MIPS_LO16 (6) against symbol 'cherierrno' defined in cheri_invoke_cabi.pico
CHERI_LLD_BROKEN=yes

.include <bsd.lib.mk>
