	.text
	.align	2
	.global	foo
	.type	foo, %function
foo:
	.cfi_startproc
	bge     .L10
	ble     .L10
	bne     .L10
.L10:
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
