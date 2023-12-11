# Testcase for a variety of unconditional branches
	.text
	.align	2
	.global	foo
	.type	foo, %function
foo:
	.cfi_startproc
	bl      dump_bt
	b	.L3
# Because of these indirect branches, SCFI will bail out
	br      x17
.L3:
	blr     x3
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
