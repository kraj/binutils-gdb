/* RISC-V ELF specific backend routines.
   Copyright (C) 2011-2025 Free Software Foundation, Inc.

   Contributed by Andrew Waterman (andrew@sifive.com).
   Based on MIPS target.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3. If not,
   see <http://www.gnu.org/licenses/>.  */

#include "elf/common.h"
#include "elf/internal.h"
#include "opcode/riscv.h"
#include "cpu-riscv.h"

#define RISCV_UNKNOWN_VERSION -1

typedef enum
{
    PLT_NORMAL            = 0x0,  /* Normal plts.  */
    PLT_ZICFILP_UNLABELED = 0x1   /* Landing pad unlabeled plts.  */
} riscv_plt_type;

struct riscv_elf_params
{
  /* Whether to relax code sequences to GP-relative addressing.  */
  bool relax_gp;
  /* Whether to check if SUB_ULEB128 relocation has non-zero addend.  */
  bool check_uleb128;
};

extern void riscv_elf32_set_options (struct bfd_link_info *,
				     struct riscv_elf_params *);
extern void riscv_elf64_set_options (struct bfd_link_info *,
				     struct riscv_elf_params *);

extern reloc_howto_type *
riscv_reloc_name_lookup (bfd *, const char *);

extern reloc_howto_type *
riscv_reloc_type_lookup (bfd *, bfd_reloc_code_real_type);

extern reloc_howto_type *
riscv_elf_rtype_to_howto (bfd *, unsigned int r_type);

/* The information of architecture attribute.  */
struct riscv_subset_t
{
  const char *name;
  int major_version;
  int minor_version;
  struct riscv_subset_t *next;
};

typedef struct riscv_subset_t riscv_subset_t;

typedef struct
{
  riscv_subset_t *head;
  riscv_subset_t *tail;
  const char *arch_str;
} riscv_subset_list_t;

extern void
riscv_release_subset_list (riscv_subset_list_t *);

extern void
riscv_add_subset (riscv_subset_list_t *,
		  const char *,
		  int, int);

extern bool
riscv_lookup_subset (const riscv_subset_list_t *,
		     const char *,
		     riscv_subset_t **);

typedef struct
{
  riscv_subset_list_t *subset_list;
  void (*error_handler) (const char *,
			 ...) ATTRIBUTE_PRINTF_1;
  unsigned *xlen;
  enum riscv_spec_class *isa_spec;
  bool check_unknown_prefixed_ext;
} riscv_parse_subset_t;

extern bool
riscv_parse_subset (riscv_parse_subset_t *,
		    const char *);

extern void
riscv_release_subset_list (riscv_subset_list_t *);

extern char *
riscv_arch_str (unsigned, riscv_subset_list_t *, bool);

extern size_t
riscv_estimate_digit (unsigned);

extern int
riscv_compare_subsets (const char *, const char *);

extern riscv_subset_list_t *
riscv_copy_subset_list (riscv_subset_list_t *);

extern bool
riscv_update_subset (riscv_parse_subset_t *, const char *);

extern bool
riscv_update_subset_norvc (riscv_parse_subset_t *);

extern bool
riscv_subset_supports (riscv_parse_subset_t *, const char *);

extern bool
riscv_multi_subset_supports (riscv_parse_subset_t *, enum riscv_insn_class);

extern const char *
riscv_multi_subset_supports_ext (riscv_parse_subset_t *, enum riscv_insn_class);

extern void
riscv_print_extensions (void);

extern void
bfd_elf32_riscv_set_data_segment_info (struct bfd_link_info *, int *);
extern void
bfd_elf64_riscv_set_data_segment_info (struct bfd_link_info *, int *);

extern bfd *
_bfd_riscv_elf_link_setup_gnu_properties (struct bfd_link_info *, uint32_t *);

extern enum elf_property_kind
_bfd_riscv_elf_parse_gnu_properties (bfd *, unsigned int, bfd_byte *,
				     unsigned int);

extern bool
_bfd_riscv_elf_merge_gnu_properties (struct bfd_link_info *, bfd *,
				     elf_property *, elf_property *, uint32_t);

#define elf_backend_parse_gnu_properties _bfd_riscv_elf_parse_gnu_properties
