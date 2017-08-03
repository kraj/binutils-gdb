	.text
	.globl _start
_start:
	movl	%gs:foo@GPREL, %eax
