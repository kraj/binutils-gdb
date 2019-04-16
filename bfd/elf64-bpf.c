/* Linux bpf specific support for 64-bit ELF
   Copyright (C) 2019 Free Software Foundation, Inc.
   Contributed by Oracle Inc.

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
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "elf-bfd.h"
#include "elf/bpf.h"
#include "libiberty.h"

/* In case we're on a 32-bit machine, construct a 64-bit "-1" value.  */
#define MINUS_ONE (~ (bfd_vma) 0)

#define BASEADDR(SEC)	((SEC)->output_section->vma + (SEC)->output_offset)

/* Relocation tables.  */
static reloc_howto_type bpf_elf_howto_table [] =
{
  HOWTO(R_BPF_NONE,	   0,3, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_SPARC_NONE",	FALSE,0,0x00000000,TRUE),
  HOWTO(R_BPF_64_64,	   0,4,64,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_BPF_64_64",	FALSE,0,MINUS_ONE, TRUE),
  HOWTO(R_BPF_64_32,	   0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_BPF_64_32",	FALSE,0,0xffffffff,TRUE),
};
#undef AHOW

/* Map BFD reloc types to bpf ELF reloc types.  */

static reloc_howto_type *
bpf_reloc_type_lookup (bfd * abfd ATTRIBUTE_UNUSED,
                        bfd_reloc_code_real_type code)
{
  /* Note that the bpf_elf_howto_table is indxed by the R_
     constants.  Thus, the order that the howto records appear in the
     table *must* match the order of the relocation types defined in
     include/elf/bpf.h.  */

  switch (code)
    {
    case BFD_RELOC_NONE:
      return &bpf_elf_howto_table[ (int) R_BPF_NONE];

    case BFD_RELOC_BPF_64_64:
      return &bpf_elf_howto_table[ (int) R_BPF_64_64];
    case BFD_RELOC_BPF_64_32:
      return &bpf_elf_howto_table[ (int) R_BPF_64_32];

    default:
      /* Pacify gcc -Wall.  */
      return NULL;
    }
  return NULL;
}

/* Map BFD reloc names to bpf ELF reloc names.  */

static reloc_howto_type *
bpf_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED, const char *r_name)
{
  unsigned int i;

  for (i = 0; i < ARRAY_SIZE (bpf_elf_howto_table); i++)
    if (bpf_elf_howto_table[i].name != NULL
	&& strcasecmp (bpf_elf_howto_table[i].name, r_name) == 0)
      return &bpf_elf_howto_table[i];

  return NULL;
}

/* Set the howto pointer for a bpf reloc.  */

static bfd_boolean
bpf_info_to_howto (bfd *abfd, arelent *bfd_reloc,
                    Elf_Internal_Rela *elf_reloc)
{
  unsigned int r_type;

  r_type = ELF64_R_TYPE (elf_reloc->r_info);
  if (r_type >= (unsigned int) R_BPF_max)
    {
      /* xgettext:c-format */
      _bfd_error_handler (_("%pB: unsupported relocation type %#x"),
                          abfd, r_type);
      bfd_set_error (bfd_error_bad_value);
      return FALSE;
    }

  bfd_reloc->howto = &bpf_elf_howto_table [r_type];
  return TRUE;
}

/* Relocate an bpf ELF section.

   The RELOCATE_SECTION function is called by the new ELF backend linker
   to handle the relocations for a section.

   The relocs are always passed as Rela structures; if the section
   actually uses Rel structures, the r_addend field will always be
   zero.

   This function is responsible for adjusting the section contents as
   necessary, and (if using Rela relocs and generating a relocatable
   output file) adjusting the reloc addend as necessary.

   This function does not have to worry about setting the reloc
   address or the reloc symbol index.

   LOCAL_SYMS is a pointer to the swapped in local symbols.

   LOCAL_SECTIONS is an array giving the section in the input file
   corresponding to the st_shndx field of each local symbol.

   The global hash table entry for the global symbols can be found
   via elf_sym_hashes (input_bfd).

   When generating relocatable output, this function must handle
   STB_LOCAL/STT_SECTION symbols specially.  The output symbol is
   going to be the section symbol corresponding to the output
   section, which means that the addend must be adjusted
   accordingly.  */

static bfd_boolean
bpf_elf_relocate_section (bfd *output_bfd ATTRIBUTE_UNUSED,
                           struct bfd_link_info *info,
                           bfd *input_bfd,
                           asection *input_section,
                           bfd_byte *contents,
                           Elf_Internal_Rela *relocs,
                           Elf_Internal_Sym *local_syms,
                           asection **local_sections)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  Elf_Internal_Rela *rel;
  Elf_Internal_Rela *relend;

  symtab_hdr = & elf_tdata (input_bfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (input_bfd);
  relend     = relocs + input_section->reloc_count;

  for (rel = relocs; rel < relend; rel ++)
    {
      reloc_howto_type *	   howto;
      unsigned long		   r_symndx;
      Elf_Internal_Sym *	   sym;
      asection *		   sec;
      struct elf_link_hash_entry * h;
      bfd_vma			   relocation;
      bfd_reloc_status_type	   r;
      const char *		   name = NULL;
      int			   r_type ATTRIBUTE_UNUSED;

      r_type = ELF64_R_TYPE (rel->r_info);
      r_symndx = ELF64_R_SYM (rel->r_info);
      howto  = bpf_elf_howto_table + ELF64_R_TYPE (rel->r_info);
      h      = NULL;
      sym    = NULL;
      sec    = NULL;

      if (r_symndx < symtab_hdr->sh_info)
	{
	  sym = local_syms + r_symndx;
	  sec = local_sections [r_symndx];
	  relocation = BASEADDR (sec) + sym->st_value;

	  name = bfd_elf_string_from_elf_section
	    (input_bfd, symtab_hdr->sh_link, sym->st_name);
	  name = (name == NULL) ? bfd_section_name (input_bfd, sec) : name;
	}
      else
	{
	  bfd_boolean warned ATTRIBUTE_UNUSED;
	  bfd_boolean unresolved_reloc ATTRIBUTE_UNUSED;
	  bfd_boolean ignored ATTRIBUTE_UNUSED;

	  RELOC_FOR_GLOBAL_SYMBOL (info, input_bfd, input_section, rel,
				   r_symndx, symtab_hdr, sym_hashes,
				   h, sec, relocation,
				   unresolved_reloc, warned, ignored);

	  name = h->root.root.string;
	}

      if (sec != NULL && discarded_section (sec))
	RELOC_AGAINST_DISCARDED_SECTION (info, input_bfd, input_section,
					 rel, 1, relend, howto, 0, contents);

      if (bfd_link_relocatable (info))
	continue;

      /* Relocate.  */
      r = _bfd_final_link_relocate (howto, input_bfd, input_section,
                                    contents, rel->r_offset,
                                    relocation, rel->r_addend);

      if (r != bfd_reloc_ok)
	{
	  const char * msg = NULL;

	  switch (r)
	    {
	    case bfd_reloc_overflow:
	      (*info->callbacks->reloc_overflow)
		(info, (h ? &h->root : NULL), name, howto->name,
		 (bfd_vma) 0, input_bfd, input_section, rel->r_offset);
	      break;

	    case bfd_reloc_undefined:
	      (*info->callbacks->undefined_symbol)
		(info, name, input_bfd, input_section, rel->r_offset, TRUE);
	      break;

	    case bfd_reloc_outofrange:
	      msg = _("internal error: out of range error");
	      break;

	    default:
	      msg = _("internal error: unknown error");
	      break;
	    }

	  if (msg)
	    (*info->callbacks->warning) (info, msg, name, input_bfd,
					 input_section, rel->r_offset);
	}
    }

  return TRUE;
}

/* Set the right machine number, which depends on the endianness of
   the ELF file.  */

static bfd_boolean
bpf_elf_object_p (bfd *abfd)
{
  /* The machine number depends on the endianness of the ELF file.  */
  switch (elf_elfheader (abfd)->e_ident[EI_DATA])
    {
    default:
    case ELFDATA2LSB:
      (void) bfd_default_set_arch_mach (abfd, bfd_arch_bpf, bfd_mach_bpf_le); break;
    case ELFDATA2MSB:
      (void) bfd_default_set_arch_mach (abfd, bfd_arch_bpf, bfd_mach_bpf_be); break;
    }

  return TRUE;
}

/* The macros below configure the architecture.  */

#define TARGET_LITTLE_SYM 	bpf_elf64_le_vec
#define TARGET_LITTLE_NAME 	"elf64-bpfle"

#define TARGET_BIG_SYM		bpf_elf64_be_vec
#define TARGET_BIG_NAME		"elf64-bpfbe"

#define ELF_ARCH bfd_arch_bpf
#define ELF_MACHINE_CODE EM_BPF

#define ELF_MAXPAGESIZE 0x8000 /* XXX: No pages on the bpf  */

#define elf_info_to_howto_rel			bpf_info_to_howto
#define elf_info_to_howto			bpf_info_to_howto

#define elf_backend_may_use_rel_p		1
#define elf_backend_may_use_rela_p		0
#define elf_backend_default_use_rela_p		0

#define elf_backend_can_gc_sections		1
#define elf_backend_relocate_section		bpf_elf_relocate_section

#define elf_symbol_leading_char			'_'
#define bfd_elf64_bfd_reloc_type_lookup		bpf_reloc_type_lookup
#define bfd_elf64_bfd_reloc_name_lookup		bpf_reloc_name_lookup

#define elf_backend_object_p			bpf_elf_object_p

#include "elf64-target.h"
