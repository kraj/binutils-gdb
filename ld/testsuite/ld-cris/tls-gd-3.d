#source: start1.s
#source: tls128.s
#source: tls-gd-3.s
#source: tls-x.s
#as: --no-underscore --emulation=criself
#ld: -m crislinux
#objdump: -d -s -t -r -p

# Check that we have proper NPTL/TLS markings and GOT for an
# executable with a single R_CRIS_32_GD.

.*:     file format elf32-cris

Program Header:
#...
     TLS off    0x0+a0 vaddr 0x0+820a0 paddr 0x0+820a0 align 2\*\*2
         filesz 0x0+84 memsz 0x0+84 flags r--
private flags = 0:
#...
SYMBOL TABLE:
#...
0+80 g       \.tdata	0+4 x
#...
Contents of section \.text:
#...
Contents of section \.tdata:
#...
Contents of section \.got:
 82124 00000000 00000000 00000000 01000000  .*
 82134 80000000                             .*

Disassembly of section \.text:

00080094 <_start>:
   80094:	41b2                	moveq 1,\$r11
#...
00080098 <tlsfn>:
   80098:	6fae 3021 0800      	move\.d [^>]+>,\$r10
#...
