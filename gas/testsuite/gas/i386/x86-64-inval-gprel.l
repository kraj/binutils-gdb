.*: Assembler messages:
.*:3: Error: invalid GP relocation
.*:3: Error: non-pc-relative relocation for pc-relative field
.*:4: Error: invalid GP relocation
.*:5: Error: invalid GP relocation
.*:6: Error: invalid GP relocation
.*:6: Error: non-pc-relative relocation for pc-relative field
.*:7: Error: invalid GP relocation
.*:8: Error: invalid GP relocation
GAS LISTING .*


[ 	]*1[ 	]+\.text
[ 	]*2[ 	]+_start:
[ 	]*3[ 	]+\?\?\?\? 648B0500 		movl	%fs:foo@GPREL\(%rip\), %eax
\*\*\*\*  Error: invalid GP relocation
\*\*\*\*  Error: non-pc-relative relocation for pc-relative field
[ 	]*3[ 	]+000000
[ 	]*4[ 	]+\?\?\?\? 648B8000 		movl	%fs:foo@GPREL\(%rax\), %eax
\*\*\*\*  Error: invalid GP relocation
[ 	]*4[ 	]+000000
[ 	]*5[ 	]+\?\?\?\? 8B844800 		movl	%ds:foo@GPREL\(%rax, %rcx, 2\), %eax
\*\*\*\*  Error: invalid GP relocation
[ 	]*5[ 	]+000000
[ 	]*6[ 	]+\?\?\?\? 8B050000 		movl	foo@GPREL\(%rip\), %eax
\*\*\*\*  Error: invalid GP relocation
\*\*\*\*  Error: non-pc-relative relocation for pc-relative field
[ 	]*6[ 	]+0000
[ 	]*7[ 	]+\?\?\?\? 8B800000 		movl	foo@GPREL\(%rax\), %eax
\*\*\*\*  Error: invalid GP relocation
[ 	]*7[ 	]+0000
[ 	]*8[ 	]+\?\?\?\? 8B042500 		movl	foo@GPREL, %eax
\*\*\*\*  Error: invalid GP relocation
[ 	]*8[ 	]+000000
