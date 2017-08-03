#objdump: -drw
#name: x86-64 gprel

.*: +file format .*

Disassembly of section .text:

0+ <_start>:
 +[a-f0-9]+:	65 8b 04 25 00 00 00 00 	mov    %gs:0x0,%eax	4: R_X86_64_GPREL	foo
#pass
