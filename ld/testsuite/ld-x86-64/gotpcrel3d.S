	.text
	.globl	bar
	.type	bar, @function
bar:
	leaq	__FUNCTION__.2215(%rip), %rdi
	movq	puts@GOTPCREL_THUNK(%rip), %r11
	bnd jmp	__x86_indirect_thunk_bnd_r11
	.size	bar, .-bar
	.globl	plt
	.type	plt, @function
plt:
	leaq	__FUNCTION__.2219(%rip), %rdi
	subq	$8, %rsp
	movq	puts@GOTPCREL_THUNK(%rip), %r11
	bnd call	__x86_indirect_thunk_bnd_r11
	leaq	__FUNCTION__.2219(%rip), %rdi
	addq	$8, %rsp
	movq	puts@GOTPCREL_THUNK(%rip), %r11
	bnd jmp	__x86_indirect_thunk_bnd_r11
	.size	plt, .-plt
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
	.section	.rodata
	.type	__FUNCTION__.2219, @object
	.size	__FUNCTION__.2219, 4
__FUNCTION__.2219:
	.string	"plt"
	.type	__FUNCTION__.2215, @object
	.size	__FUNCTION__.2215, 4
__FUNCTION__.2215:
	.string	"bar"
