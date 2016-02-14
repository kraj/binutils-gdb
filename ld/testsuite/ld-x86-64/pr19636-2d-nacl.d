#source: pr19636-2.s
#as: --64 -mrelax-relocations=no
#ld: -pie -m elf_x86_64 -z nodynamic-undefined-weak
#objdump: -dw
#target: x86_64-*-nacl*

.*: +file format .*


Disassembly of section .plt:

0+ <.plt>:
[ 	]*[a-f0-9]+:	ff 35 c2 02 01 10    	pushq  0x100102c2\(%rip\)        # 100102c8 <_GLOBAL_OFFSET_TABLE_\+0x8>
[ 	]*[a-f0-9]+:	4c 8b 1d c3 02 01 10 	mov    0x100102c3\(%rip\),%r11        # 100102d0 <_GLOBAL_OFFSET_TABLE_\+0x10>
[ 	]*[a-f0-9]+:	41 83 e3 e0          	and    \$0xffffffe0,%r11d
[ 	]*[a-f0-9]+:	4d 01 fb             	add    %r15,%r11
[ 	]*[a-f0-9]+:	41 ff e3             	jmpq   \*%r11
[ 	]*[a-f0-9]+:	66 0f 1f 84 00 00 00 00 00 	nopw   0x0\(%rax,%rax,1\)
[ 	]*[a-f0-9]+:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 data16 nopw %cs:0x0\(%rax,%rax,1\)
[ 	]*[a-f0-9]+:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 data16 nopw %cs:0x0\(%rax,%rax,1\)
[ 	]*[a-f0-9]+:	66 90                	xchg   %ax,%ax
[ 	]*[a-f0-9]+:	4c 8b 1d 91 02 01 10 	mov    0x10010291\(%rip\),%r11        # 100102d8 <_GLOBAL_OFFSET_TABLE_\+0x18>
[ 	]*[a-f0-9]+:	41 83 e3 e0          	and    \$0xffffffe0,%r11d
[ 	]*[a-f0-9]+:	4d 01 fb             	add    %r15,%r11
[ 	]*[a-f0-9]+:	41 ff e3             	jmpq   \*%r11
[ 	]*[a-f0-9]+:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 data16 nopw %cs:0x0\(%rax,%rax,1\)
[ 	]*[a-f0-9]+:	68 00 00 00 00       	pushq  \$0x0
[ 	]*[a-f0-9]+:	e9 00 00 00 00       	jmpq   6a <_start-0x16>
[ 	]*[a-f0-9]+:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 data16 nopw %cs:0x0\(%rax,%rax,1\)
[ 	]*[a-f0-9]+:	0f 1f 80 00 00 00 00 	nopl   0x0\(%rax\)

Disassembly of section .text:

0+80 <_start>:
[ 	]*[a-f0-9]+:	48 3b 05 29 02 01 10 	cmp    0x10010229\(%rip\),%rax        # 100102b0 <_DYNAMIC\+0xe0>
[ 	]*[a-f0-9]+:	ff 25 2b 02 01 10    	jmpq   \*0x1001022b\(%rip\)        # 100102b8 <_DYNAMIC\+0xe8>
[ 	]*[a-f0-9]+:	e8 ae ff ff ff       	callq  40 <_start-0x40>
