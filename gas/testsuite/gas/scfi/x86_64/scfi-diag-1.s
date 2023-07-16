# Testcase for REG_FP based CFA
# and using REG_FP as scratch.
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
# The following add causes REG_FP to become untraceable
	addq	%rax, %rbp
	.cfi_def_cfa_register 7
	pop	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo

