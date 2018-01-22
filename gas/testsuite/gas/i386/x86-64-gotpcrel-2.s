	.text
_start:
	movq	$foo@GOTPCREL_THUNK, %rax
	movq	foo@GOTPCREL_THUNK, %rax
	movq	foo@GOTPCREL_THUNK(%rip), %rax
	movl	foo@GOTPCREL_THUNK(%rip), %eax
	movq	foo@GOTPCREL_THUNK(%rcx), %rax

	call	*foo@GOTPCREL_THUNK(%rip)
	call	*foo@GOTPCREL_THUNK(%rax)
	jmp	*foo@GOTPCREL_THUNK(%rip)
	jmp	*foo@GOTPCREL_THUNK(%rcx)

	.intel_syntax noprefix

	mov	rax, offset foo@gotpcrel_thunk
	mov	rax, QWORD PTR [foo@GOTPCREL_THUNK]
	mov	rax, QWORD PTR foo@GOTPCREL_THUNK[rip]
	mov	eax, DWORD PTR foo@GOTPCREL_THUNK[rip]
	mov	rax, QWORD PTR [rcx + foo@GOTPCREL_THUNK]

	call	QWORD PTR foo@GOTPCREL_THUNK[rip]
	call	QWORD PTR [rax + foo@GOTPCREL_THUNK]
	jmp	QWORD PTR [rip + foo@GOTPCREL_THUNK]
	jmp	QWORD PTR [rcx + foo@GOTPCREL_THUNK]
