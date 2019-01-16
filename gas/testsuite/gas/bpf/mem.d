#as: --LE
#objdump: -dr
#name: eBPF MEM instructions, modulus lddw

.*: +file format .*bpf.*

Disassembly of section .text:

0+ <.text>:
   0:	20 23 00 00 ef be 00 00 	ldabsw %r2,%r3,48879
   8:	28 45 00 00 ef be 00 00 	ldabsh %r4,%r5,48879
  10:	30 67 00 00 ef be 00 00 	ldabsb %r6,%r7,48879
  18:	38 89 00 00 ef be 00 00 	ldabsdw %r8,%r9,48879
  20:	40 23 00 00 ef be 00 00 	ldindw %r2,%r3,48879
  28:	48 45 00 00 ef be 00 00 	ldindh %r4,%r5,48879
  30:	50 67 00 00 ef be 00 de 	ldindb %r6,%r7,48879
  38:	58 89 00 00 ef be 00 00 	ldinddw %r8,%r9,48879
