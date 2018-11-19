#as: --LE
#objdump: -dr
#name: eBPF LDDW

.*: +file format .*ebpf.*

Disassembly of section .text:

0+ <.text>:
   0:	18 03 00 00 01 00 00 00 	lddw %r3,1
   8:	00 00 00 00 00 00 00 00 
  10:	18 04 00 00 ef be ad de 	lddw %r4, 3735928559
  18:	00 00 00 00 00 00 00 00
  20:	18 05 00 00 88 77 66 55 	lddw %r5,1234605616436508552
  28:	44 33 22 11 00 00 00 00 
  30:	18 06 00 00 fe ff ff ff 	lddw %r6,-1
  38:	ff ff ff ff 00 00 00 00
