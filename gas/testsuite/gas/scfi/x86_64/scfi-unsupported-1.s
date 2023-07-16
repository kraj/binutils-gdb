# Testcase run with --m32 (Not supported).
	.text
	.globl	foo
	.type	foo, @function
foo:
	pushq	%rbp
	ret
.LFE0:
	.size	foo, .-foo
