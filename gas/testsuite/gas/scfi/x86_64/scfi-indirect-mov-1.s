# An example of static stack allocation by hand
	.type foo, @function
foo:
	.cfi_startproc
	/* Allocate space for 7 registers.  */
	subq	$56,%rsp
	.cfi_adjust_cfa_offset 56
	movq	%rbx,(%rsp)
	.cfi_rel_offset 3, 0
	movq	%rbp,8(%rsp)
	.cfi_rel_offset 6, 8
	movq	%r12,16(%rsp)
	.cfi_rel_offset 12, 16
	movq	%r13,24(%rsp)
	.cfi_rel_offset 13, 24
	movq	%r14,32(%rsp)
	.cfi_rel_offset 14, 32
	movq	%r15,40(%rsp)
	.cfi_rel_offset 15, 40
	movq	%r9,48(%rsp)

	/* Setup parameter for __foo_internal.  */
	/* selfpc is the return address on the stack.  */
	movq	56(%rsp),%rsi
	/* Get frompc via the frame pointer.  */
	movq	8(%rbp),%rdi
	call __foo_internal
	/* Pop the saved registers.  Please note that `foo' has no
	   return value.  */
	movq	48(%rsp),%r9

	movq	40(%rsp),%r15
	.cfi_restore 15
	movq	32(%rsp),%r14
	.cfi_restore 14
	movq	24(%rsp),%r13
	.cfi_restore 13
	movq	16(%rsp),%r12
	.cfi_restore 12
	movq	8(%rsp),%rbp
	.cfi_restore 6
	movq	(%rsp),%rbx
	.cfi_restore 3
	addq	$56,%rsp
	.cfi_adjust_cfa_offset -56
	ret
	.cfi_endproc
	.size foo, .-foo
