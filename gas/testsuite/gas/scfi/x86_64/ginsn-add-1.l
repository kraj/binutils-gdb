GAS LISTING .*


   1              	## Testcase with a variety of add.
   2              	## Some add insns valid in 64-bit mode may not be processed for SCFI.
   3              		.text
   4              		.globl	foo
   5              		.type	foo, @function
   5              	ginsn: SYM FUNC_BEGIN
   6              	foo:
   6              	ginsn: SYM foo
   7 0000 54       		push	%rsp
   7              	ginsn: SUB %r7, 8, %r7
   7              	ginsn: STORE %r7, \[%r7\+0\]
   8 0001 4889E5   		movq	%rsp, %rbp
   8              	ginsn: MOV %r7, %r6
   9              	
  10 0004 48010425 		addq	%rax, symbol
  10      00000000 
  11 000c 03042500 	        add     symbol, %eax
  11      000000
  12              	
  13 0013 670320   	        add	\(%eax\), %esp
  13              	ginsn: ADD \[%r0\+0\], %r7, %r7
  14 0016 67012405 	        add	%esp, \(,%eax\)
  14      00000000 
  15              	
  16 001e 4801C3   	        addq	%rax, %rbx
  16              	ginsn: ADD %r0, %r3, %r3
  17 0021 01C3     		add	%eax, %ebx
  17              	ginsn: ADD %r0, %r3, %r3
  18              	
  19 0023 488345F0 	        addq    \$1, -16\(%rbp\)
  19      01
  20              	
  21 0028 67032405 	        add	\(,%eax\), %esp
  21      00000000 
  21              	ginsn: ADD \[%r0\+0\], %r7, %r7
  22 0030 67012405 	        add	%esp, \(,%eax\)
  22      00000000 
  23              	
  24 0038 C3       		ret
  24              	ginsn: RET
  25              	.LFE0:
  25              	ginsn: SYM .LFE0
  26              		.size	foo, .-foo
  26              	ginsn: SYM FUNC_END
