# Testcase for CFG creation of ginsns
# This testcase has no return instruction at the end.
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	foo
	shrl	$31, %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	exit
	.cfi_endproc
.LFE7:
	.size	main, .-main
