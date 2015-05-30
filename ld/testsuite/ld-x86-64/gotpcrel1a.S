	.text
	.globl	main
	.type	main, @function
main:
	subq	$8, %rsp
	call   *foo@GOTPCREL(%rip)
	call   *bar@GOTPCREL(%rip)
	call   *plt@GOTPCREL(%rip)
	xorl	%edi, %edi
	addq	$8, %rsp
	jmp	*myexit@GOTPCREL(%rip)
	.size	main, .-main
