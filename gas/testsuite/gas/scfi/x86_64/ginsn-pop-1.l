GAS LISTING .*


   1              	## Testcase with a variety of pop.
   2              	## all pop insns valid in 64-bit mode must be processed for SCFI.
   3              		.text
   4              		.globl	foo
   5              		.type	foo, @function
   5              	ginsn: SYM FUNC_BEGIN
   6              	foo:
   6              	ginsn: SYM foo
   7 0000 660FA1   		popw	%fs
   7              	ginsn: LOAD \[%r7\+0\], %r54
   7              	ginsn: ADD %r7, 2, %r7
   8 0003 660FA9   		popw    %gs
   8              	ginsn: LOAD \[%r7\+0\], %r55
   8              	ginsn: ADD %r7, 2, %r7
   9 0006 669D     		popfw
   9              	ginsn: LOAD \[%r7\+0\], %r49
   9              	ginsn: ADD %r7, 2, %r7
  10 0008 66418F42 		popw	-8\(%r10\)
  10      F8
  10              	ginsn: LOAD \[%r7\+0\], \[%r10\+0\]
  10              	ginsn: ADD %r7, 2, %r7
  11 000d C3       		ret
  11              	ginsn: RET
  12              	.LFE0:
  12              	ginsn: SYM .LFE0
  13              		.size	foo, .-foo
  13              	ginsn: SYM FUNC_END
