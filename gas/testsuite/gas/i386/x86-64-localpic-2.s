	.text
foo:
	.quad 0
	movq	foo@GOTPCREL_THUNK(%rip), %rax
