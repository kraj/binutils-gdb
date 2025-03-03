/* DO NOT EDIT!  -*- buffer-read-only: t -*- vi:set ro:  */
/* Instruction opcode header for xstormy16.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2025 Free Software Foundation, Inc.

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

#ifndef XSTORMY16_OPC_H
#define XSTORMY16_OPC_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- opc.h */

/* Allows reason codes to be output when assembler errors occur.  */
#define CGEN_VERBOSE_ASSEMBLER_ERRORS

/* We can't use the default hash size because many bits are used by
   operands.  */
#define CGEN_DIS_HASH_SIZE 1
#define CGEN_DIS_HASH(buf, value) 0
/* -- */
/* Enum declaration for xstormy16 instruction types.  */
typedef enum cgen_insn_type {
  XSTORMY16_INSN_INVALID, XSTORMY16_INSN_MOVLMEMIMM, XSTORMY16_INSN_MOVHMEMIMM, XSTORMY16_INSN_MOVLGRMEM
 , XSTORMY16_INSN_MOVHGRMEM, XSTORMY16_INSN_MOVLMEMGR, XSTORMY16_INSN_MOVHMEMGR, XSTORMY16_INSN_MOVGRGRI
 , XSTORMY16_INSN_MOVGRGRIPOSTINC, XSTORMY16_INSN_MOVGRGRIPREDEC, XSTORMY16_INSN_MOVGRIGR, XSTORMY16_INSN_MOVGRIPOSTINCGR
 , XSTORMY16_INSN_MOVGRIPREDECGR, XSTORMY16_INSN_MOVGRGRII, XSTORMY16_INSN_MOVGRGRIIPOSTINC, XSTORMY16_INSN_MOVGRGRIIPREDEC
 , XSTORMY16_INSN_MOVGRIIGR, XSTORMY16_INSN_MOVGRIIPOSTINCGR, XSTORMY16_INSN_MOVGRIIPREDECGR, XSTORMY16_INSN_MOVGRGR
 , XSTORMY16_INSN_MOVWIMM8, XSTORMY16_INSN_MOVWGRIMM8, XSTORMY16_INSN_MOVWGRIMM16, XSTORMY16_INSN_MOVLOWGR
 , XSTORMY16_INSN_MOVHIGHGR, XSTORMY16_INSN_MOVFGRGRI, XSTORMY16_INSN_MOVFGRGRIPOSTINC, XSTORMY16_INSN_MOVFGRGRIPREDEC
 , XSTORMY16_INSN_MOVFGRIGR, XSTORMY16_INSN_MOVFGRIPOSTINCGR, XSTORMY16_INSN_MOVFGRIPREDECGR, XSTORMY16_INSN_MOVFGRGRII
 , XSTORMY16_INSN_MOVFGRGRIIPOSTINC, XSTORMY16_INSN_MOVFGRGRIIPREDEC, XSTORMY16_INSN_MOVFGRIIGR, XSTORMY16_INSN_MOVFGRIIPOSTINCGR
 , XSTORMY16_INSN_MOVFGRIIPREDECGR, XSTORMY16_INSN_MASKGRGR, XSTORMY16_INSN_MASKGRIMM16, XSTORMY16_INSN_PUSHGR
 , XSTORMY16_INSN_POPGR, XSTORMY16_INSN_SWPN, XSTORMY16_INSN_SWPB, XSTORMY16_INSN_SWPW
 , XSTORMY16_INSN_ANDGRGR, XSTORMY16_INSN_ANDIMM8, XSTORMY16_INSN_ANDGRIMM16, XSTORMY16_INSN_ORGRGR
 , XSTORMY16_INSN_ORIMM8, XSTORMY16_INSN_ORGRIMM16, XSTORMY16_INSN_XORGRGR, XSTORMY16_INSN_XORIMM8
 , XSTORMY16_INSN_XORGRIMM16, XSTORMY16_INSN_NOTGR, XSTORMY16_INSN_ADDGRGR, XSTORMY16_INSN_ADDGRIMM4
 , XSTORMY16_INSN_ADDIMM8, XSTORMY16_INSN_ADDGRIMM16, XSTORMY16_INSN_ADCGRGR, XSTORMY16_INSN_ADCGRIMM4
 , XSTORMY16_INSN_ADCIMM8, XSTORMY16_INSN_ADCGRIMM16, XSTORMY16_INSN_SUBGRGR, XSTORMY16_INSN_SUBGRIMM4
 , XSTORMY16_INSN_SUBIMM8, XSTORMY16_INSN_SUBGRIMM16, XSTORMY16_INSN_SBCGRGR, XSTORMY16_INSN_SBCGRIMM4
 , XSTORMY16_INSN_SBCGRIMM8, XSTORMY16_INSN_SBCGRIMM16, XSTORMY16_INSN_INCGRIMM2, XSTORMY16_INSN_DECGRIMM2
 , XSTORMY16_INSN_RRCGRGR, XSTORMY16_INSN_RRCGRIMM4, XSTORMY16_INSN_RLCGRGR, XSTORMY16_INSN_RLCGRIMM4
 , XSTORMY16_INSN_SHRGRGR, XSTORMY16_INSN_SHRGRIMM, XSTORMY16_INSN_SHLGRGR, XSTORMY16_INSN_SHLGRIMM
 , XSTORMY16_INSN_ASRGRGR, XSTORMY16_INSN_ASRGRIMM, XSTORMY16_INSN_SET1GRIMM, XSTORMY16_INSN_SET1GRGR
 , XSTORMY16_INSN_SET1LMEMIMM, XSTORMY16_INSN_SET1HMEMIMM, XSTORMY16_INSN_CLR1GRIMM, XSTORMY16_INSN_CLR1GRGR
 , XSTORMY16_INSN_CLR1LMEMIMM, XSTORMY16_INSN_CLR1HMEMIMM, XSTORMY16_INSN_CBWGR, XSTORMY16_INSN_REVGR
 , XSTORMY16_INSN_BCCGRGR, XSTORMY16_INSN_BCCGRIMM8, XSTORMY16_INSN_BCCIMM16, XSTORMY16_INSN_BNGRIMM4
 , XSTORMY16_INSN_BNGRGR, XSTORMY16_INSN_BNLMEMIMM, XSTORMY16_INSN_BNHMEMIMM, XSTORMY16_INSN_BPGRIMM4
 , XSTORMY16_INSN_BPGRGR, XSTORMY16_INSN_BPLMEMIMM, XSTORMY16_INSN_BPHMEMIMM, XSTORMY16_INSN_BCC
 , XSTORMY16_INSN_BGR, XSTORMY16_INSN_BR, XSTORMY16_INSN_JMP, XSTORMY16_INSN_JMPF
 , XSTORMY16_INSN_CALLRGR, XSTORMY16_INSN_CALLRIMM, XSTORMY16_INSN_CALLGR, XSTORMY16_INSN_CALLFIMM
 , XSTORMY16_INSN_ICALLRGR, XSTORMY16_INSN_ICALLGR, XSTORMY16_INSN_ICALLFIMM, XSTORMY16_INSN_IRET
 , XSTORMY16_INSN_RET, XSTORMY16_INSN_MUL, XSTORMY16_INSN_DIV, XSTORMY16_INSN_SDIV
 , XSTORMY16_INSN_SDIVLH, XSTORMY16_INSN_DIVLH, XSTORMY16_INSN_RESET, XSTORMY16_INSN_NOP
 , XSTORMY16_INSN_HALT, XSTORMY16_INSN_HOLD, XSTORMY16_INSN_HOLDX, XSTORMY16_INSN_BRK
 , XSTORMY16_INSN_SYSCALL
} CGEN_INSN_TYPE;

/* Index of `invalid' insn place holder.  */
#define CGEN_INSN_INVALID XSTORMY16_INSN_INVALID

/* Total number of insns in table.  */
#define MAX_INSNS ((int) XSTORMY16_INSN_SYSCALL + 1)

/* This struct records data prior to insertion or after extraction.  */
struct cgen_fields
{
  int length;
  long f_nil;
  long f_anyof;
  long f_Rd;
  long f_Rdm;
  long f_Rm;
  long f_Rs;
  long f_Rb;
  long f_Rbj;
  long f_op1;
  long f_op2;
  long f_op2a;
  long f_op2m;
  long f_op3;
  long f_op3a;
  long f_op3b;
  long f_op4;
  long f_op4m;
  long f_op4b;
  long f_op5;
  long f_op5a;
  long f_op;
  long f_imm2;
  long f_imm3;
  long f_imm3b;
  long f_imm4;
  long f_imm8;
  long f_imm12;
  long f_imm16;
  long f_lmem8;
  long f_hmem8;
  long f_rel8_2;
  long f_rel8_4;
  long f_rel12;
  long f_rel12a;
  long f_abs24_1;
  long f_abs24_2;
  long f_abs24;
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

#endif /* XSTORMY16_OPC_H */
