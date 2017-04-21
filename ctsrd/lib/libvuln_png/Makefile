.include <src.opts.mk>

LIB=		vuln_png
LIBADD=		z
NO_PIC=		yes

.if ${MK_DEMO_VULNERABILITIES} != "no"
CFLAGS+=	-DCTSRD_BACKDOOR
.else
SRCS+=	no_vuln_stub.c
.endif

BUILDDIR=	${.CURDIR}/../../../lib/libpng
SRCDIR=		${.CURDIR}/../../../contrib/libpng

.include <${BUILDDIR}/Makefile>
