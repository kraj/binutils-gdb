# Testcase for a diagnostic around assymetrical restore
.type	foo, @function
foo:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	addq	$24, %rsp
# Note that the order of r12 and rbx restore does not match
# order of the corresponding save(s).
# The SCFI machinery warns the user.
	popq	%r12
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	foo, .-foo
