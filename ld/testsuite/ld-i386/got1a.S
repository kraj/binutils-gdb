	.text
	.globl	main
	.type	main, @function
main:
	subl	$12, %esp
	call	*foo@GOT
	call	*bar@GOT
	call	*plt@GOT
	subl	$12, %esp
	pushl	$0
	jmp	*myexit@GOT
	.size	main, .-main
