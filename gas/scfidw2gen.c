/* scfidw2gen.c - Support for emission of synthesized Dwarf2 CFI.
   Copyright (C) 2003-2023 Free Software Foundation, Inc.

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
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#include "as.h"
#include "dw2gencfi.h"
#include "subsegs.h"
#include "scfidw2gen.h"

void
scfi_dot_cfi_startproc (symbolS *start_sym)
{
  if (frchain_now->frch_cfi_data != NULL)
    {
      as_bad (_("previous CFI entry not closed (missing .cfi_endproc)"));
      return;
    }

  cfi_new_fde (start_sym);

  cfi_set_sections ();

  frchain_now->frch_cfi_data->cur_cfa_offset = 0;

  /* By default, SCFI machinery assumes .cfi_startproc is used without
     parameter simple.  */
  tc_cfi_frame_initial_instructions ();

  if ((all_cfi_sections & CFI_EMIT_target) != 0)
    tc_cfi_startproc ();
}

void
scfi_dot_cfi_endproc (symbolS *end_sym)
{
  struct fde_entry *fde_last;

  if (frchain_now->frch_cfi_data == NULL)
    {
      as_bad (_(".cfi_endproc without corresponding .cfi_startproc"));
      return;
    }

  fde_last = frchain_now->frch_cfi_data->cur_fde_data;
  cfi_set_last_fde (fde_last);

  cfi_end_fde (end_sym);

  if ((all_cfi_sections & CFI_EMIT_target) != 0)
    tc_cfi_endproc (fde_last);
}

void
scfi_dot_cfi (int arg, unsigned reg1, unsigned reg2, offsetT offset, symbolS *advloc)
{
  if (frchain_now->frch_cfi_data == NULL)
    {
      as_bad (_("CFI instruction used without previous .cfi_startproc"));
      // ignore_rest_of_line ();
      return;
    }

  /* If the last address was not at the current PC, advance to current.  */
  if (frchain_now->frch_cfi_data->last_address != advloc)
    cfi_add_advance_loc (advloc);

  switch (arg)
    {
    case DW_CFA_offset:
      // reg1 = cfi_parse_reg ();
      // cfi_parse_separator ();
      // offset = cfi_parse_const ();
      cfi_add_CFA_offset (reg1, offset);
      break;

    case DW_CFA_val_offset:
      // reg1 = cfi_parse_reg ();
      // cfi_parse_separator ();
      // offset = cfi_parse_const ();
      cfi_add_CFA_val_offset (reg1, offset);
      break;

    case CFI_rel_offset:
      // reg1 = cfi_parse_reg ();
      // cfi_parse_separator ();
      // offset = cfi_parse_const ();
      cfi_add_CFA_offset (reg1,
			  offset - frchain_now->frch_cfi_data->cur_cfa_offset);
      break;

    case DW_CFA_def_cfa:
      // reg1 = cfi_parse_reg ();
      // cfi_parse_separator ();
      // offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa (reg1, offset);
      break;

    case DW_CFA_register:
      // reg1 = cfi_parse_reg ();
      // cfi_parse_separator ();
      // reg2 = cfi_parse_reg ();
      cfi_add_CFA_register (reg1, reg2);
      break;

    case DW_CFA_def_cfa_register:
      // reg1 = cfi_parse_reg ();
      cfi_add_CFA_def_cfa_register (reg1);
      break;

    case DW_CFA_def_cfa_offset:
      // offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa_offset (offset);
      break;

    case CFI_adjust_cfa_offset:
      // offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa_offset (frchain_now->frch_cfi_data->cur_cfa_offset
				  + offset);
      break;

    case DW_CFA_restore:
      cfi_add_CFA_restore (reg1);
      break;

    case DW_CFA_remember_state:
      cfi_add_CFA_remember_state ();
      break;

    case DW_CFA_restore_state:
      cfi_add_CFA_restore_state ();
      break;

/*
    case DW_CFA_undefined:
      for (;;)
	{
	  reg1 = cfi_parse_reg ();
	  cfi_add_CFA_undefined (reg1);
	  SKIP_WHITESPACE ();
	  if (*input_line_pointer != ',')
	    break;
	  ++input_line_pointer;
	}
      break;

    case DW_CFA_same_value:
      reg1 = cfi_parse_reg ();
      cfi_add_CFA_same_value (reg1);
      break;

    case CFI_return_column:
      reg1 = cfi_parse_reg ();
      cfi_set_return_column (reg1);
      break;

    case DW_CFA_GNU_window_save:
      cfi_add_CFA_insn (DW_CFA_GNU_window_save);
      break;

    case CFI_signal_frame:
      frchain_now->frch_cfi_data->cur_fde_data->signal_frame = 1;
      break;
*/
    default:
      abort ();
    }

  // demand_empty_rest_of_line ();
}
