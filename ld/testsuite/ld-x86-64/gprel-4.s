	.text
	.globl _start
_start:
	movl	%gs:foo@GPREL, %eax

	.data
	.globl bar_gprel
bar_gprel:
	.long bar@GPREL

foo:
	.long 0x12345678

	.section .rodata,"a",@progbits
bar:
	.long 0x12345678

