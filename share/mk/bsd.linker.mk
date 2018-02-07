# $FreeBSD$

# Setup variables for the linker.
#
# LINKER_TYPE is the major type of linker. Currently binutils and lld support
# automatic detection.
#
# LINKER_VERSION is a numeric constant equal to:
#     major * 10000 + minor * 100 + tiny
# It too can be overridden on the command line.
#
# LINKER_FEATURES may contain one or more of the following, based on
# linker support for that feature:
#
# - build-id : support for generating a Build-ID note
#
# These variables with an X_ prefix will also be provided if XLD is set.
#
# This file may be included multiple times, but only has effect the first time.
#

.if !target(__<bsd.linker.mk>__)
__<bsd.linker.mk>__:

.for ld X_ in LD $${_empty_var_} XLD X_
.if ${ld} == "LD" || !empty(XLD)
# Try to import LINKER_TYPE and LINKER_VERSION from parent make.
# The value is only used/exported for the same environment that impacts
# LD and LINKER_* settings here.
_exported_vars=	${X_}LINKER_TYPE ${X_}LINKER_VERSION ${X_}LINKER_FEATURES
${X_}_ld_hash=	${${ld}}${MACHINE}${PATH}
${X_}_ld_hash:=	${${X_}_ld_hash:hash}
# Only import if none of the vars are set somehow else.
_can_export=	yes
.for var in ${_exported_vars}
.if defined(${var})
_can_export=	no
.endif
.endfor
.if ${_can_export} == yes
.for var in ${_exported_vars}
.if defined(${var}.${${X_}_ld_hash})
${var}=	${${var}.${${X_}_ld_hash}}
.endif
.endfor
.endif

.if ${ld} == "LD" || (${ld} == "XLD" && ${XLD} != ${LD})
.if !defined(${X_}LINKER_TYPE) || !defined(${X_}LINKER_VERSION)
_ld_version!=	(${${ld}} --version 2>/dev/null || echo none) | head -n 1
.if ${_ld_version} == "none"
# The MacOS /usr/bin/ld doesn't accept --version but -v works.
# The final test -eq 141 is there in order to make this work even when the bmake
# shell is set to bash -o pipefail
_ld_version!=	(${${ld}} -v 2>&1 || echo none) | head -n 1 || test $$? -eq 141
.if ${_ld_version} == "none"
.warning Unable to determine linker type from ${ld}=${${ld}}
.endif
.endif
.if ${_ld_version:[1..2]} == "GNU ld"
${X_}LINKER_TYPE=	bfd
_v=	${_ld_version:M[1-9].[0-9]*:[1]}
.elif ${_ld_version:[1]} == "LLD"
${X_}LINKER_TYPE=	lld
_v=	${_ld_version:[2]}
.elif ${_ld_version:[1]} == "@(\#)PROGRAM:ld"
# bootstrap linker on MacOS
${X_}LINKER_TYPE=	mac
_v=	${_ld_version:[2]:S/PROJECT:ld64-//}
# Convert version 305 to 3.0.5 so that the echo + awk below works
_v:=	${_v:C/([0-9])([0-9])/\1.\2./}
# .info "MacOS linker version is ${_v}"
.else
.warning Unknown linker from ${ld}=${${ld}}: ${_ld_version}, defaulting to bfd
${X_}LINKER_TYPE=	bfd
_v=	2.17.50
.endif
${X_}LINKER_VERSION!=	echo "${_v:M[1-9].[0-9]*}" | \
			  awk -F. '{print $$1 * 10000 + $$2 * 100 + $$3;}'
.undef _ld_version
.undef _v
${X_}LINKER_FEATURES=
.if ${${X_}LINKER_TYPE} != "bfd" || ${${X_}LINKER_VERSION} > 21750
${X_}LINKER_FEATURES+=	build-id
.endif
.if ${${X_}LINKER_TYPE} != "lld" || ${${X_}LINKER_VERSION} >= 50000
${X_}LINKER_FEATURES+=	filter
.endif
.endif
.else
# Use LD's values
X_LINKER_TYPE=		${LINKER_TYPE}
X_LINKER_VERSION=	${LINKER_VERSION}
X_LINKER_FEATURES=	${LINKER_FEATURES}
.endif	# ${ld} == "LD" || (${ld} == "XLD" && ${XLD} != ${LD})

# Export the values so sub-makes don't have to look them up again, using the
# hash key computed above.
.for var in ${_exported_vars}
${var}.${${X_}_ld_hash}:=	${${var}}
.export-env ${var}.${${X_}_ld_hash}
.undef ${var}.${${X_}_ld_hash}
.endfor

.endif	# ${ld} == "LD" || !empty(XLD)
.endfor	# .for ld in LD XLD


.endif	# !target(__<bsd.linker.mk>__)
