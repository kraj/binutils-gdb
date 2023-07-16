## Testcase with a variety of add.
## Some add insns valid in 64-bit mode may not be processed for SCFI.
	.text
	.globl	foo
	.type	foo, @function
foo:
	push	%rsp
	movq	%rsp, %rbp

	addq	%rax, symbol
        add     symbol, %eax

        add	(%eax), %esp
        add	%esp, (,%eax)

        addq	%rax, %rbx
	add	%eax, %ebx

        addq    $1, -16(%rbp)

        add	(,%eax), %esp
        add	%esp, (,%eax)

	ret
.LFE0:
	.size	foo, .-foo
