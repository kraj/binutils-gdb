        .section        .rodata
	.type	simd_cmp_op, @object
	.size	simd_cmp_op, 8
simd_cmp_op:
	.long	2
	.zero	4

# Testcase for add instruction.
# add reg, reg instruction
	.text
	.globl	foo
	.type	foo, @function
foo:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq    %rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	.cfi_offset 12, -24
	mov	%rsp, %r12
# Stack manipulation is permitted if the base register for
# tracking CFA has been changed to FP.
	addq    %rdx, %rsp
	addq	%rsp, %rax
# Other kind of add instructions should not error out in the
# x86_64 -> ginsn translator
	addq    $simd_cmp_op+8, %rdx
	mov	%r12, %rsp
# Popping a callee-saved register.
# RSP must be traceable.
	pop     %r12
	.cfi_restore 12
	leave
	.cfi_def_cfa_register 7
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo

