# $FreeBSD$

.PATH: ${.CURDIR}/../../include

LIB=		egacy
SRC=
INCSGROUPS=	INCS SYSINCS MACHINESYSINCS UFSINCS FFSINCS
INCS=

SYSINCSDIR=	${INCLUDEDIR}/sys
MACHINESYSINCSDIR=	${INCLUDEDIR}/machine
UFSINCSDIR=	${INCLUDEDIR}/ufs/ufs
FFSINCSDIR=	${INCLUDEDIR}/ufs/ffs

BOOTSTRAPPING?=	0

_WITH_PWCACHEDB!= grep -c pwcache_groupdb /usr/include/grp.h || true
.if ${_WITH_PWCACHEDB} == 0
.PATH: ${.CURDIR}/../../contrib/libc-pwcache
CFLAGS.pwcache.c+=	-I${.CURDIR}/../../contrib/libc-pwcache \
		-I${.CURDIR}/../../lib/libc/include
SRCS+=		pwcache.c
.endif

_WITH_STRSVIS!=	grep -c strsvis /usr/include/vis.h || true
.if ${_WITH_STRSVIS} == 0
.PATH: ${.CURDIR}/../../contrib/libc-vis
SRCS+=		vis.c
CFLAGS.vis.c+=	-I${.CURDIR}/../../contrib/libc-vis \
		-I${.CURDIR}/../../lib/libc/include
.endif

_WITH_REALLOCARRAY!= grep -c reallocarray /usr/include/stdlib.h || true
.if ${_WITH_REALLOCARRAY} == 0
.PATH: ${.CURDIR}/../../lib/libc/stdlib
INCS+=		stdlib.h
SRCS+=		reallocarray.c
CFLAGS.reallocarray.c+=	-I${.CURDIR}/../../lib/libc/include
.endif

_WITH_UTIMENS!= grep -c utimensat /usr/include/sys/stat.h || true
.if ${_WITH_UTIMENS} == 0
SYSINCS+=	stat.h
SRCS+=		futimens.c utimensat.c
.endif

.if ${.MAKE.OS} != "FreeBSD"
# don't copy stdlib.h when cross-building since it will cause
# conflicts with the host system's headers
INCS:=	${INCS:Nstdlib.h}
SYSINCS+=	${SRCTOP}/sys/sys/md5.h
SYSINCS+=	${SRCTOP}/sys/sys/sbuf.h
SYSINCS+=	${SRCTOP}/sys/sys/elf32.h
SYSINCS+=	${SRCTOP}/sys/sys/elf64.h
SYSINCS+=	${SRCTOP}/sys/sys/elf_common.h
SYSINCS+=	${SRCTOP}/sys/sys/elf_generic.h
_host_arch=${MACHINE}
.if ${_host_arch} == "x86_64"
# bmake on Linux/mac often prints that instead of amd64
_host_arch=amd64
.endif
MACHINESYSINCS+=	${SRCTOP}/sys/${_host_arch}/include/elf.h

.PATH: ${.CURDIR}/../../lib/libc/stdlib
SRCS+=	strtonum.c
.PATH: ${.CURDIR}/../../lib/libc/locale
SRCS+=	rpmatch.c

# needed for btxld:
MACHINESYSINCS+=	${SRCTOP}/sys/${_host_arch}/include/exec.h
MACHINESYSINCS+=	${SRCTOP}/sys/${_host_arch}/include/reloc.h
INCS+=	${SRCTOP}/include/a.out.h
SYSINCS+=	${SRCTOP}/sys/sys/imgact_aout.h

# For mkscrfil.c:
SYSINCS+=	${SRCTOP}/sys/sys/consio.h ${SRCTOP}/sys/sys/ioccom.h
# for gencat:
INCS+=	${SRCTOP}/include/nl_types.h

#for makefs:
UFSINCS+=	${SRCTOP}/sys/ufs/ufs/dinode.h
UFSINCS+=	${SRCTOP}/sys/ufs/ufs/dir.h
FFSINCS+=	${SRCTOP}/sys/ufs/ffs/fs.h

# for tzsetup:
SRCS+=	fake_sysctl.c

.endif

.if empty(SRCS)
SRCS=		dummy.c
.endif

.if defined(CROSS_BUILD_TESTING)
SUBDIR=		cross-build
.endif

.include <bsd.lib.mk>
