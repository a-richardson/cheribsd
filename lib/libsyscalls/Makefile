LIB=syscalls

LIBC_SRCTOP=	${.CURDIR}/../libc/

.if exists(${LIBC_SRCTOP}/${MACHINE_ARCH})
LIBC_ARCH=${MACHINE_ARCH}
.else
LIBC_ARCH=${MACHINE_CPUARCH}
.endif

SHLIB_MAJOR= 7

CFLAGS+=-I${LIBC_SRCTOP}/include -I${LIBC_SRCTOP}/../../include
CFLAGS+=-I${LIBC_SRCTOP}/${LIBC_ARCH}

# Define (empty) variables so that make doesn't give substitution
# errors if the included makefiles don't change these:
MDSRCS=
MISRCS=
MDASM=
MIASM=
NOASM=

# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp6' defined in _getlogin.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp6' defined in _getlogin.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '$tmp6' defined in _getlogin.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _getlogin.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp6' defined in _exit.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp6' defined in _exit.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '$tmp6' defined in _exit.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: _exit.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp6' defined in numa_setaffinity.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp6' defined in numa_setaffinity.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '$tmp6' defined in numa_setaffinity.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_setaffinity.S:3: can't create dynamic relocation R_MIPS_HI16 (5) against symbol '__cerror' defined in cerror.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_getaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHEST (29) against symbol '$tmp6' defined in numa_getaffinity.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: numa_getaffinity.S:3: can't create dynamic relocation R_MIPS_HIGHER (28) against symbol '$tmp6' defined in numa_getaffinity.pico
# /home/alr48/cheri/output/sdk256/bin/cheri-unknown-freebsd-ld.lld: error: too many errors emitted, stopping now (use -error-limit=0 to see all errors)
# clang-3.8: error: linker command failed with exit code 1 (use -v to see invocation)
NO_PIC=yes


.include "${LIBC_SRCTOP}/sys/Makefile.inc"

VERSION_DEF=${LIBC_SRCTOP}/Versions.def
SYMBOL_MAPS=${SYM_MAPS}
CFLAGS+= -DSYMBOL_VERSIONING

MAN=

.include <bsd.lib.mk>
