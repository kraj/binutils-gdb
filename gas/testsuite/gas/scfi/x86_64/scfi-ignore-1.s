	.text
	.globl	foo
	.type	foo, @function
foo:
	.cfi_startproc
	pushq	%rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo

