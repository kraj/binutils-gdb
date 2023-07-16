# Testcase for sub reg, reg instruction.
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
	subq    %rax, %rsp
# SCFI: Stack-pointer manipulation after switching
# to RBP based tracking is OK.
	addq	%rax, %rsp
	leave
	.cfi_def_cfa_register 7
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
