/* DO NOT EDIT!  -*- buffer-read-only: t -*- vi:set ro:  */
/* CPU data for bpf.

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
#include <stdio.h>
#include <stdarg.h>
#include "ansidecl.h"
#include "bfd.h"
#include "symcat.h"
#include "bpf-desc.h"
#include "bpf-opc.h"
#include "opintl.h"
#include "libiberty.h"
#include "xregex.h"

/* Attributes.  */

static const CGEN_ATTR_ENTRY bool_attr[] =
{
  { "#f", 0 },
  { "#t", 1 },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY MACH_attr[] ATTRIBUTE_UNUSED =
{
  { "base", MACH_BASE },
  { "bpf_le", MACH_BPF_LE },
  { "bpf_be", MACH_BPF_BE },
  { "max", MACH_MAX },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY ISA_attr[] ATTRIBUTE_UNUSED =
{
  { "ebpf_isa", ISA_EBPF_ISA },
  { "max", ISA_MAX },
  { 0, 0 }
};

const CGEN_ATTR_TABLE bpf_cgen_ifield_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "RESERVED", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE bpf_cgen_hardware_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "CACHE-ADDR", &bool_attr[0], &bool_attr[0] },
  { "PC", &bool_attr[0], &bool_attr[0] },
  { "PROFILE", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE bpf_cgen_operand_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { "NEGATIVE", &bool_attr[0], &bool_attr[0] },
  { "RELAX", &bool_attr[0], &bool_attr[0] },
  { "SEM-ONLY", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE bpf_cgen_insn_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "ALIAS", &bool_attr[0], &bool_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "UNCOND-CTI", &bool_attr[0], &bool_attr[0] },
  { "COND-CTI", &bool_attr[0], &bool_attr[0] },
  { "SKIP-CTI", &bool_attr[0], &bool_attr[0] },
  { "DELAY-SLOT", &bool_attr[0], &bool_attr[0] },
  { "RELAXABLE", &bool_attr[0], &bool_attr[0] },
  { "RELAXED", &bool_attr[0], &bool_attr[0] },
  { "NO-DIS", &bool_attr[0], &bool_attr[0] },
  { "PBB", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

/* Instruction set variants.  */

static const CGEN_ISA bpf_cgen_isa_table[] = {
  { "ebpf-isa", 32, 64, 64, 128 },
  { 0, 0, 0, 0, 0 }
};

/* Machine variants.  */

static const CGEN_MACH bpf_cgen_mach_table[] = {
  { "bpf:le", "bpf:le", MACH_BPF_LE, 0 },
  { "bpf:be", "bpf:be", MACH_BPF_BE, 0 },
  { 0, 0, 0, 0 }
};

static CGEN_KEYWORD_ENTRY bpf_cgen_opval_h_gpr_entries[] =
{
  { "%a", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "%r1", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "%r2", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "%r3", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "%r4", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "%r5", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "%r6", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "%r7", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "%r8", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "%r9", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "%fp", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "%r0", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "%r10", 10, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD bpf_cgen_opval_h_gpr =
{
  & bpf_cgen_opval_h_gpr_entries[0],
  13,
  0, 0, 0, 0, ""
};


/* The hardware table.  */

#define A(a) (1 << CGEN_HW_##a)

const CGEN_HW_ENTRY bpf_cgen_hw_table[] =
{
  { "h-memory", HW_H_MEMORY, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-sint", HW_H_SINT, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-uint", HW_H_UINT, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-addr", HW_H_ADDR, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-iaddr", HW_H_IADDR, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-gpr", HW_H_GPR, CGEN_ASM_KEYWORD, (PTR) & bpf_cgen_opval_h_gpr, { 0, { { { (1<<MACH_BPF_LE)|(1<<MACH_BPF_BE), 0 } } } } },
  { "h-pc", HW_H_PC, CGEN_ASM_NONE, 0, { 0|A(PROFILE)|A(PC), { { { (1<<MACH_BASE), 0 } } } } },
  { 0, 0, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A


/* The instruction field table.  */

#define A(a) (1 << CGEN_IFLD_##a)

const CGEN_IFLD bpf_cgen_ifld_table[] =
{
  { BPF_F_NIL, "f-nil", 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_ANYOF, "f-anyof", 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OFFSET16, "f-offset16", 0, 32, 31, 16, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_SRC, "f-src", 0, 32, 15, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_DST, "f-dst", 0, 32, 11, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OP_CODE, "f-op-code", 0, 32, 7, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OP_SRC, "f-op-src", 0, 32, 3, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OP_CLASS, "f-op-class", 0, 32, 2, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OP_MODE, "f-op-mode", 0, 32, 7, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_OP_SIZE, "f-op-size", 0, 32, 4, 2, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_IMM32, "f-imm32", 32, 32, 31, 32, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_IMM64_A, "f-imm64-a", 32, 32, 31, 32, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_IMM64_B, "f-imm64-b", 64, 32, 31, 32, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_IMM64_C, "f-imm64-c", 96, 32, 31, 32, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { BPF_F_IMM64, "f-imm64", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { 0, 0, 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A



/* multi ifield declarations */

const CGEN_MAYBE_MULTI_IFLD BPF_F_IMM64_MULTI_IFIELD [];


/* multi ifield definitions */

const CGEN_MAYBE_MULTI_IFLD BPF_F_IMM64_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_IMM64_A] } },
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_IMM64_B] } },
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_IMM64_C] } },
    { 0, { (const PTR) 0 } }
};

/* The operand table.  */

#define A(a) (1 << CGEN_OPERAND_##a)
#define OPERAND(op) BPF_OPERAND_##op

const CGEN_OPERAND bpf_cgen_operand_table[] =
{
/* pc: program counter */
  { "pc", BPF_OPERAND_PC, HW_H_PC, 0, 0,
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_NIL] } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* dst: destination register */
  { "dst", BPF_OPERAND_DST, HW_H_GPR, 11, 4,
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_DST] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* src: source register */
  { "src", BPF_OPERAND_SRC, HW_H_GPR, 15, 4,
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_SRC] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* imm32: 32-bit immediate */
  { "imm32", BPF_OPERAND_IMM32, HW_H_SINT, 31, 32,
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_IMM32] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* imm64: 64-bit immediate */
  { "imm64", BPF_OPERAND_IMM64, HW_H_SINT, 31, 96,
    { 3, { (const PTR) &BPF_F_IMM64_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* offset16: 16-bit offset */
  { "offset16", BPF_OPERAND_OFFSET16, HW_H_SINT, 31, 16,
    { 0, { (const PTR) &bpf_cgen_ifld_table[BPF_F_OFFSET16] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* sentinel */
  { 0, 0, 0, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A


/* The instruction table.  */

#define OP(field) CGEN_SYNTAX_MAKE_FIELD (OPERAND (field))
#define A(a) (1 << CGEN_INSN_##a)

static const CGEN_IBASE bpf_cgen_insn_table[MAX_INSNS] =
{
  /* Special null first entry.
     A `num' value of zero is thus invalid.
     Also, the special `invalid' insn resides here.  */
  { 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
/* add $dst,$imm32 */
  {
    BPF_INSN_ADDI, "addi", "add", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* add $dst,$src */
  {
    BPF_INSN_ADDR, "addr", "add", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* add32 $dst,$imm32 */
  {
    BPF_INSN_ADD32I, "add32i", "add32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* add32 $dst,$src */
  {
    BPF_INSN_ADD32R, "add32r", "add32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub $dst,$imm32 */
  {
    BPF_INSN_SUBI, "subi", "sub", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub $dst,$src */
  {
    BPF_INSN_SUBR, "subr", "sub", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub32 $dst,$imm32 */
  {
    BPF_INSN_SUB32I, "sub32i", "sub32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub32 $dst,$src */
  {
    BPF_INSN_SUB32R, "sub32r", "sub32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mul $dst,$imm32 */
  {
    BPF_INSN_MULI, "muli", "mul", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mul $dst,$src */
  {
    BPF_INSN_MULR, "mulr", "mul", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mul32 $dst,$imm32 */
  {
    BPF_INSN_MUL32I, "mul32i", "mul32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mul32 $dst,$src */
  {
    BPF_INSN_MUL32R, "mul32r", "mul32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* div $dst,$imm32 */
  {
    BPF_INSN_DIVI, "divi", "div", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* div $dst,$src */
  {
    BPF_INSN_DIVR, "divr", "div", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* div32 $dst,$imm32 */
  {
    BPF_INSN_DIV32I, "div32i", "div32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* div32 $dst,$src */
  {
    BPF_INSN_DIV32R, "div32r", "div32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* or $dst,$imm32 */
  {
    BPF_INSN_ORI, "ori", "or", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* or $dst,$src */
  {
    BPF_INSN_ORR, "orr", "or", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* or32 $dst,$imm32 */
  {
    BPF_INSN_OR32I, "or32i", "or32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* or32 $dst,$src */
  {
    BPF_INSN_OR32R, "or32r", "or32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* and $dst,$imm32 */
  {
    BPF_INSN_ANDI, "andi", "and", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* and $dst,$src */
  {
    BPF_INSN_ANDR, "andr", "and", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* and32 $dst,$imm32 */
  {
    BPF_INSN_AND32I, "and32i", "and32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* and32 $dst,$src */
  {
    BPF_INSN_AND32R, "and32r", "and32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsh $dst,$imm32 */
  {
    BPF_INSN_LSHI, "lshi", "lsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsh $dst,$src */
  {
    BPF_INSN_LSHR, "lshr", "lsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsh32 $dst,$imm32 */
  {
    BPF_INSN_LSH32I, "lsh32i", "lsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsh32 $dst,$src */
  {
    BPF_INSN_LSH32R, "lsh32r", "lsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* rsh $dst,$imm32 */
  {
    BPF_INSN_RSHI, "rshi", "rsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* rsh $dst,$src */
  {
    BPF_INSN_RSHR, "rshr", "rsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* rsh32 $dst,$imm32 */
  {
    BPF_INSN_RSH32I, "rsh32i", "rsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* rsh32 $dst,$src */
  {
    BPF_INSN_RSH32R, "rsh32r", "rsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mod $dst,$imm32 */
  {
    BPF_INSN_MODI, "modi", "mod", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mod $dst,$src */
  {
    BPF_INSN_MODR, "modr", "mod", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mod32 $dst,$imm32 */
  {
    BPF_INSN_MOD32I, "mod32i", "mod32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mod32 $dst,$src */
  {
    BPF_INSN_MOD32R, "mod32r", "mod32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* xor $dst,$imm32 */
  {
    BPF_INSN_XORI, "xori", "xor", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* xor $dst,$src */
  {
    BPF_INSN_XORR, "xorr", "xor", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* xor32 $dst,$imm32 */
  {
    BPF_INSN_XOR32I, "xor32i", "xor32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* xor32 $dst,$src */
  {
    BPF_INSN_XOR32R, "xor32r", "xor32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov $dst,$imm32 */
  {
    BPF_INSN_MOVI, "movi", "mov", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov $dst,$src */
  {
    BPF_INSN_MOVR, "movr", "mov", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov32 $dst,$imm32 */
  {
    BPF_INSN_MOV32I, "mov32i", "mov32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov32 $dst,$src */
  {
    BPF_INSN_MOV32R, "mov32r", "mov32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* arsh $dst,$imm32 */
  {
    BPF_INSN_ARSHI, "arshi", "arsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* arsh $dst,$src */
  {
    BPF_INSN_ARSHR, "arshr", "arsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* arsh32 $dst,$imm32 */
  {
    BPF_INSN_ARSH32I, "arsh32i", "arsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* arsh32 $dst,$src */
  {
    BPF_INSN_ARSH32R, "arsh32r", "arsh32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* neg $dst */
  {
    BPF_INSN_NEG, "neg", "neg", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* neg32 $dst */
  {
    BPF_INSN_NEG32, "neg32", "neg32", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* lddw $dst,$imm64 */
  {
    BPF_INSN_LDDW, "lddw", "lddw", 128,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldabsw $src,$dst,$imm32 */
  {
    BPF_INSN_LDABSW, "ldabsw", "ldabsw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldabsh $src,$dst,$imm32 */
  {
    BPF_INSN_LDABSH, "ldabsh", "ldabsh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldabsb $src,$dst,$imm32 */
  {
    BPF_INSN_LDABSB, "ldabsb", "ldabsb", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldabsdw $src,$dst,$imm32 */
  {
    BPF_INSN_LDABSDW, "ldabsdw", "ldabsdw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldindw $src,$dst,$imm32 */
  {
    BPF_INSN_LDINDW, "ldindw", "ldindw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldindh $src,$dst,$imm32 */
  {
    BPF_INSN_LDINDH, "ldindh", "ldindh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldindb $src,$dst,$imm32 */
  {
    BPF_INSN_LDINDB, "ldindb", "ldindb", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldinddw $src,$dst,$imm32 */
  {
    BPF_INSN_LDINDDW, "ldinddw", "ldinddw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldxw $dst,[$src+$offset16] */
  {
    BPF_INSN_LDXW, "ldxw", "ldxw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldxh $dst,[$src+$offset16] */
  {
    BPF_INSN_LDXH, "ldxh", "ldxh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldxb $dst,[$src+$offset16] */
  {
    BPF_INSN_LDXB, "ldxb", "ldxb", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldxdw $dst,[$src+$offset16] */
  {
    BPF_INSN_LDXDW, "ldxdw", "ldxdw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stw [$dst+$offset16],$imm32 */
  {
    BPF_INSN_STW, "stw", "stw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* sth [$dst+$offset16],$imm32 */
  {
    BPF_INSN_STH, "sth", "sth", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stb [$dst+$offset16],$imm32 */
  {
    BPF_INSN_STB, "stb", "stb", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stdw [$dst+$offset16],$imm32 */
  {
    BPF_INSN_STDW, "stdw", "stdw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stxw [$dst+$offset16],$src */
  {
    BPF_INSN_STXW, "stxw", "stxw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stxh [$dst+$offset16],$src */
  {
    BPF_INSN_STXH, "stxh", "stxh", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stxb [$dst+$offset16],$src */
  {
    BPF_INSN_STXB, "stxb", "stxb", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* stxdw [$dst+$offset16],$src */
  {
    BPF_INSN_STXDW, "stxdw", "stxdw", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* ja +$offset16 */
  {
    BPF_INSN_JA, "ja", "ja", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jeq $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JEQI, "jeqi", "jeq", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jeq $dst,$src,+$offset16 */
  {
    BPF_INSN_JEQR, "jeqr", "jeq", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jgt $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JGTI, "jgti", "jgt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jgt $dst,$src,+$offset16 */
  {
    BPF_INSN_JGTR, "jgtr", "jgt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jge $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JGEI, "jgei", "jge", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jge $dst,$src,+$offset16 */
  {
    BPF_INSN_JGER, "jger", "jge", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jlt $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JLTI, "jlti", "jlt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jlt $dst,$src,+$offset16 */
  {
    BPF_INSN_JLTR, "jltr", "jlt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jle $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JLEI, "jlei", "jle", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jle $dst,$src,+$offset16 */
  {
    BPF_INSN_JLER, "jler", "jle", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jset $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JSETI, "jseti", "jset", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jset $dst,$src,+$offset16 */
  {
    BPF_INSN_JSETR, "jsetr", "jset", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jne $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JNEI, "jnei", "jne", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jne $dst,$src,+$offset16 */
  {
    BPF_INSN_JNER, "jner", "jne", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsgt $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JSGTI, "jsgti", "jsgt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsgt $dst,$src,+$offset16 */
  {
    BPF_INSN_JSGTR, "jsgtr", "jsgt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsge $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JSGEI, "jsgei", "jsge", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsge $dst,$src,+$offset16 */
  {
    BPF_INSN_JSGER, "jsger", "jsge", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jslt $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JSLTI, "jslti", "jslt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jslt $dst,$src,+$offset16 */
  {
    BPF_INSN_JSLTR, "jsltr", "jslt", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsle $dst,$imm32,+$offset16 */
  {
    BPF_INSN_JSLEI, "jslei", "jsle", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* jsle $dst,$src,+$offset16 */
  {
    BPF_INSN_JSLER, "jsler", "jsle", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* call $imm32 */
  {
    BPF_INSN_CALL, "call", "call", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
/* exit */
  {
    BPF_INSN_EXIT, "exit", "exit", 64,
    { 0, { { { (1<<MACH_BASE), 0 } } } }
  },
};

#undef OP
#undef A

/* Initialize anything needed to be done once, before any cpu_open call.  */

static void
init_tables (void)
{
}

#ifndef opcodes_error_handler
#define opcodes_error_handler(...) \
  fprintf (stderr, __VA_ARGS__); fputc ('\n', stderr)
#endif

static const CGEN_MACH * lookup_mach_via_bfd_name (const CGEN_MACH *, const char *);
static void build_hw_table      (CGEN_CPU_TABLE *);
static void build_ifield_table  (CGEN_CPU_TABLE *);
static void build_operand_table (CGEN_CPU_TABLE *);
static void build_insn_table    (CGEN_CPU_TABLE *);
static void bpf_cgen_rebuild_tables (CGEN_CPU_TABLE *);

/* Subroutine of bpf_cgen_cpu_open to look up a mach via its bfd name.  */

static const CGEN_MACH *
lookup_mach_via_bfd_name (const CGEN_MACH *table, const char *name)
{
  while (table->name)
    {
      if (strcmp (name, table->bfd_name) == 0)
	return table;
      ++table;
    }
  return NULL;
}

/* Subroutine of bpf_cgen_cpu_open to build the hardware table.  */

static void
build_hw_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_HW_ENTRY *init = & bpf_cgen_hw_table[0];
  /* MAX_HW is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_HW_ENTRY **selected =
    (const CGEN_HW_ENTRY **) xmalloc (MAX_HW * sizeof (CGEN_HW_ENTRY *));

  cd->hw_table.init_entries = init;
  cd->hw_table.entry_size = sizeof (CGEN_HW_ENTRY);
  memset (selected, 0, MAX_HW * sizeof (CGEN_HW_ENTRY *));
  /* ??? For now we just use machs to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_HW_ATTR_VALUE (&init[i], CGEN_HW_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->hw_table.entries = selected;
  cd->hw_table.num_entries = MAX_HW;
}

/* Subroutine of bpf_cgen_cpu_open to build the hardware table.  */

static void
build_ifield_table (CGEN_CPU_TABLE *cd)
{
  cd->ifld_table = & bpf_cgen_ifld_table[0];
}

/* Subroutine of bpf_cgen_cpu_open to build the hardware table.  */

static void
build_operand_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_OPERAND *init = & bpf_cgen_operand_table[0];
  /* MAX_OPERANDS is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_OPERAND **selected = xmalloc (MAX_OPERANDS * sizeof (* selected));

  cd->operand_table.init_entries = init;
  cd->operand_table.entry_size = sizeof (CGEN_OPERAND);
  memset (selected, 0, MAX_OPERANDS * sizeof (CGEN_OPERAND *));
  /* ??? For now we just use mach to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_OPERAND_ATTR_VALUE (&init[i], CGEN_OPERAND_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->operand_table.entries = selected;
  cd->operand_table.num_entries = MAX_OPERANDS;
}

/* Subroutine of bpf_cgen_cpu_open to build the hardware table.
   ??? This could leave out insns not supported by the specified mach/isa,
   but that would cause errors like "foo only supported by bar" to become
   "unknown insn", so for now we include all insns and require the app to
   do the checking later.
   ??? On the other hand, parsing of such insns may require their hardware or
   operand elements to be in the table [which they mightn't be].  */

static void
build_insn_table (CGEN_CPU_TABLE *cd)
{
  int i;
  const CGEN_IBASE *ib = & bpf_cgen_insn_table[0];
  CGEN_INSN *insns = xmalloc (MAX_INSNS * sizeof (CGEN_INSN));

  memset (insns, 0, MAX_INSNS * sizeof (CGEN_INSN));
  for (i = 0; i < MAX_INSNS; ++i)
    insns[i].base = &ib[i];
  cd->insn_table.init_entries = insns;
  cd->insn_table.entry_size = sizeof (CGEN_IBASE);
  cd->insn_table.num_init_entries = MAX_INSNS;
}

/* Subroutine of bpf_cgen_cpu_open to rebuild the tables.  */

static void
bpf_cgen_rebuild_tables (CGEN_CPU_TABLE *cd)
{
  int i;
  CGEN_BITSET *isas = cd->isas;
  unsigned int machs = cd->machs;

  cd->int_insn_p = CGEN_INT_INSN_P;

  /* Data derived from the isa spec.  */
#define UNSET (CGEN_SIZE_UNKNOWN + 1)
  cd->default_insn_bitsize = UNSET;
  cd->base_insn_bitsize = UNSET;
  cd->min_insn_bitsize = 65535; /* Some ridiculously big number.  */
  cd->max_insn_bitsize = 0;
  for (i = 0; i < MAX_ISAS; ++i)
    if (cgen_bitset_contains (isas, i))
      {
	const CGEN_ISA *isa = & bpf_cgen_isa_table[i];

	/* Default insn sizes of all selected isas must be
	   equal or we set the result to 0, meaning "unknown".  */
	if (cd->default_insn_bitsize == UNSET)
	  cd->default_insn_bitsize = isa->default_insn_bitsize;
	else if (isa->default_insn_bitsize == cd->default_insn_bitsize)
	  ; /* This is ok.  */
	else
	  cd->default_insn_bitsize = CGEN_SIZE_UNKNOWN;

	/* Base insn sizes of all selected isas must be equal
	   or we set the result to 0, meaning "unknown".  */
	if (cd->base_insn_bitsize == UNSET)
	  cd->base_insn_bitsize = isa->base_insn_bitsize;
	else if (isa->base_insn_bitsize == cd->base_insn_bitsize)
	  ; /* This is ok.  */
	else
	  cd->base_insn_bitsize = CGEN_SIZE_UNKNOWN;

	/* Set min,max insn sizes.  */
	if (isa->min_insn_bitsize < cd->min_insn_bitsize)
	  cd->min_insn_bitsize = isa->min_insn_bitsize;
	if (isa->max_insn_bitsize > cd->max_insn_bitsize)
	  cd->max_insn_bitsize = isa->max_insn_bitsize;
      }

  /* Data derived from the mach spec.  */
  for (i = 0; i < MAX_MACHS; ++i)
    if (((1 << i) & machs) != 0)
      {
	const CGEN_MACH *mach = & bpf_cgen_mach_table[i];

	if (mach->insn_chunk_bitsize != 0)
	{
	  if (cd->insn_chunk_bitsize != 0 && cd->insn_chunk_bitsize != mach->insn_chunk_bitsize)
	    {
	      opcodes_error_handler
		(/* xgettext:c-format */
		 _("internal error: bpf_cgen_rebuild_tables: "
		   "conflicting insn-chunk-bitsize values: `%d' vs. `%d'"),
		 cd->insn_chunk_bitsize, mach->insn_chunk_bitsize);
	      abort ();
	    }

 	  cd->insn_chunk_bitsize = mach->insn_chunk_bitsize;
	}
      }

  /* Determine which hw elements are used by MACH.  */
  build_hw_table (cd);

  /* Build the ifield table.  */
  build_ifield_table (cd);

  /* Determine which operands are used by MACH/ISA.  */
  build_operand_table (cd);

  /* Build the instruction table.  */
  build_insn_table (cd);
}

/* Initialize a cpu table and return a descriptor.
   It's much like opening a file, and must be the first function called.
   The arguments are a set of (type/value) pairs, terminated with
   CGEN_CPU_OPEN_END.

   Currently supported values:
   CGEN_CPU_OPEN_ISAS:    bitmap of values in enum isa_attr
   CGEN_CPU_OPEN_MACHS:   bitmap of values in enum mach_attr
   CGEN_CPU_OPEN_BFDMACH: specify 1 mach using bfd name
   CGEN_CPU_OPEN_ENDIAN:  specify endian choice
   CGEN_CPU_OPEN_END:     terminates arguments

   ??? Simultaneous multiple isas might not make sense, but it's not (yet)
   precluded.  */

CGEN_CPU_DESC
bpf_cgen_cpu_open (enum cgen_cpu_open_arg arg_type, ...)
{
  CGEN_CPU_TABLE *cd = (CGEN_CPU_TABLE *) xmalloc (sizeof (CGEN_CPU_TABLE));
  static int init_p;
  CGEN_BITSET *isas = 0;  /* 0 = "unspecified" */
  unsigned int machs = 0; /* 0 = "unspecified" */
  enum cgen_endian endian = CGEN_ENDIAN_UNKNOWN;
  va_list ap;

  if (! init_p)
    {
      init_tables ();
      init_p = 1;
    }

  memset (cd, 0, sizeof (*cd));

  va_start (ap, arg_type);
  while (arg_type != CGEN_CPU_OPEN_END)
    {
      switch (arg_type)
	{
	case CGEN_CPU_OPEN_ISAS :
	  isas = va_arg (ap, CGEN_BITSET *);
	  break;
	case CGEN_CPU_OPEN_MACHS :
	  machs = va_arg (ap, unsigned int);
	  break;
	case CGEN_CPU_OPEN_BFDMACH :
	  {
	    const char *name = va_arg (ap, const char *);
	    const CGEN_MACH *mach =
	      lookup_mach_via_bfd_name (bpf_cgen_mach_table, name);

	    if (mach != NULL)
	      machs |= 1 << mach->num;
	    break;
	  }
	case CGEN_CPU_OPEN_ENDIAN :
	  endian = va_arg (ap, enum cgen_endian);
	  break;
	default :
	  opcodes_error_handler
	    (/* xgettext:c-format */
	     _("internal error: bpf_cgen_cpu_open: "
	       "unsupported argument `%d'"),
	     arg_type);
	  abort (); /* ??? return NULL? */
	}
      arg_type = va_arg (ap, enum cgen_cpu_open_arg);
    }
  va_end (ap);

  /* Mach unspecified means "all".  */
  if (machs == 0)
    machs = (1 << MAX_MACHS) - 1;
  /* Base mach is always selected.  */
  machs |= 1;
  if (endian == CGEN_ENDIAN_UNKNOWN)
    {
      /* ??? If target has only one, could have a default.  */
      opcodes_error_handler
	(/* xgettext:c-format */
	 _("internal error: bpf_cgen_cpu_open: no endianness specified"));
      abort ();
    }

  cd->isas = cgen_bitset_copy (isas);
  cd->machs = machs;
  cd->endian = endian;
  /* FIXME: for the sparc case we can determine insn-endianness statically.
     The worry here is where both data and insn endian can be independently
     chosen, in which case this function will need another argument.
     Actually, will want to allow for more arguments in the future anyway.  */
  cd->insn_endian = endian;

  /* Table (re)builder.  */
  cd->rebuild_tables = bpf_cgen_rebuild_tables;
  bpf_cgen_rebuild_tables (cd);

  /* Default to not allowing signed overflow.  */
  cd->signed_overflow_ok_p = 0;

  return (CGEN_CPU_DESC) cd;
}

/* Cover fn to bpf_cgen_cpu_open to handle the simple case of 1 isa, 1 mach.
   MACH_NAME is the bfd name of the mach.  */

CGEN_CPU_DESC
bpf_cgen_cpu_open_1 (const char *mach_name, enum cgen_endian endian)
{
  return bpf_cgen_cpu_open (CGEN_CPU_OPEN_BFDMACH, mach_name,
			       CGEN_CPU_OPEN_ENDIAN, endian,
			       CGEN_CPU_OPEN_END);
}

/* Close a cpu table.
   ??? This can live in a machine independent file, but there's currently
   no place to put this file (there's no libcgen).  libopcodes is the wrong
   place as some simulator ports use this but they don't use libopcodes.  */

void
bpf_cgen_cpu_close (CGEN_CPU_DESC cd)
{
  unsigned int i;
  const CGEN_INSN *insns;

  if (cd->macro_insn_table.init_entries)
    {
      insns = cd->macro_insn_table.init_entries;
      for (i = 0; i < cd->macro_insn_table.num_init_entries; ++i, ++insns)
	if (CGEN_INSN_RX ((insns)))
	  regfree (CGEN_INSN_RX (insns));
    }

  if (cd->insn_table.init_entries)
    {
      insns = cd->insn_table.init_entries;
      for (i = 0; i < cd->insn_table.num_init_entries; ++i, ++insns)
	if (CGEN_INSN_RX (insns))
	  regfree (CGEN_INSN_RX (insns));
    }

  if (cd->macro_insn_table.init_entries)
    free ((CGEN_INSN *) cd->macro_insn_table.init_entries);

  if (cd->insn_table.init_entries)
    free ((CGEN_INSN *) cd->insn_table.init_entries);

  if (cd->hw_table.entries)
    free ((CGEN_HW_ENTRY *) cd->hw_table.entries);

  if (cd->operand_table.entries)
    free ((CGEN_HW_ENTRY *) cd->operand_table.entries);

  free (cd);
}

