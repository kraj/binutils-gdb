/* tc-bpf.c -- Assembler for the Linux eBPF.
   Copyright (C) 2018 Free Software Foundation, Inc.
   Contributed by Oracle, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include "as.h"
#include "subsegs.h"
#include "symcat.h"
#include "opcodes/bpf-desc.h"
#include "opcodes/bpf-opc.h"
#include "cgen.h"
#include "elf/common.h"
#include "elf/bpf.h"
#include "dwarf2dbg.h"

const char comment_chars[]        = ";";
const char line_comment_chars[] = "#";
const char line_separator_chars[] = "`";
const char EXP_CHARS[]            = "eE";
const char FLT_CHARS[]            = "fFdD";

/* The target specific pseudo-ops which we support.  */
const pseudo_typeS md_pseudo_table[] =
{
    { NULL,         NULL,             0 }
};



/* Command-line options processing.  */

enum options
{
  OPTION_LITTLE_ENDIAN = OPTION_MD_BASE,
  OPTION_BIG_ENDIAN
};

struct option md_longopts[] =
{
  { "LE", no_argument, NULL, OPTION_LITTLE_ENDIAN },
  { "BE", no_argument, NULL, OPTION_BIG_ENDIAN },
  { NULL,          no_argument, NULL, 0 },
};

size_t md_longopts_size = sizeof (md_longopts);

const char * md_shortopts = "";

extern int target_big_endian; /* Little-endian by default.  */

int
md_parse_option (int c, const char * arg ATTRIBUTE_UNUSED)
{
  switch (c)
    {
    case OPTION_BIG_ENDIAN:
      target_big_endian = 1;
      break;
    case OPTION_LITTLE_ENDIAN:  /* This is the default.  */
      break;
    default:
      return 0;
    }

  return 1;
}

void
md_show_usage (FILE * stream)
{
  fprintf (stream, _("\nBPF options:\n"));
  fprintf (stream, _("\
  --LE			generate code for a little endian machine (default)\n\
  --BE			generate code for a big endian machine\n"));
}


void
md_begin (void)
{
  /* Initialize the `cgen' interface.  */

  /* Set the machine number and endian.  */
  gas_cgen_cpu_desc = bpf_cgen_cpu_open (CGEN_CPU_OPEN_ENDIAN,
                                          target_big_endian ?
                                          CGEN_ENDIAN_BIG : CGEN_ENDIAN_LITTLE,
                                          CGEN_CPU_OPEN_END);
  bpf_cgen_init_asm (gas_cgen_cpu_desc);

  /* This is a callback from cgen to gas to parse operands.  */
  cgen_set_parse_operand_fn (gas_cgen_cpu_desc, gas_cgen_parse_operand);

  /* Set the machine type.  */
  bfd_default_set_arch_mach (stdoutput, bfd_arch_bpf,
                             target_big_endian ? bfd_mach_bpf_be : bfd_mach_bpf_le);
}

valueT
md_section_align (segT segment, valueT size)
{
  int align = bfd_get_section_alignment (stdoutput, segment);

  return ((size + (1 << align) - 1) & -(1 << align));
}


/* Functions concerning relocs.  */

long
md_pcrel_from (fixS *fixP ATTRIBUTE_UNUSED)
{
  abort ();
}

/* Write a value out to the object file, using the appropriate endianness.  */

void
md_number_to_chars (char * buf, valueT val, int n)
{
  if (target_big_endian)
    number_to_chars_bigendian (buf, val, n);
  else
    number_to_chars_littleendian (buf, val, n);
}

arelent *
tc_gen_reloc (asection *sec, fixS *fix)
{
  return gas_cgen_tc_gen_reloc (sec, fix);
}

/* Return the bfd reloc type for OPERAND of INSN at fixup FIXP.  This
   is called when the operand is an expression that couldn't be fully
   resolved.  Returns BFD_RELOC_NONE if no reloc type can be found.
   *FIXP may be modified if desired.  */

bfd_reloc_code_real_type
md_cgen_lookup_reloc (const CGEN_INSN *insn ATTRIBUTE_UNUSED,
		      const CGEN_OPERAND *operand,
		      fixS *fixP ATTRIBUTE_UNUSED)
{
  switch (operand->type)
    {
    case BPF_OPERAND_IMM64:
      return BFD_RELOC_BPF_64_64;
      /*    case EPIPHANY_OPERAND_IMM16:
      if (0 == strcmp ("movt", CGEN_INSN_MNEMONIC (insn)))
	return BFD_RELOC_EPIPHANY_HIGH;
      else if (0 == strcmp ("mov", CGEN_INSN_MNEMONIC (insn)))
	return BFD_RELOC_EPIPHANY_LOW;
      else
      as_bad ("unknown imm16 operand");*/
    default:
      break;
    }
  return BFD_RELOC_NONE;
}

/* *FRAGP has been relaxed to its final size, and now needs to have
   the bytes inside it modified to conform to the new size.

   Called after relaxation is finished.
   fragP->fr_type == rs_machine_dependent.
   fragP->fr_subtype is the subtype of what the address relaxed to.  */

void
md_convert_frag (bfd *abfd ATTRIBUTE_UNUSED,
		 segT sec ATTRIBUTE_UNUSED,
		 fragS *fragP ATTRIBUTE_UNUSED)
{
  as_fatal (_("convert_frag called"));
}

int
md_estimate_size_before_relax (fragS *fragP ATTRIBUTE_UNUSED,
                               segT segment ATTRIBUTE_UNUSED)
{
  as_fatal (_("estimate_size_before_relax called"));
  return 0;
}


/* Parse %-operands.  XXX: writeme  */

int
bpf_cgen_parse_fix_exp (int opinfo, expressionS *exp ATTRIBUTE_UNUSED)
{
  switch (opinfo)
    {
    case BFD_RELOC_BPF_64_64:
    case BFD_RELOC_BPF_64_32:
      break;
    default:
      return opinfo;
    }

  /* XXX: writeme.  */
  return opinfo;
}

void
md_apply_fix (fixS *fixP, valueT *valP, segT seg)
{
  return gas_cgen_md_apply_fix (fixP, valP, seg);
}

void
md_assemble (char *str)
{
  const CGEN_INSN *insn;
  char *errmsg;
  CGEN_FIELDS fields;

#if CGEN_INT_INSN_P
  CGEN_INSN_INT buffer[CGEN_MAX_INSN_SIZE / sizeof (CGEN_INT_INSN_P)];
#else
  unsigned char buffer[CGEN_MAX_INSN_SIZE];
#endif

  gas_cgen_init_parse ();
  insn = bpf_cgen_assemble_insn (gas_cgen_cpu_desc, str, &fields,
                                  buffer, &errmsg);

  if (insn == NULL)
    {
      as_bad ("%s", errmsg);
      return;
    }

  gas_cgen_finish_insn (insn, buffer, CGEN_FIELDS_BITSIZE (&fields),
                        0, /* zero to ban relaxable insns.  */
                        NULL); /* NULL so results not returned here.  */
}

void
md_operand (expressionS *expressionP)
{
  gas_cgen_md_operand (expressionP);
}


symbolS *
md_undefined_symbol (char *name ATTRIBUTE_UNUSED)
{
  return NULL;
}


/* Turn a string in input_line_pointer into a floating point constant
   of type TYPE, and store the appropriate bytes in *LITP.  The number
   of LITTLENUMS emitted is stored in *SIZEP.  An error message is
   returned, or NULL on OK.  */

const char *
md_atof (int type, char *litP, int *sizeP)
{
  return ieee_md_atof (type, litP, sizeP, FALSE);
}
