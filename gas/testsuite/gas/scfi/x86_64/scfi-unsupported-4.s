	.type	foo, @function
foo:
.LFB16:
#	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq    %rsp, %rbp
# The following stack manipulation is OK to do, as CFA tracking
# REG_FP based.
	movq	%rax, %rsp
# But...not quite, if there is a follow up usage of stack
# like a register save of a callee-saved register.
	push	%rbx
	mov	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa 7, 8
	.cfi_restore 6
	ret
#	.cfi_endproc
.LFE16:
	.size	foo, .-foo

