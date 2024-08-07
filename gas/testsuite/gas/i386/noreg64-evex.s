	.macro pfx insn:vararg
	.ifdef DATA16
	data16 {evex} \insn
	.else
	{evex} \insn
	.endif
	.endm

        .text
_start:
	pfx adc		$1, (%rax)
	pfx adc		$0x89, (%rax)
	pfx adc		$0x1234, (%rax)
	pfx adc		$0x12345678, (%rax)
	pfx add		$1, (%rax)
	pfx add		$0x89, (%rax)
	pfx add		$0x1234, (%rax)
	pfx add		$0x12345678, (%rax)
	pfx and		$1, (%rax)
	pfx and		$0x89, (%rax)
	pfx and		$0x1234, (%rax)
	pfx and		$0x12345678, (%rax)
	pfx cmp		$1, (%rax)
	pfx cmp		$0x89, (%rax)
	pfx cmp		$0x1234, (%rax)
	pfx cmp		$0x12345678, (%rax)
	pfx crc32	(%rax), %eax
	pfx crc32	(%rax), %rax
	pfx dec		(%rax)
	pfx div		(%rax)
	pfx idiv	(%rax)
	pfx imul	(%rax)
	pfx inc		(%rax)
	pfx mul		(%rax)
	pfx neg		(%rax)
	pfx not		(%rax)
	pfx or		$1, (%rax)
	pfx or		$0x89, (%rax)
	pfx or		$0x1234, (%rax)
	pfx or		$0x12345678, (%rax)
	pfx rcl		$1, (%rax)
	pfx rcl		$2, (%rax)
	pfx rcl		%cl, (%rax)
	pfx rcr		$1, (%rax)
	pfx rcr		$2, (%rax)
	pfx rcr		%cl, (%rax)
	pfx rol		$1, (%rax)
	pfx rol		$2, (%rax)
	pfx rol		%cl, (%rax)
	pfx ror		$1, (%rax)
	pfx ror		$2, (%rax)
	pfx ror		%cl, (%rax)
	pfx sal		$1, (%rax)
	pfx sal		$2, (%rax)
	pfx sal		%cl, (%rax)
	pfx sar		$1, (%rax)
	pfx sar		$2, (%rax)
	pfx sar		%cl, (%rax)
	pfx sbb		$1, (%rax)
	pfx sbb		$0x89, (%rax)
	pfx sbb		$0x1234, (%rax)
	pfx sbb		$0x12345678, (%rax)
	pfx shl		$1, (%rax)
	pfx shl		$2, (%rax)
	pfx shl		%cl, (%rax)
	pfx shr		$1, (%rax)
	pfx shr		$2, (%rax)
	pfx shr		%cl, (%rax)
	pfx sub		$1, (%rax)
	pfx sub		$0x89, (%rax)
	pfx sub		$0x1234, (%rax)
	pfx sub		$0x12345678, (%rax)
	pfx test	$0x89, (%rax)
	pfx test	$0x1234, (%rax)
	pfx test	$0x12345678, (%rax)
	pfx xor		$1, (%rax)
	pfx xor		$0x89, (%rax)
	pfx xor		$0x1234, (%rax)
	pfx xor		$0x12345678, (%rax)
