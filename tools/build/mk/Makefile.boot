# $FreeBSD$

CFLAGS+=	-I${WORLDTMP}/legacy/usr/include
DPADD+=		${WORLDTMP}/legacy/usr/lib/libegacy.a
LDADD+=		-legacy
LDFLAGS+=	-L${WORLDTMP}/legacy/usr/lib
.if ${.MAKE.OS} != "FreeBSD"
# Add various -Werror flags to catch missing function declarations
CFLAGS+=	-Werror=implicit-function-declaration -Werror=implicit-int \
		-Werror=return-type -Wundef
CFLAGS+=	-DHAVE_NBTOOL_CONFIG_H=1
CFLAGS+=	-isystem  ${SRCTOP}/tools/build/cross-build/include/common
.if ${.MAKE.OS} == "Linux"
CFLAGS+=	-isystem /usr/include/bsd -DLIBBSD_OVERLAY=1 -D_GNU_SOURCE=1
CFLAGS+=	-isystem /Users/alex/cheri/freebsd-crossbuild/include/common
CFLAGS+=	-isystem /Users/alex/cheri/freebsd-crossbuild/include/linux
CFLAGS+=	-include /Users/alex/cheri/freebsd-crossbuild/include/linux/pre-include.h
LDFLAGS+=	-lbsd
.elif ${.MAKE.OS} == "Darwin"
CFLAGS+=	-D_DARWIN_C_SOURCE=1
CFLAGS+=	-isystem ${SRCTOP}/tools/build/cross-build/include/mac
CFLAGS+=	-isystem /Users/alex/cheri/freebsd-crossbuild/include/common
CFLAGS+=	-isystem /Users/alex/cheri/freebsd-crossbuild/include/mac
CFLAGS+=	-include /Users/alex/cheri/freebsd-crossbuild/include/mac/pre-include.h
# On MacOS using a non-mac ar will fail the build
AR:=	/usr/bin/ar
RANLIB:=	/usr/bin/ranlib
NM:=	/usr/bin/nm
LORDER:=	/usr/bin/lorder
ARFLAGS:=	-cr
RANLIBFLAGS:=
.else
.error "Unsupported build OS: ${.MAKE.OS}"
.endif
.endif

# we do not want to capture dependencies referring to the above
UPDATE_DEPENDFILE= no
