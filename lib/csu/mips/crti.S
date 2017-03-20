#include <machine/asm.h>
__FBSDID("$FreeBSD$");

/*
 * XXXAR: do we need this with clang?
 * Tag_GNU_MIPS_ABI_FP (4)
 * The floating-point ABI used by this object file. The value will be:
 * 0 for files not affected by the floating-point ABI.
 * XXXAM: can be omitted with clang
 */
#ifndef __clang__
	.gnu_attribute 4, 0
#endif
	.section .init,"ax",%progbits
	.align 4
	.globl	_init
	.type	_init,%function
_init:
	.set noreorder
#if defined(__ABICALLS__) && (defined(__mips_o32) || defined(__mips_o64))
	SETUP_GP
#endif
	PTR_ADDU sp, sp, -CALLFRAME_SIZ
	REG_S	ra, CALLFRAME_RA(sp)
#if defined(__ABICALLS__)
#if defined(__mips_o32) || defined(__mips_o64)
	SAVE_GP(CALLFRAME_GP)
#else
	SETUP_GP64(CALLFRAME_GP, _init)
#endif
#else /* __ABICALLS__ */
#if defined(__mips_n32) || defined(__mips_n64)
	REG_S	gp, CALLFRAME_GP(sp)
#endif
#endif
	.set reorder

	.section .fini,"ax",%progbits
	.align 4
	.globl	_fini
	.type	_fini,%function
_fini:
	.set noreorder
#if defined(__ABICALLS__) && (defined(__mips_o32) || defined(__mips_o64))
	SETUP_GP
#endif
	PTR_ADDU sp, sp, -CALLFRAME_SIZ
	REG_S	ra, CALLFRAME_RA(sp)
#if defined(__ABICALLS__)
#if defined(__mips_o32) || defined(__mips_o64)
	SAVE_GP(CALLFRAME_GP)
#else
	SETUP_GP64(CALLFRAME_GP, _fini)
#endif
#else /* __ABICALLS__ */
#if defined(__mips_n32) || defined(__mips_n64)
	REG_S	gp, CALLFRAME_GP(sp)
#endif
#endif
	.set reorder
