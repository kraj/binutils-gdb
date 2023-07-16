# Testcase for movq instructions
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

	subq	$16,%rsp

# store rbx at %rsp; rsp = rbp - 16; rsp = CFA - 32
	movq	%rbx, (%rsp)
	.cfi_rel_offset 3, -16
# store r12 at %rsp + 8; rsp = CFA - 32
	movq	%r12, 8(%rsp)
	.cfi_rel_offset 12, -8

	call bar

	movq	(%rsp), %rbx
	.cfi_restore 3
	movq	8(%rsp), %r12
	.cfi_restore 12

	addq	$16,%rsp

	mov	%rbp, %rsp
	.cfi_def_cfa_register 7
	pop	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
	.size	foo, .-foo
