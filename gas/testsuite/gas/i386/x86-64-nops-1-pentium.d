#as: -mtune=pentium
#source: nops-1.s
#objdump: -drw
#name: x86-64 -mtune=pentium nops 1

.*: +file format .*

Disassembly of section .text:

0+ <nop15>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	2e 48 8d 74 26 00    	cs lea (0x)?0\(%rsi,%riz,1\),%rsi
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+10 <nop14>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d 74 26 00       	lea    (0x)?0\(%rsi,%riz,1\),%rsi
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+20 <nop13>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d 76 00          	lea    (0x)?0\(%rsi\),%rsi
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+30 <nop12>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 89 f6             	mov    %rsi,%rsi
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+40 <nop11>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	66 90                	xchg   %ax,%ax
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+50 <nop10>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	90                   	nop
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+60 <nop9>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	2e 48 8d b4 26 00 00 00 00 	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+70 <nop8>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d b4 26 00 00 00 00 	lea    (0x)?0\(%rsi,%riz,1\),%rsi

0+80 <nop7>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d b6 00 00 00 00 	lea    (0x)?0\(%rsi\),%rsi

0+90 <nop6>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	2e 48 8d 74 26 00    	cs lea (0x)?0\(%rsi,%riz,1\),%rsi

0+a0 <nop5>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d 74 26 00       	lea    (0x)?0\(%rsi,%riz,1\),%rsi

0+b0 <nop4>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 8d 76 00          	lea    (0x)?0\(%rsi\),%rsi

0+c0 <nop3>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	48 89 f6             	mov    %rsi,%rsi

0+d0 <nop2>:
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	f8                   	clc
[ 	]*[a-f0-9]+:	66 90                	xchg   %ax,%ax
#pass
