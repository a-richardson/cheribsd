# $FreeBSD$

SRCS+=	trivial-vdso_tc.c

MDASM=	Ovfork.S cerror.S exect.S syscall.S

.if !defined(LIBCHERI)
MDASM+=	brk.S sbrk.S
.endif

# -fno-pic is currently broken so we always need to use the PIC assembly
CFLAGS+=-DPIC

# Don't generate default code for these syscalls:
NOASM+=	vfork.o
