# Testcase for leave insn
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
	push    %rbx
	.cfi_offset 3, -24
	push    %rdi
	pop	%rdi
	pop	%rbx
	.cfi_restore 3
	leave
	.cfi_def_cfa_register 7
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo

