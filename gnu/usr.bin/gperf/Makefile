# $FreeBSD$

.include <bsd.own.mk>
GPERFDIR=	${.CURDIR}/../../../contrib/gperf

.PATH: ${GPERFDIR}/src ${GPERFDIR}/lib ${GPERFDIR}/doc

PROG_CXX=	gperf
SRCS=	bool-array.cc hash-table.cc input.cc keyword-list.cc keyword.cc \
	main.cc options.cc output.cc positions.cc search.cc version.cc \
	getline.cc hash.cc
WARNS=	1
MAN=	gperf.1 gperf.7
# This is the first target built by `make xdev` so we need to create the debug directory if MK_DEBUG_FILES is set
DEBUGMKDIR=	yes

CXXFLAGS+=	-I${GPERFDIR}/lib -I${.CURDIR}

.include <bsd.prog.mk>
