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
CFLAGS+=	-I  ${SRCTOP}/tools/build/cross-build/include/common

.if ${.MAKE.OS} == "Linux"
CFLAGS+=	-isystem ${SRCTOP}/tools/build/cross-build/include/linux
CFLAGS+=	-isystem /usr/include/bsd -DLIBBSD_OVERLAY=1 -D_GNU_SOURCE=1
CFLAGS+=	-std=c99
LDFLAGS+=	-lbsd
# Linux tsort doesn't understand the -q flag
TSORTFLAGS:=
.elif ${.MAKE.OS} == "Darwin"
CFLAGS+=	-D_DARWIN_C_SOURCE=1
CFLAGS+=	-I ${SRCTOP}/tools/build/cross-build/include/mac
# The macOS ar and ranlib don't understand all the flags supported by the
# FreeBSD and Linux ar/ranlib
ARFLAGS:=	-cr
RANLIBFLAGS:=
.else
.error "Unsupported build OS: ${.MAKE.OS}"
.endif
.endif

# we do not want to capture dependencies referring to the above
UPDATE_DEPENDFILE= no
