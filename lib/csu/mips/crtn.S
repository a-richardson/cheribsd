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
	.set noreorder
#if defined(__ABICALLS__) && (defined(__mips_n32) || defined(__mips_n64))
	REG_L	gp, CALLFRAME_GP(sp)
#endif
	REG_L	ra, CALLFRAME_RA(sp)
	jr	ra
	PTR_ADDU sp, sp, CALLFRAME_SIZ
	.set reorder

	.section .fini,"ax",%progbits
	.align 4
	.set noreorder
#if defined(__ABICALLS__) && (defined(__mips_n32) || defined(__mips_n64))
	REG_L	gp, CALLFRAME_GP(sp)
#endif
	REG_L	ra, CALLFRAME_RA(sp)
	jr	ra
	PTR_ADDU sp, sp, CALLFRAME_SIZ
	.set reorder
