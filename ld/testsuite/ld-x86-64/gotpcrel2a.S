	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	pushq	%r12
	subq	$8, %rsp
	movq	foo@GOTPCREL_THUNK(%rip), %rax
	call	__x86_indirect_thunk_rax
	movq	bar@GOTPCREL_THUNK(%rip), %rbp
	call	__x86_indirect_thunk_rbp
	movq	plt@GOTPCREL_THUNK(%rip), %r11
	call	__x86_indirect_thunk_r11
	movq	foo@GOTPCREL_THUNK(%rip), %rax
	call	__x86_indirect_thunk_rax
	call	__x86_indirect_thunk_rbp
	movq	plt@GOTPCREL_THUNK(%rip), %rdx
	call	__x86_indirect_thunk_rdx
	xorl	%edi, %edi
	popq	%r12
	popq	%rbp
	addq	$8, %rsp
	movq	myexit@GOTPCREL_THUNK(%rip), %r11
	jmp	__x86_indirect_thunk_r11
	ret
	.size	main, .-main
	.section	.text.__x86_indirect_thunk_rax,"axG",@progbits,__x86_indirect_thunk_r11,comdat
	.globl	__x86_indirect_thunk_rax
	.hidden	__x86_indirect_thunk_rax
	.type	__x86_indirect_thunk_rax, @function
__x86_indirect_thunk_rax:
	call	.LIND7
.LIND6:
	pause
	lfence
	jmp	.LIND6
.LIND7:
	mov	%rax, (%rsp)
	ret
	.section	.text.__x86_indirect_thunk_rdx,"axG",@progbits,__x86_indirect_thunk_r11,comdat
	.globl	__x86_indirect_thunk_rdx
	.hidden	__x86_indirect_thunk_rdx
	.type	__x86_indirect_thunk_rdx, @function
__x86_indirect_thunk_rdx:
	call	.LIND3
.LIND2:
	pause
	lfence
	jmp	.LIND2
.LIND3:
	mov	%rdx, (%rsp)
	ret
	.section	.text.__x86_indirect_thunk_rbp,"axG",@progbits,__x86_indirect_thunk_r11,comdat
	.globl	__x86_indirect_thunk_rbp
	.hidden	__x86_indirect_thunk_rbp
	.type	__x86_indirect_thunk_rbp, @function
__x86_indirect_thunk_rbp:
	call	.LIND5
.LIND4:
	pause
	lfence
	jmp	.LIND4
.LIND5:
	mov	%rbp, (%rsp)
	ret
	.section	.text.__x86_indirect_thunk_r11,"axG",@progbits,__x86_indirect_thunk_r11,comdat
	.globl	__x86_indirect_thunk_r11
	.hidden	__x86_indirect_thunk_r11
	.type	__x86_indirect_thunk_r11, @function
__x86_indirect_thunk_r11:
	call	.LIND1
.LIND0:
	pause
	lfence
	jmp	.LIND0
.LIND1:
	mov	%r11, (%rsp)
	ret
