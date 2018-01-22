# $FreeBSD$

CFLAGS+=	-I${WORLDTMP}/legacy/usr/include
DPADD+=		${WORLDTMP}/legacy/usr/lib/libegacy.a
LDADD+=		-legacy
LDFLAGS+=	-L${WORLDTMP}/legacy/usr/lib
.if ${.MAKE.OS} != "FreeBSD"
# On MacOS using a non-mac ar will fail the build, similarly on Linux using
# nm may not work as expected if the nm for the target architecture comes in
# $PATH before a nm that supports the host architecture.
# To ensure that host binary compile as expected we use the tools from /usr/bin.
AR:=	/usr/bin/ar
RANLIB:=	/usr/bin/ranlib
NM:=	/usr/bin/nm
LORDER:=	/usr/bin/lorder
TSORT:=	/usr/bin/tsort

# Add various -Werror flags to catch missing function declarations
CFLAGS+=	-Werror=implicit-function-declaration -Werror=implicit-int \
		-Werror=return-type -Wundef
CFLAGS+=	-DHAVE_NBTOOL_CONFIG_H=1
CFLAGS+=	-D__BSD_VISIBLE=1
CFLAGS+=	-isystem ${SRCTOP}/tools/build/cross-build/include/common

# ensure that we use the FreeBSD versions of libdb:
FREEBSD_LIBDB:=	-ldb-freebsd

.if ${.MAKE.OS} == "Linux"
CFLAGS+=	-isystem ${SRCTOP}/tools/build/cross-build/include/linux
CFLAGS+=	-isystem /usr/include/bsd -DLIBBSD_OVERLAY=1 -D_GNU_SOURCE=1
CFLAGS+=	-std=c99
LDFLAGS+=	-lbsd
# Needed for sem_init, etc. on Linux (used by usr.bin/sort)
LDFLAGS+=	-pthread

# Linux tsort doesn't understand the -q flag
TSORTFLAGS:=
.elif ${.MAKE.OS} == "Darwin"
CFLAGS+=	-D_DARWIN_C_SOURCE=1
CFLAGS+=	-I ${SRCTOP}/tools/build/cross-build/include/mac
# The macOS ar and ranlib don't understand all the flags supported by the
# FreeBSD and Linux ar/ranlib
ARFLAGS:=	-cr
RANLIBFLAGS:=

# to get libarchive (needed for elftoolchain)
# MacOS ships /usr/lib/libarchive.dylib but doesn't have the headers
CFLAGS+=	-I/usr/local/opt/libarchive/include
LDFLAGS+=	-L/usr/local/opt/libarchive/lib

.else
.error "Unsupported build OS: ${.MAKE.OS}"
.endif

# b64_pton and b64_ntop is in libresolv on MacOS and Linux:
# TODO: only needed for uuencode and uudecode
LDFLAGS+=-lresolv
.endif

# we do not want to capture dependencies referring to the above
UPDATE_DEPENDFILE= no
