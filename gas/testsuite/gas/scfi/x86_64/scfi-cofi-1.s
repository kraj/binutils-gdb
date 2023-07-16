# Testcase with a variety of "change of flow instructions"
#
# Must be run with -W so it remains warning free.
#
# This test does not have much going on wrt synthesis of CFI;
# it just aims to ensure x8_64 -> ginsn decoding must behave
# gracefully for these "change of flow instructions"
	.text
	.globl	foo
	.type	foo, @function
foo:
	.cfi_startproc
	addq    %rdx, %rax
	notrack jmp     *%rax
	call   *%r8
	jmp     *48(%rdi)
	jo      .L179
.L179:
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo

