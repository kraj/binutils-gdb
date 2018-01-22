#as: -mrelax-relocations=no
#objdump: -dwr

.*: +file format .*


Disassembly of section .text:

0+ <_start>:
[ 	]*[a-f0-9]+:	48 c7 c0 00 00 00 00 	mov    \$0x0,%rax	3: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	48 8b 04 25 00 00 00 00 	mov    0x0,%rax	b: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	48 8b 05 00 00 00 00 	mov    0x0\(%rip\),%rax        # 16 <_start\+0x16>	12: R_X86_64_THUNK_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	8b 05 00 00 00 00    	mov    0x0\(%rip\),%eax        # 1c <_start\+0x1c>	18: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	48 8b 81 00 00 00 00 	mov    0x0\(%rcx\),%rax	1f: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	ff 15 00 00 00 00    	callq  \*0x0\(%rip\)        # 29 <_start\+0x29>	25: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	ff 90 00 00 00 00    	callq  \*0x0\(%rax\)	2b: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	ff 25 00 00 00 00    	jmpq   \*0x0\(%rip\)        # 35 <_start\+0x35>	31: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	ff a1 00 00 00 00    	jmpq   \*0x0\(%rcx\)	37: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	48 c7 c0 00 00 00 00 	mov    \$0x0,%rax	3e: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	48 8b 04 25 00 00 00 00 	mov    0x0,%rax	46: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	48 8b 05 00 00 00 00 	mov    0x0\(%rip\),%rax        # 51 <_start\+0x51>	4d: R_X86_64_THUNK_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	8b 05 00 00 00 00    	mov    0x0\(%rip\),%eax        # 57 <_start\+0x57>	53: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	48 8b 81 00 00 00 00 	mov    0x0\(%rcx\),%rax	5a: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	ff 15 00 00 00 00    	callq  \*0x0\(%rip\)        # 64 <_start\+0x64>	60: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	ff 90 00 00 00 00    	callq  \*0x0\(%rax\)	66: R_X86_64_GOTPCREL	foo
[ 	]*[a-f0-9]+:	ff 25 00 00 00 00    	jmpq   \*0x0\(%rip\)        # 70 <_start\+0x70>	6c: R_X86_64_GOTPCRELX	foo-0x4
[ 	]*[a-f0-9]+:	ff a1 00 00 00 00    	jmpq   \*0x0\(%rcx\)	72: R_X86_64_GOTPCREL	foo
#pass
