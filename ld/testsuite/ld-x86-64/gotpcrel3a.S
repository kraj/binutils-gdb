	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	pushq	%r12
	subq	$8, %rsp
	movq	foo@GOTPCREL_THUNK(%rip), %rax
	bnd call	__x86_indirect_thunk_bnd_rax
	movq	bar@GOTPCREL_THUNK(%rip), %rbp
	bnd call	__x86_indirect_thunk_bnd_rbp
	movq	plt@GOTPCREL_THUNK(%rip), %r11
	bnd call	__x86_indirect_thunk_bnd_r11
	movq	foo@GOTPCREL_THUNK(%rip), %rax
	bnd call	__x86_indirect_thunk_bnd_rax
	bnd call	__x86_indirect_thunk_bnd_rbp
	movq	plt@GOTPCREL_THUNK(%rip), %rdx
	bnd call	__x86_indirect_thunk_bnd_rdx
	xorl	%edi, %edi
	popq	%r12
	popq	%rbp
	addq	$8, %rsp
	movq	myexit@GOTPCREL_THUNK(%rip), %r11
	bnd jmp	__x86_indirect_thunk_bnd_r11
	bnd ret
	.size	main, .-main
	.section	.text.__x86_indirect_thunk_bnd_rax,"axG",@progbits,__x86_indirect_thunk_bnd_r11,comdat
	.globl	__x86_indirect_thunk_bnd_rax
	.hidden	__x86_indirect_thunk_bnd_rax
	.type	__x86_indirect_thunk_bnd_rax, @function
__x86_indirect_thunk_bnd_rax:
	bnd call	.LIND7
.LIND6:
	pause
	lfence
	jmp	.LIND6
.LIND7:
	mov	%rax, (%rsp)
	bnd ret
	.section	.text.__x86_indirect_thunk_bnd_rdx,"axG",@progbits,__x86_indirect_thunk_bnd_r11,comdat
	.globl	__x86_indirect_thunk_bnd_rdx
	.hidden	__x86_indirect_thunk_bnd_rdx
	.type	__x86_indirect_thunk_bnd_rdx, @function
__x86_indirect_thunk_bnd_rdx:
	bnd call	.LIND3
.LIND2:
	pause
	lfence
	jmp	.LIND2
.LIND3:
	mov	%rdx, (%rsp)
	bnd ret
	.section	.text.__x86_indirect_thunk_bnd_rbp,"axG",@progbits,__x86_indirect_thunk_bnd_r11,comdat
	.globl	__x86_indirect_thunk_bnd_rbp
	.hidden	__x86_indirect_thunk_bnd_rbp
	.type	__x86_indirect_thunk_bnd_rbp, @function
__x86_indirect_thunk_bnd_rbp:
	bnd call	.LIND5
.LIND4:
	pause
	lfence
	jmp	.LIND4
.LIND5:
	mov	%rbp, (%rsp)
	bnd ret
	.section	.text.__x86_indirect_thunk_bnd_r11,"axG",@progbits,__x86_indirect_thunk_bnd_r11,comdat
	.globl	__x86_indirect_thunk_bnd_r11
	.hidden	__x86_indirect_thunk_bnd_r11
	.type	__x86_indirect_thunk_bnd_r11, @function
__x86_indirect_thunk_bnd_r11:
	bnd call	.LIND1
.LIND0:
	pause
	lfence
	jmp	.LIND0
.LIND1:
	mov	%r11, (%rsp)
	bnd ret
