# $FreeBSD$

.include <src.opts.mk>

SUBDIR=writefile

.if ${MK_FILE} != "no"
SUBDIR+=	browser
.endif

# XXX: The latter two should be buildable without cheri but aren't yet.
.if ${MK_CHERI} != "no"
SUBDIR+=	cheripoint \
		pictview \
		pngsb
.endif

.include <bsd.subdir.mk>
