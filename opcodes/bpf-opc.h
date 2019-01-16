/* DO NOT EDIT!  -*- buffer-read-only: t -*- vi:set ro:  */
/* Instruction opcode header for bpf.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2019 Free Software Foundation, Inc.

This file is part of the GNU Binutils and/or GDB, the GNU debugger.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#ifndef BPF_OPC_H
#define BPF_OPC_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- opc.h */

#undef CGEN_DIS_HASH_SIZE
#define CGEN_DIS_HASH_SIZE 1

#undef CGEN_DIS_HASH
#define CGEN_DIS_HASH(buffer, value) 0

/* Allows reason codes to be output when assembler errors occur.  */
#define CGEN_VERBOSE_ASSEMBLER_ERRORS



/* -- opc.c */
/* Enum declaration for bpf instruction types.  */
typedef enum cgen_insn_type {
  BPF_INSN_INVALID, BPF_INSN_ADDI, BPF_INSN_ADDR, BPF_INSN_ADD32I
 , BPF_INSN_ADD32R, BPF_INSN_SUBI, BPF_INSN_SUBR, BPF_INSN_SUB32I
 , BPF_INSN_SUB32R, BPF_INSN_MULI, BPF_INSN_MULR, BPF_INSN_MUL32I
 , BPF_INSN_MUL32R, BPF_INSN_DIVI, BPF_INSN_DIVR, BPF_INSN_DIV32I
 , BPF_INSN_DIV32R, BPF_INSN_ORI, BPF_INSN_ORR, BPF_INSN_OR32I
 , BPF_INSN_OR32R, BPF_INSN_ANDI, BPF_INSN_ANDR, BPF_INSN_AND32I
 , BPF_INSN_AND32R, BPF_INSN_LSHI, BPF_INSN_LSHR, BPF_INSN_LSH32I
 , BPF_INSN_LSH32R, BPF_INSN_RSHI, BPF_INSN_RSHR, BPF_INSN_RSH32I
 , BPF_INSN_RSH32R, BPF_INSN_MODI, BPF_INSN_MODR, BPF_INSN_MOD32I
 , BPF_INSN_MOD32R, BPF_INSN_XORI, BPF_INSN_XORR, BPF_INSN_XOR32I
 , BPF_INSN_XOR32R, BPF_INSN_MOVI, BPF_INSN_MOVR, BPF_INSN_MOV32I
 , BPF_INSN_MOV32R, BPF_INSN_ARSHI, BPF_INSN_ARSHR, BPF_INSN_ARSH32I
 , BPF_INSN_ARSH32R, BPF_INSN_NEG, BPF_INSN_NEG32, BPF_INSN_LDDW
 , BPF_INSN_LDABSW, BPF_INSN_LDABSH, BPF_INSN_LDABSB, BPF_INSN_LDABSDW
 , BPF_INSN_LDINDW, BPF_INSN_LDINDH, BPF_INSN_LDINDB, BPF_INSN_LDINDDW
 , BPF_INSN_LDXW, BPF_INSN_LDXH, BPF_INSN_LDXB, BPF_INSN_LDXDW
 , BPF_INSN_STW, BPF_INSN_STH, BPF_INSN_STB, BPF_INSN_STDW
 , BPF_INSN_STXW, BPF_INSN_STXH, BPF_INSN_STXB, BPF_INSN_STXDW
 , BPF_INSN_JA, BPF_INSN_JEQI, BPF_INSN_JEQR, BPF_INSN_JGTI
 , BPF_INSN_JGTR, BPF_INSN_JGEI, BPF_INSN_JGER, BPF_INSN_JLTI
 , BPF_INSN_JLTR, BPF_INSN_JLEI, BPF_INSN_JLER, BPF_INSN_JSETI
 , BPF_INSN_JSETR, BPF_INSN_JNEI, BPF_INSN_JNER, BPF_INSN_JSGTI
 , BPF_INSN_JSGTR, BPF_INSN_JSGEI, BPF_INSN_JSGER, BPF_INSN_JSLTI
 , BPF_INSN_JSLTR, BPF_INSN_JSLEI, BPF_INSN_JSLER, BPF_INSN_CALL
 , BPF_INSN_EXIT
} CGEN_INSN_TYPE;

/* Index of `invalid' insn place holder.  */
#define CGEN_INSN_INVALID BPF_INSN_INVALID

/* Total number of insns in table.  */
#define MAX_INSNS ((int) BPF_INSN_EXIT + 1)

/* This struct records data prior to insertion or after extraction.  */
struct cgen_fields
{
  int length;
  long f_nil;
  long f_anyof;
  long f_offset16;
  long f_src;
  long f_dst;
  long f_op_code;
  long f_op_src;
  long f_op_class;
  long f_op_mode;
  long f_op_size;
  long f_imm32;
  long f_imm64_a;
  long f_imm64_b;
  long f_imm64_c;
  long f_imm64;
};

#define CGEN_INIT_PARSE(od) \
{\
}
#define CGEN_INIT_INSERT(od) \
{\
}
#define CGEN_INIT_EXTRACT(od) \
{\
}
#define CGEN_INIT_PRINT(od) \
{\
}


   #ifdef __cplusplus
   }
   #endif

#endif /* BPF_OPC_H */
