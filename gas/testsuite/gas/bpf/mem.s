# eBPF tests for MEM instructions, modulus lddw.

        .text

 	ldabsw %r2, %r3, 0xbeef
	ldabsh %r4, %r5, 0xbeef
 	ldabsb %r6, %r7, 0xbeef
 	ldabsdw %r8, %r9, 0xbeef
	ldindw %r2, %r3, 0xbeef
 	ldindh %r4, %r5, 0xbeef
 	ldindb %r6, %r7, 0xbeef
 	ldinddw %r8, %r9, 0xbeef
