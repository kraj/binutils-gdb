#source: gc-start.s
#source: gc-relocs-309.s
#source: gc-relocs-311.s
#source: gc-relocs-312.s
#ld: --gc-sections -T aarch64.ld
#objdump: -s -t -d

# Executable with got related relocs against global sysmbol gced.
# After gc-section removal we are cheking that symbol and got section
# do not exist and text section contains only start function.

.*:     file format elf64-(little|big)aarch64

SYMBOL TABLE:
0+10000 l    d  \.text	0+ \.text
0+00000 l    df \*ABS\*	0+ .*
0+10000 g       \.text	0+ _start

Contents of section .text:
 10000 1f2003d5                             .*

Disassembly of section \.text:

0+10000 \<_start>:
   10000:	d503201f 	nop
