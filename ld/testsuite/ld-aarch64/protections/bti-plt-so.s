	.global	foo
	.type	foo, %function
foo:
	sub	sp, sp, #16
	mov	w0, 9
	str	w0, [sp, 12]
	ldr	w0, [sp, 12]
	add	w0, w0, 4
	str	w0, [sp, 12]
	nop
	add	sp, sp, 16
	ret
	.size	foo, .-foo
	.global	bar
	.type	bar, %function
bar:
	sub	sp, sp, #16
	mov	w0, 9
	str	w0, [sp, 12]
	ldr	w0, [sp, 12]
	add	w0, w0, 4
	str	w0, [sp, 12]
	nop
	add	sp, sp, 16
	ret
	.size	bar, .-bar

.include "gnu-note-properties-selectable-merged.inc"
