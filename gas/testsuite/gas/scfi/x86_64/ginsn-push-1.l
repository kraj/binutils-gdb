GAS LISTING .*


   1              	## Testcase with a variety of push.
   2              	## all push insns valid in 64-bit mode must be processed for SCFI.
   3              		.text
   4              		.globl	foo
   5              		.type	foo, @function
   5              	ginsn: SYM FUNC_BEGIN
   6              	foo:
   6              	ginsn: SYM foo
   7 0000 660FA0   		pushw	%fs
   7              	ginsn: SUB %r7, 2, %r7
   7              	ginsn: STORE %r54, \[%r7\+0\]
   8 0003 660FA8   		pushw	%gs
   8              	ginsn: SUB %r7, 2, %r7
   8              	ginsn: STORE %r55, \[%r7\+0\]
   9 0006 666A28   		pushw	\$40
   9              	ginsn: SUB %r7, 2, %r7
   9              	ginsn: STORE 0, \[%r7\+0\]
  10 0009 6641FF72 		pushw	-8\(%r10\)
  10      F8
  10              	ginsn: SUB %r7, 2, %r7
  10              	ginsn: STORE \[%r10\+0\], \[%r7\+0\]
  11 000e 669C     		pushfw
  11              	ginsn: SUB %r7, 2, %r7
  11              	ginsn: STORE 0, \[%r7\+0\]
  12 0010 C3       		ret
  12              	ginsn: RET
  13              	.LFE0:
  13              	ginsn: SYM .LFE0
  14              		.size	foo, .-foo
  14              	ginsn: SYM FUNC_END
