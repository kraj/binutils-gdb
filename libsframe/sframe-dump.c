/* sframe-dump.c - Textual dump of .sframe.

   Copyright (C) 2022-2025 Free Software Foundation, Inc.

   This file is part of libsframe.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "sframe-impl.h"

/* Return TRUE if the SFrame section is associated with the aarch64 ABIs.  */

static bool
is_sframe_abi_arch_aarch64 (sframe_decoder_ctx *sfd_ctx)
{
  bool aarch64_p = false;

  uint8_t abi_arch = sframe_decoder_get_abi_arch (sfd_ctx);
  if (abi_arch == SFRAME_ABI_AARCH64_ENDIAN_BIG
      || abi_arch == SFRAME_ABI_AARCH64_ENDIAN_LITTLE)
    aarch64_p = true;

  return aarch64_p;
}

/* Return TRUE if the SFrame section is associated with the s390x ABI.  */

static bool
is_sframe_abi_arch_s390x (sframe_decoder_ctx *sfd_ctx)
{
  return sframe_decoder_get_abi_arch (sfd_ctx) == SFRAME_ABI_S390X_ENDIAN_BIG;
}

static void
dump_sframe_header_flags (sframe_decoder_ctx *sfd_ctx)
{
  uint8_t flags;
  const char *prefix = "Flags: ";

  flags = sframe_decoder_get_flags (sfd_ctx);
  if (!flags)
    {
      printf ("%11sNONE\n", prefix);
      return;
    }

#define PRINT_FLAG(x) \
  if (flags & (x)) \
    { flags = (flags & ~(x)); \
      printf ("%11s%s%s\n", prefix, #x, flags ? "," : ""); \
      prefix = " "; \
    }

  PRINT_FLAG (SFRAME_F_FDE_SORTED);
  PRINT_FLAG (SFRAME_F_FRAME_POINTER);
  PRINT_FLAG (SFRAME_F_FDE_FUNC_START_PCREL);
#undef PRINT_FLAG

  /* Print any residual flags, should this implementation be out of sync when
     new flags are added.  */
  if (flags)
    printf ("%11s%d\n", prefix, flags);
}

static void
dump_sframe_header (sframe_decoder_ctx *sfd_ctx)
{
  uint8_t ver;
  const char *ver_str = NULL;
  int8_t cfa_fixed_fp_offset;
  int8_t cfa_fixed_ra_offset;
  const sframe_header *header = &(sfd_ctx->sfd_header);

  /* Prepare SFrame section version string.  */
  const char *version_names[]
    = { "NULL",
	"SFRAME_VERSION_1",
	"SFRAME_VERSION_2" };

  ver = sframe_decoder_get_version (sfd_ctx);
  if (ver <= SFRAME_VERSION)
    ver_str = version_names[ver];

  /* CFA fixed FP and RA offsets.  */
  cfa_fixed_fp_offset = header->sfh_cfa_fixed_fp_offset;
  cfa_fixed_ra_offset = header->sfh_cfa_fixed_ra_offset;

  const char* subsec_name = "Header";
  printf ("\n");
  printf ("  %s :\n", subsec_name);
  printf ("\n");
  printf ("    Version: %s\n", ver_str);

  dump_sframe_header_flags (sfd_ctx);

  if (cfa_fixed_fp_offset != SFRAME_CFA_FIXED_FP_INVALID)
    printf ("    CFA fixed FP offset: %d\n", cfa_fixed_fp_offset);
  if (cfa_fixed_ra_offset != SFRAME_CFA_FIXED_RA_INVALID)
    printf ("    CFA fixed RA offset: %d\n", cfa_fixed_ra_offset);
  printf ("    Num FDEs: %d\n", sframe_decoder_get_num_fidx (sfd_ctx));
  printf ("    Num FREs: %d\n", header->sfh_num_fres);
}

static void
dump_sframe_func_with_fres (sframe_decoder_ctx *sfd_ctx,
			    unsigned int funcidx,
			    uint64_t sec_addr)
{
  uint32_t j = 0;
  uint32_t num_fres = 0;
  uint32_t func_size = 0;
  int32_t func_start_address = 0;
  unsigned char func_info = 0;

  uint64_t func_start_pc_vma = 0;
  uint64_t fre_start_pc_vma = 0;
  const char *base_reg_str[] = {"fp", "sp"};
  int32_t cfa_offset = 0;
  int32_t fp_offset = 0;
  int32_t ra_offset = 0;
  uint8_t base_reg_id = 0;
  int err[3] = {0, 0, 0};

  sframe_frame_row_entry fre;

  /* Get the SFrame function descriptor.  */
  sframe_decoder_get_funcdesc (sfd_ctx, funcidx, &num_fres,
			       &func_size, &func_start_address, &func_info);
/* Calculate the virtual memory address for function start pc.  Some older
   SFrame V2 sections in ET_DYN or ET_EXEC may still have the
   SFRAME_F_FDE_FUNC_START_PCREL flag unset, and hence may be using the
   old encoding.  Continue to support dumping the sections at least.  */
  func_start_pc_vma = func_start_address + sec_addr;
  if (sframe_decoder_get_flags (sfd_ctx) & SFRAME_F_FDE_FUNC_START_PCREL)
    func_start_pc_vma += sframe_decoder_get_offsetof_fde_start_addr (sfd_ctx,
								     funcidx,
								     NULL);

  /* Mark FDEs with [m] where the FRE start address is interpreted as a
     mask.  */
  int fde_type_addrmask_p = (SFRAME_V1_FUNC_FDE_TYPE (func_info)
			     == SFRAME_FDE_TYPE_PCMASK);
  const char *fde_type_marker
    = (fde_type_addrmask_p ? "[m]" : "   ");

  printf ("\n    func idx [%d]: pc = 0x%"PRIx64 ", size = %d bytes",
	  funcidx,
	  func_start_pc_vma,
	  func_size);

  if (is_sframe_abi_arch_aarch64 (sfd_ctx)
      && (SFRAME_V1_FUNC_PAUTH_KEY (func_info) == SFRAME_AARCH64_PAUTH_KEY_B))
    printf (", pauth = B key");

  char temp[100];

  printf ("\n    %-7s%-8s %-10s%-10s%-13s",
	  "STARTPC", fde_type_marker, "CFA", "FP", "RA");
  for (j = 0; j < num_fres; j++)
    {
      sframe_decoder_get_fre (sfd_ctx, funcidx, j, &fre);

      fre_start_pc_vma = (fde_type_addrmask_p
			  ? fre.fre_start_addr
			  : func_start_pc_vma + fre.fre_start_addr);

      /* FIXME - fixup the err caching in array.
	 assert no error for base reg id.  */
      base_reg_id = sframe_fre_get_base_reg_id (&fre, &err[0]);
      cfa_offset = sframe_fre_get_cfa_offset (sfd_ctx, &fre, &err[0]);
      fp_offset = sframe_fre_get_fp_offset (sfd_ctx, &fre, &err[1]);
      ra_offset = sframe_fre_get_ra_offset (sfd_ctx, &fre, &err[2]);

      /* Dump CFA info.  */
      printf ("\n");
      printf ("    %016"PRIx64, fre_start_pc_vma);
      sprintf (temp, "%s+%d", base_reg_str[base_reg_id], cfa_offset);
      printf ("  %-10s", temp);

      /* Dump SP/FP info.  */
      if (err[1] == 0)
	{
	  if (is_sframe_abi_arch_s390x (sfd_ctx)
	      && SFRAME_V2_S390X_OFFSET_IS_REGNUM (fp_offset))
	    sprintf (temp, "r%d", SFRAME_V2_S390X_OFFSET_DECODE_REGNUM (fp_offset));
	  else
	    sprintf (temp, "c%+d", fp_offset);
	}
      else
	strcpy (temp, "u");
      printf ("%-10s", temp);

      /* Dump RA info.
	 If an ABI does not track RA offset, e.g., AMD64, display 'f',
	 else display the offset d as 'c+-d'.  */
      if (sframe_decoder_get_fixed_ra_offset (sfd_ctx)
	  != SFRAME_CFA_FIXED_RA_INVALID)
	strcpy (temp, "f");
      /* If an ABI does track RA offset, e.g. s390x, it can be a padding
	 to represent FP without RA being saved on stack.  */
      else if (err[2] == 0 && ra_offset == SFRAME_FRE_RA_OFFSET_INVALID)
	sprintf (temp, "U");
      else if (err[2] == 0)
	{
	  if (is_sframe_abi_arch_s390x (sfd_ctx)
	      && SFRAME_V2_S390X_OFFSET_IS_REGNUM (ra_offset))
	    sprintf (temp, "r%d", SFRAME_V2_S390X_OFFSET_DECODE_REGNUM (ra_offset));
	  else
	    sprintf (temp, "c%+d", ra_offset);
	}
      else
	strcpy (temp, "u");

      /* Mark SFrame FRE's RA information with "[s]" if the RA is mangled
	 with signature bits.  */
      const char *ra_mangled_p_str
	= ((sframe_fre_get_ra_mangled_p (sfd_ctx, &fre, &err[2]))
	   ? "[s]" : "   ");
      strcat (temp, ra_mangled_p_str);
      printf ("%-13s", temp);
    }
}

static void
dump_sframe_functions (sframe_decoder_ctx *sfd_ctx, uint64_t sec_addr)
{
  uint32_t i;
  uint32_t num_fdes;

  const char* subsec_name = "Function Index";
  printf ("\n  %s :\n", subsec_name);

  num_fdes = sframe_decoder_get_num_fidx (sfd_ctx);
  for (i = 0; i < num_fdes; i++)
    {
      dump_sframe_func_with_fres (sfd_ctx, i, sec_addr);
      printf ("\n");
    }
}

void
dump_sframe (sframe_decoder_ctx *sfd_ctx, uint64_t sec_addr)
{
  uint8_t ver;

  dump_sframe_header (sfd_ctx);

  ver = sframe_decoder_get_version (sfd_ctx);
  if (ver == SFRAME_VERSION)
    dump_sframe_functions (sfd_ctx, sec_addr);
  else
    printf ("\n No further information can be displayed.  %s",
	    "SFrame version not supported\n");
}
