#source: pr19807-1a.s
#as: --x32
#ld: -pie -melf32_x86_64 --defsym foo=0x7fffffff
#objdump: -dw

.*: +file format .*


Disassembly of section .text:

[a-f0-9]+ <_start>:
[ 	]*[a-f0-9]+:	48 c7 c0 ff ff ff 7f 	mov    \$0x7fffffff,%rax
#pass
