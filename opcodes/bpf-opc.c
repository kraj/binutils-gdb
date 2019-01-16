/* DO NOT EDIT!  -*- buffer-read-only: t -*- vi:set ro:  */
/* Instruction opcode table for bpf.

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

#include "sysdep.h"
#include "ansidecl.h"
#include "bfd.h"
#include "symcat.h"
#include "bpf-desc.h"
#include "bpf-opc.h"
#include "libiberty.h"

/* -- opc.c */

/* -- asm.c */
/* The hash functions are recorded here to help keep assembler code out of
   the disassembler and vice versa.  */

static int asm_hash_insn_p        (const CGEN_INSN *);
static unsigned int asm_hash_insn (const char *);
static int dis_hash_insn_p        (const CGEN_INSN *);
static unsigned int dis_hash_insn (const char *, CGEN_INSN_INT);

/* Instruction formats.  */

#define F(f) & bpf_cgen_ifld_table[BPF_##f]
static const CGEN_IFMT ifmt_empty ATTRIBUTE_UNUSED = {
  0, 0, 0x0, { { 0 } }
};

static const CGEN_IFMT ifmt_addi ATTRIBUTE_UNUSED = {
  64, 64, 0xfffff0ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_addr ATTRIBUTE_UNUSED = {
  64, 64, 0xffff00ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_neg ATTRIBUTE_UNUSED = {
  64, 64, 0xfffff0ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_lddw ATTRIBUTE_UNUSED = {
  64, 128, 0xfffff0ff, { { F (F_IMM64) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_MODE) }, { F (F_OP_SIZE) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_ldabsw ATTRIBUTE_UNUSED = {
  64, 64, 0xffff00ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_MODE) }, { F (F_OP_SIZE) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_ldxw ATTRIBUTE_UNUSED = {
  64, 64, 0xff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_MODE) }, { F (F_OP_SIZE) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_stw ATTRIBUTE_UNUSED = {
  64, 64, 0xf0ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_MODE) }, { F (F_OP_SIZE) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_ja ATTRIBUTE_UNUSED = {
  64, 64, 0xffff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_jeqi ATTRIBUTE_UNUSED = {
  64, 64, 0xf0ff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_jeqr ATTRIBUTE_UNUSED = {
  64, 64, 0xff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_call ATTRIBUTE_UNUSED = {
  64, 64, 0xffffffff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

static const CGEN_IFMT ifmt_exit ATTRIBUTE_UNUSED = {
  64, 64, 0xffffffff, { { F (F_IMM32) }, { F (F_OFFSET16) }, { F (F_SRC) }, { F (F_DST) }, { F (F_OP_CODE) }, { F (F_OP_SRC) }, { F (F_OP_CLASS) }, { 0 } }
};

#undef F

#define A(a) (1 << CGEN_INSN_##a)
#define OPERAND(op) BPF_OPERAND_##op
#define MNEM CGEN_SYNTAX_MNEMONIC /* syntax value for mnemonic */
#define OP(field) CGEN_SYNTAX_MAKE_FIELD (OPERAND (field))

/* The instruction table.  */

static const CGEN_OPCODE bpf_cgen_insn_opcode_table[MAX_INSNS] =
{
  /* Special null first entry.
     A `num' value of zero is thus invalid.
     Also, the special `invalid' insn resides here.  */
  { { 0, 0, 0, 0 }, {{0}}, 0, {0}},
/* add $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x7 }
  },
/* add $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xf }
  },
/* add32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x4 }
  },
/* add32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xc }
  },
/* sub $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x17 }
  },
/* sub $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x1f }
  },
/* sub32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x14 }
  },
/* sub32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x1c }
  },
/* mul $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x27 }
  },
/* mul $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x2f }
  },
/* mul32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x24 }
  },
/* mul32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x2c }
  },
/* div $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x37 }
  },
/* div $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x3f }
  },
/* div32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x34 }
  },
/* div32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x3c }
  },
/* or $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x47 }
  },
/* or $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x4f }
  },
/* or32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x44 }
  },
/* or32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x4c }
  },
/* and $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x57 }
  },
/* and $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x5f }
  },
/* and32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x54 }
  },
/* and32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x5c }
  },
/* lsh $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x67 }
  },
/* lsh $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x6f }
  },
/* lsh32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x64 }
  },
/* lsh32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x6c }
  },
/* rsh $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x77 }
  },
/* rsh $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x7f }
  },
/* rsh32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x74 }
  },
/* rsh32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x7c }
  },
/* mod $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x97 }
  },
/* mod $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x9f }
  },
/* mod32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0x94 }
  },
/* mod32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0x9c }
  },
/* xor $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xa7 }
  },
/* xor $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xaf }
  },
/* xor32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xa4 }
  },
/* xor32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xac }
  },
/* mov $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xb7 }
  },
/* mov $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xbf }
  },
/* mov32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xb4 }
  },
/* mov32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xbc }
  },
/* arsh $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xc7 }
  },
/* arsh $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xcf }
  },
/* arsh32 $dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_addi, { 0xc4 }
  },
/* arsh32 $dst,$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), 0 } },
    & ifmt_addr, { 0xcc }
  },
/* neg $dst */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), 0 } },
    & ifmt_neg, { 0x8f }
  },
/* neg32 $dst */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), 0 } },
    & ifmt_neg, { 0x8c }
  },
/* lddw $dst,$imm64 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM64), 0 } },
    & ifmt_lddw, { 0x18 }
  },
/* ldabsw $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x20 }
  },
/* ldabsh $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x28 }
  },
/* ldabsb $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x30 }
  },
/* ldabsdw $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x38 }
  },
/* ldindw $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x40 }
  },
/* ldindh $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x48 }
  },
/* ldindb $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x50 }
  },
/* ldinddw $src,$dst,$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (SRC), ',', OP (DST), ',', OP (IMM32), 0 } },
    & ifmt_ldabsw, { 0x58 }
  },
/* ldxw $dst,[$src+$offset16] */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', '[', OP (SRC), '+', OP (OFFSET16), ']', 0 } },
    & ifmt_ldxw, { 0x61 }
  },
/* ldxh $dst,[$src+$offset16] */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', '[', OP (SRC), '+', OP (OFFSET16), ']', 0 } },
    & ifmt_ldxw, { 0x69 }
  },
/* ldxb $dst,[$src+$offset16] */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', '[', OP (SRC), '+', OP (OFFSET16), ']', 0 } },
    & ifmt_ldxw, { 0x71 }
  },
/* ldxdw $dst,[$src+$offset16] */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', '[', OP (SRC), '+', OP (OFFSET16), ']', 0 } },
    & ifmt_ldxw, { 0x79 }
  },
/* stw [$dst+$offset16],$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (IMM32), 0 } },
    & ifmt_stw, { 0x62 }
  },
/* sth [$dst+$offset16],$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (IMM32), 0 } },
    & ifmt_stw, { 0x6a }
  },
/* stb [$dst+$offset16],$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (IMM32), 0 } },
    & ifmt_stw, { 0x72 }
  },
/* stdw [$dst+$offset16],$imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (IMM32), 0 } },
    & ifmt_stw, { 0x7a }
  },
/* stxw [$dst+$offset16],$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (SRC), 0 } },
    & ifmt_ldxw, { 0x63 }
  },
/* stxh [$dst+$offset16],$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (SRC), 0 } },
    & ifmt_ldxw, { 0x6b }
  },
/* stxb [$dst+$offset16],$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (SRC), 0 } },
    & ifmt_ldxw, { 0x73 }
  },
/* stxdw [$dst+$offset16],$src */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '[', OP (DST), '+', OP (OFFSET16), ']', ',', OP (SRC), 0 } },
    & ifmt_ldxw, { 0x7b }
  },
/* ja +$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', '+', OP (OFFSET16), 0 } },
    & ifmt_ja, { 0x5 }
  },
/* jeq $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x15 }
  },
/* jeq $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x1d }
  },
/* jgt $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x25 }
  },
/* jgt $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x2d }
  },
/* jge $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x35 }
  },
/* jge $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x3d }
  },
/* jlt $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0xa5 }
  },
/* jlt $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0xad }
  },
/* jle $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0xb5 }
  },
/* jle $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0xbd }
  },
/* jset $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x45 }
  },
/* jset $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x4d }
  },
/* jne $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x55 }
  },
/* jne $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x5d }
  },
/* jsgt $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x65 }
  },
/* jsgt $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x6d }
  },
/* jsge $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0x75 }
  },
/* jsge $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0x7d }
  },
/* jslt $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0xc5 }
  },
/* jslt $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0xcd }
  },
/* jsle $dst,$imm32,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (IMM32), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqi, { 0xd5 }
  },
/* jsle $dst,$src,+$offset16 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (DST), ',', OP (SRC), ',', '+', OP (OFFSET16), 0 } },
    & ifmt_jeqr, { 0xdd }
  },
/* call $imm32 */
  {
    { 0, 0, 0, 0 },
    { { MNEM, ' ', OP (IMM32), 0 } },
    & ifmt_call, { 0x85 }
  },
/* exit */
  {
    { 0, 0, 0, 0 },
    { { MNEM, 0 } },
    & ifmt_exit, { 0x95 }
  },
};

#undef A
#undef OPERAND
#undef MNEM
#undef OP

/* Formats for ALIAS macro-insns.  */

#define F(f) & bpf_cgen_ifld_table[BPF_##f]
#undef F

/* Each non-simple macro entry points to an array of expansion possibilities.  */

#define A(a) (1 << CGEN_INSN_##a)
#define OPERAND(op) BPF_OPERAND_##op
#define MNEM CGEN_SYNTAX_MNEMONIC /* syntax value for mnemonic */
#define OP(field) CGEN_SYNTAX_MAKE_FIELD (OPERAND (field))

/* The macro instruction table.  */

static const CGEN_IBASE bpf_cgen_macro_insn_table[] =
{
};

/* The macro instruction opcode table.  */

static const CGEN_OPCODE bpf_cgen_macro_insn_opcode_table[] =
{
};

#undef A
#undef OPERAND
#undef MNEM
#undef OP

#ifndef CGEN_ASM_HASH_P
#define CGEN_ASM_HASH_P(insn) 1
#endif

#ifndef CGEN_DIS_HASH_P
#define CGEN_DIS_HASH_P(insn) 1
#endif

/* Return non-zero if INSN is to be added to the hash table.
   Targets are free to override CGEN_{ASM,DIS}_HASH_P in the .opc file.  */

static int
asm_hash_insn_p (const CGEN_INSN *insn ATTRIBUTE_UNUSED)
{
  return CGEN_ASM_HASH_P (insn);
}

static int
dis_hash_insn_p (const CGEN_INSN *insn)
{
  /* If building the hash table and the NO-DIS attribute is present,
     ignore.  */
  if (CGEN_INSN_ATTR_VALUE (insn, CGEN_INSN_NO_DIS))
    return 0;
  return CGEN_DIS_HASH_P (insn);
}

#ifndef CGEN_ASM_HASH
#define CGEN_ASM_HASH_SIZE 127
#ifdef CGEN_MNEMONIC_OPERANDS
#define CGEN_ASM_HASH(mnem) (*(unsigned char *) (mnem) % CGEN_ASM_HASH_SIZE)
#else
#define CGEN_ASM_HASH(mnem) (*(unsigned char *) (mnem) % CGEN_ASM_HASH_SIZE) /*FIXME*/
#endif
#endif

/* It doesn't make much sense to provide a default here,
   but while this is under development we do.
   BUFFER is a pointer to the bytes of the insn, target order.
   VALUE is the first base_insn_bitsize bits as an int in host order.  */

#ifndef CGEN_DIS_HASH
#define CGEN_DIS_HASH_SIZE 256
#define CGEN_DIS_HASH(buf, value) (*(unsigned char *) (buf))
#endif

/* The result is the hash value of the insn.
   Targets are free to override CGEN_{ASM,DIS}_HASH in the .opc file.  */

static unsigned int
asm_hash_insn (const char *mnem)
{
  return CGEN_ASM_HASH (mnem);
}

/* BUF is a pointer to the bytes of the insn, target order.
   VALUE is the first base_insn_bitsize bits as an int in host order.  */

static unsigned int
dis_hash_insn (const char *buf ATTRIBUTE_UNUSED,
		     CGEN_INSN_INT value ATTRIBUTE_UNUSED)
{
  return CGEN_DIS_HASH (buf, value);
}

/* Set the recorded length of the insn in the CGEN_FIELDS struct.  */

static void
set_fields_bitsize (CGEN_FIELDS *fields, int size)
{
  CGEN_FIELDS_BITSIZE (fields) = size;
}

/* Function to call before using the operand instance table.
   This plugs the opcode entries and macro instructions into the cpu table.  */

void
bpf_cgen_init_opcode_table (CGEN_CPU_DESC cd)
{
  int i;
  int num_macros = (sizeof (bpf_cgen_macro_insn_table) /
		    sizeof (bpf_cgen_macro_insn_table[0]));
  const CGEN_IBASE *ib = & bpf_cgen_macro_insn_table[0];
  const CGEN_OPCODE *oc = & bpf_cgen_macro_insn_opcode_table[0];
  CGEN_INSN *insns = xmalloc (num_macros * sizeof (CGEN_INSN));

  /* This test has been added to avoid a warning generated
     if memset is called with a third argument of value zero.  */
  if (num_macros >= 1)
    memset (insns, 0, num_macros * sizeof (CGEN_INSN));
  for (i = 0; i < num_macros; ++i)
    {
      insns[i].base = &ib[i];
      insns[i].opcode = &oc[i];
      bpf_cgen_build_insn_regex (& insns[i]);
    }
  cd->macro_insn_table.init_entries = insns;
  cd->macro_insn_table.entry_size = sizeof (CGEN_IBASE);
  cd->macro_insn_table.num_init_entries = num_macros;

  oc = & bpf_cgen_insn_opcode_table[0];
  insns = (CGEN_INSN *) cd->insn_table.init_entries;
  for (i = 0; i < MAX_INSNS; ++i)
    {
      insns[i].opcode = &oc[i];
      bpf_cgen_build_insn_regex (& insns[i]);
    }

  cd->sizeof_fields = sizeof (CGEN_FIELDS);
  cd->set_fields_bitsize = set_fields_bitsize;

  cd->asm_hash_p = asm_hash_insn_p;
  cd->asm_hash = asm_hash_insn;
  cd->asm_hash_size = CGEN_ASM_HASH_SIZE;

  cd->dis_hash_p = dis_hash_insn_p;
  cd->dis_hash = dis_hash_insn;
  cd->dis_hash_size = CGEN_DIS_HASH_SIZE;
}
