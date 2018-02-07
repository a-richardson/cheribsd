# $FreeBSD$

.PATH: ${.CURDIR}/../../include

LIB=		egacy
SRC=
INCSGROUPS=	INCS SYSINCS MACHINESYSINCS UFSINCS FFSINCS X86INCS
INCS=

SYSINCSDIR=	${INCLUDEDIR}/sys
MACHINESYSINCSDIR=	${INCLUDEDIR}/machine
UFSINCSDIR=	${INCLUDEDIR}/ufs/ufs
FFSINCSDIR=	${INCLUDEDIR}/ufs/ffs
X86INCSDIR=	${INCLUDEDIR}/x86

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
.if ${_host_arch} == "amd64" || ${_host_arch} == "i386"
X86INCS+=	${SRCTOP}/sys/x86/include/elf.h
.endif

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

# for vtfontcvt:
SYSINCS+=	${SRCTOP}/sys/sys/fnv_hash.h

# opensolaris stuff
INCS+=	${SRCTOP}/include/elf.h

# We need to build a FreeBSD compatible libdb for tools like tsort, etc.
# I believe the db routines shipped with MacOS are compatible but on Linux they
# definitelty aren't. To avoid any surprises let's just always build it when
# we are crossbuilding.
SUBDIR+=	cross-build/libdb_freebsd
.endif

.if empty(SRCS)
SRCS=		dummy.c
.endif

.if defined(CROSS_BUILD_TESTING)
SUBDIR=		cross-build
.endif


# When building on Linux/Mac we want to run the build with only ${WORLDTMP} in
# $PATH to ensure we don't run tools that are incompatible with the FreeBSD
# versions. In order to do this we symlink all the basic tools that are known
# to be compatible into ${WORLDTMP} and build all others from the FreeBSD
# sources during the bootstrap-tools stage
.if ${.MAKE.OS} != "FreeBSD"
# basic commands (used only with known flags)
_host_tools_to_symlink=	basename chmod chown cmp comm cp date dirname echo env \
	false find fmt gzip head hostname id ln ls mkdir mv nice patch rm realpath \
	sleep tee touch tr true uname uniq wc which
# needed for the fake sysctl script
_host_tools_to_symlink+=python
# should we bootstrap this instead?
_host_tools_to_symlink+=gperf
# needed by bootloader
_host_tools_to_symlink+=bzip2 dd

_make_abs!=	which "${MAKE}"
_host_abs_tools_to_symlink=	${_make_abs}:make ${_make_abs}:bmake
.if ${.MAKE.OS} == "Darwin"
# /usr/bin/cpp may invoke xcrun:
_host_tools_to_symlink+=xcrun
# the m4 in /usr/bin does not accept the flags necessary to bootstrap lex+m4.
# Therefore we need to add this symlink and then have the bootstrap-tools phase
# overwrite it with the correct version. This requires m4 from homebrew.
_host_abs_tools_to_symlink+=	/usr/local/opt/m4/bin/m4:m4
.endif
# On Ubuntu /bin/sh is dash which is totally useless. Let's just link bash
# as the build sh since that will work fine. Also on MacOS /bin/sh doesn't
# support the -e flag to echo so let's use the builtin from bash
_host_abs_tools_to_symlink+=	/bin/bash:sh
.endif

host-symlinks:
.if ${.MAKE.OS} != "FreeBSD"
	@echo "Linking host tools into ${DESTDIR}/usr/bin"
.for _tool in ${_host_tools_to_symlink}
	@if [ ! -e "${DESTDIR}/usr/bin/${_tool}" ]; then \
		source_path=`which ${_tool}`; \
		if [ ! -e "$${source_path}" ] ; then \
			echo "Cannot find host tool '${_tool}'"; false; \
		fi; \
		ln -sfnv "$${source_path}" "${DESTDIR}/usr/bin/${_tool}"; \
	fi
.endfor
.for _tool in ${_host_abs_tools_to_symlink}
	@source_path="${_tool:S/:/ /:[1]}"; \
	target_path="${DESTDIR}/usr/bin/${_tool:S/:/ /:[2]}"; \
	if [ ! -e "$${target_path}" ] ; then \
		if [ ! -e "$${source_path}" ] ; then \
			echo "Host tool '${src_path}' is missing"; false; \
		fi; \
		ln -sfnv "$${source_path}" "$${target_path}"; \
	fi
.endfor
.endif # ${.MAKE.OS} != "FreeBSD"

# Create all the directories that are needed during the legacy, bootstrap-tools
# and cross-tools stages. We do this here using mkdir since mtree may not exist
# yet (this happens if we are crossbuilding from Linux/Mac).
installdirs:
.for _dir in bin usr/bin usr/sbin usr/lib usr/include
	mkdir -p "${DESTDIR}/${_dir}"
.endfor
.for _group in ${INCSGROUPS:NINCS}
	mkdir -p "${DESTDIR}/${${_group}DIR}"
.endfor

.include <bsd.lib.mk>
