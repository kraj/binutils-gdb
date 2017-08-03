	.text
_start:
	movl	%fs:foo@GPREL(%rip), %eax
	movl	%fs:foo@GPREL(%rax), %eax
	movl	%ds:foo@GPREL(%rax, %rcx, 2), %eax
	movl	foo@GPREL(%rip), %eax
	movl	foo@GPREL(%rax), %eax
	movl	foo@GPREL, %eax
