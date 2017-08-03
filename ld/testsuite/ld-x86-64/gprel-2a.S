	.text
	.globl get_foo
get_foo:
	movl	%gs:foo@GPREL, %eax
	ret

	.data
	.globl foo_gprel
foo_gprel:
	.long foo@GPREL

	.data
foo:
	.long 0x12345678
