# Testcase for switching between sp/fp based CFA.
	.text
	.globl	foo
	.type	foo, @function
foo:
        .cfi_startproc
        pushq   %r14
        .cfi_def_cfa_offset 16
        .cfi_offset 14, -16
        pushq   %r13
        .cfi_def_cfa_offset 24
        .cfi_offset 13, -24
        pushq   %r12
        .cfi_def_cfa_offset 32
        .cfi_offset 12, -32
        pushq   %rbp
        .cfi_def_cfa_offset 40
        .cfi_offset 6, -40
        pushq   %rbx
        .cfi_def_cfa_offset 48
        .cfi_offset 3, -48
        movq    %rdi, %rbx
        subq    $32, %rsp
        .cfi_def_cfa_offset 80
# This mov does not switch CFA tracking to REG_FP, because there has already
# been stack usage between here and the push %rbp
        movq    %rsp, %rbp
        xorl    %eax, %eax
        addq    $32, %rsp
        .cfi_def_cfa_offset 48
        popq    %rbx
	.cfi_restore 3
        .cfi_def_cfa_offset 40
        popq    %rbp
	.cfi_restore 6
        .cfi_def_cfa_offset 32
        popq    %r12
	.cfi_restore 12
        .cfi_def_cfa_offset 24
        popq    %r13
	.cfi_restore 13
        .cfi_def_cfa_offset 16
        popq    %r14
	.cfi_restore 14
        .cfi_def_cfa_offset 8
        ret
	.cfi_endproc
	.size	foo, .-foo

