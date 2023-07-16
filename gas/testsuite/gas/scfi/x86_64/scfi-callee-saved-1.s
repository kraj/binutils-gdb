	.text
	.globl	foo
	.type	foo, @function
foo:
#	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	push	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	pushq	%rbp
        .cfi_def_cfa_offset 32
        .cfi_offset 6, -32
	popq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_restore 6
	popq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popq	%rax
        .cfi_def_cfa_offset 8
	ret
#	.cfi_endproc
.LFE0:
	.size	foo, .-foo

