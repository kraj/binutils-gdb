## Testcase with a variety of pop.
## all pop insns valid in 64-bit mode must be processed for SCFI.
	.text
	.globl	foo
	.type	foo, @function
foo:
	popw	%fs
	popw    %gs
	popfw
	popw	-8(%r10)
	ret
.LFE0:
	.size	foo, .-foo
