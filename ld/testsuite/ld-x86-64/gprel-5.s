	.text
	.globl _start
_start:
	movl	%gs:foo@GPREL, %eax

	.data
	.globl bar_gprel
bar_gprel:
	.long bar@GPREL

	.globl foo
foo:
	.long 0x12345678

	.section .rodata,"a",@progbits
	.globl bar
bar:
	.long 0x12345678

