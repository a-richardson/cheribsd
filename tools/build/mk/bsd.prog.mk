# $FreeBSD$

.include "Makefile.boot"
# .if ${HOST_OS} == "FreeBSD"
.include "../../../share/mk/bsd.prog.mk"
# .else
# .include <bsd.prog.mk>
# .endif
