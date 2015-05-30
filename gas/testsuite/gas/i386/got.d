#objdump: -dwr

.*: +file format .*


Disassembly of section .text:

0+ <_start>:
[ 	]*[a-f0-9]+:	b8 00 00 00 00       	mov    \$0x0,%eax	1: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	a1 00 00 00 00       	mov    0x0,%eax	6: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	8b 80 00 00 00 00    	mov    0x0\(%eax\),%eax	c: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	ff 15 00 00 00 00    	call   \*0x0	12: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff 90 00 00 00 00    	call   \*0x0\(%eax\)	18: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff 25 00 00 00 00    	jmp    \*0x0	1e: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff a0 00 00 00 00    	jmp    \*0x0\(%eax\)	24: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	b8 00 00 00 00       	mov    \$0x0,%eax	29: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	a1 00 00 00 00       	mov    0x0,%eax	2e: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	8b 80 00 00 00 00    	mov    0x0\(%eax\),%eax	34: R_386_GOT32	foo
[ 	]*[a-f0-9]+:	ff 90 00 00 00 00    	call   \*0x0\(%eax\)	3a: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff 15 00 00 00 00    	call   \*0x0	40: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff a0 00 00 00 00    	jmp    \*0x0\(%eax\)	46: R_386_RELAX_GOT32	foo
[ 	]*[a-f0-9]+:	ff 25 00 00 00 00    	jmp    \*0x0	4c: R_386_RELAX_GOT32	foo
#pass
