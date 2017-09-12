# $FreeBSD$

.include <host-target.mk>

.if ${HOST_OS} == "FreeBSD"
CFLAGS+=	-I${WORLDTMP}/legacy/usr/include
DPADD+=		${WORLDTMP}/legacy/usr/lib/libegacy.a
LDADD+=		-legacy
LDFLAGS+=	-L${WORLDTMP}/legacy/usr/lib
.endif

# we do not want to capture dependencies referring to the above
UPDATE_DEPENDFILE= no
