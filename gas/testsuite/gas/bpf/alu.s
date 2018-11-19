# Tests for the ALU eBPF instructions
        .text
        add32	%r2, 666
        add32	%r3, -666
        add32	%r4, 0xdeadbeef
        add32	%r5, %r6
        sub32	%r2, 666
        sub32	%r3, -666
        sub32	%r4, 0xdeadbeef
        sub32	%r5, %r6
        mul32	%r2, 666
        mul32	%r3, -666
        mul32	%r4, 0xdeadbeef
        mul32	%r5, %r6
        div32	%r2, 666
        div32	%r3, -666
        div32	%r4, 0xdeadbeef
        div32	%r5, %r6
        or32	%r2, 666
        or32	%r3, -666
        or32	%r4, 0xdeadbeef
        or32	%r5, %r6
        and32	%r2, 666
        and32	%r3, -666
        and32	%r4, 0xdeadbeef
        and32	%r5, %r6
        lsh32	%r2, 666
        lsh32	%r3, -666
        lsh32	%r4, 0xdeadbeef
        lsh32	%r5, %r6
        rsh32	%r2, 666
        rsh32	%r3, -666
        rsh32	%r4, 0xdeadbeef
        rsh32	%r5, %r6
        mod32	%r2, 666
        mod32	%r3, -666
        mod32	%r4, 0xdeadbeef
        mod32	%r5, %r6
        xor32	%r2, 666
        xor32	%r3, -666
        xor32	%r4, 0xdeadbeef
        xor32	%r5, %r6
        mov32	%r2, 666
        mov32	%r3, -666
        mov32	%r4, 0xdeadbeef
        mov32	%r5, %r6
        arsh32	%r2, 666
        arsh32	%r3, -666
        arsh32	%r4, 0xdeadbeef
        arsh32	%r5, %r6
        neg32	%r2
	le16	%r9
        le32	%r8
        le64	%r7
        be16	%r6
        be32	%r5
        be64	%r4
