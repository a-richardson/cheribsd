# $FreeBSD$
.if !empty(CROSSBUILD)
# OS X doesn't want to build static binaries and Linux distributions don't
# always have the static libraries/crt objects installed
NO_SHARED:=no
.endif
.include "../../../share/mk/bsd.prog.mk"
.include "Makefile.boot"
