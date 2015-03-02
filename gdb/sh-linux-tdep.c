/* Target-dependent code for GNU/Linux Super-H.

   Copyright (C) 2005-2017 Free Software Foundation, Inc.

   This file is part of GDB.

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

#include "defs.h"
#include "gdbcore.h"
#include "frame.h"
#include "frame-base.h"
#include "frame-unwind.h"
#include "dwarf2-frame.h"
#include "value.h"
#include "regcache.h"
#include "inferior.h"
#include "osabi.h"

#include "reggroups.h"
#include "arch-utils.h"
#include "floatformat.h"
#include "solib-svr4.h"
#include "symtab.h"
#include "gdb_string.h"
#include "command.h"
#include "gdb_assert.h"

#include "trad-frame.h"
#include "tramp-frame.h"

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/user.h>
#include <sys/syscall.h>

#include <asm/ptrace.h>

#include "regset.h"
#include "glibc-tdep.h"
#include "sh-tdep.h"
#include "linux-tdep.h"

#define REGSx16(base) \
  {(base),      0}, \
  {(base) +  1, 4}, \
  {(base) +  2, 8}, \
  {(base) +  3, 12}, \
  {(base) +  4, 16}, \
  {(base) +  5, 20}, \
  {(base) +  6, 24}, \
  {(base) +  7, 28}, \
  {(base) +  8, 32}, \
  {(base) +  9, 36}, \
  {(base) + 10, 40}, \
  {(base) + 11, 44}, \
  {(base) + 12, 48}, \
  {(base) + 13, 52}, \
  {(base) + 14, 56}, \
  {(base) + 15, 60}

/* Describe the contents of the .reg section of the core file.  */

static const struct sh_corefile_regmap gregs_table[] =
{
  REGSx16 (R0_REGNUM),
  {PC_REGNUM,   64},
  {PR_REGNUM,   68},
  {SR_REGNUM,   72},
  {GBR_REGNUM,  76},
  {MACH_REGNUM, 80},
  {MACL_REGNUM, 84},
  {-1 /* Terminator.  */, 0}
};

/* Describe the contents of the .reg2 section of the core file.  */

static const struct sh_corefile_regmap fpregs_table[] =
{
  REGSx16 (FR0_REGNUM),
  /* REGSx16 xfp_regs omitted.  */
  {FPSCR_REGNUM, 128},
  {FPUL_REGNUM,  132},
  {-1 /* Terminator.  */, 0}
};

/* SH signal handler frame support.  */

static void
sh_linux_sigtramp_cache (struct frame_info *this_frame,
			 struct trad_frame_cache *this_cache,
			 CORE_ADDR func, int regs_offset)
{
  int i;
  struct gdbarch *gdbarch = get_frame_arch (this_frame);
  CORE_ADDR base = get_frame_register_unsigned (this_frame,
						gdbarch_sp_regnum (gdbarch));
  CORE_ADDR regs = base + regs_offset;

  for (i = 0; i < 18; i++)
    trad_frame_set_reg_addr (this_cache, i, regs + i * 4);

  trad_frame_set_reg_addr (this_cache, SR_REGNUM, regs + 18 * 4);
  trad_frame_set_reg_addr (this_cache, GBR_REGNUM, regs + 19 * 4);
  trad_frame_set_reg_addr (this_cache, MACH_REGNUM, regs + 20 * 4);
  trad_frame_set_reg_addr (this_cache, MACL_REGNUM, regs + 21 * 4);

  /* Restore FP state if we have an FPU.  */
  if (gdbarch_fp0_regnum (gdbarch) != -1)
    {
      CORE_ADDR fpregs = regs + 22 * 4;
      for (i = FR0_REGNUM; i <= FP_LAST_REGNUM; i++)
	trad_frame_set_reg_addr (this_cache, i, fpregs + i * 4);
      trad_frame_set_reg_addr (this_cache, FPSCR_REGNUM, fpregs + 32 * 4);
      trad_frame_set_reg_addr (this_cache, FPUL_REGNUM, fpregs + 33 * 4);
    }

  /* Save a frame ID.  */
  trad_frame_set_id (this_cache, frame_id_build (base, func));
}

/* Implement struct tramp_frame "init" callbacks for signal
   trampolines on 32-bit SH.  */

static void
sh_linux_sigreturn_init (const struct tramp_frame *self,
			 struct frame_info *this_frame,
			 struct trad_frame_cache *this_cache,
			 CORE_ADDR func)
{
  /* SH 32-bit sigframe: sigcontext at start of sigframe,
     registers start after a single 'oldmask' word.  */
  sh_linux_sigtramp_cache (this_frame, this_cache, func, 4);
}

static void
sh_linux_rt_sigreturn_init (const struct tramp_frame *self,
			    struct frame_info *this_frame,
			    struct trad_frame_cache *this_cache,
			    CORE_ADDR func)
{
  /* SH 32-bit rt_sigframe: starts with a siginfo (128 bytes), then
     we can find sigcontext embedded within a ucontext (offset 20 bytes).
     Then registers start after a single 'oldmask' word.  */
  sh_linux_sigtramp_cache (this_frame, this_cache, func,
			   128 /* sizeof (struct siginfo)  */
			   + 20 /* offsetof (struct ucontext, uc_mcontext) */
			   + 4 /* oldmask word at start of sigcontext */);
}

/* Instruction patterns.  */
#define SH_MOVW     0x9305
#define SH_TRAP     0xc300
#define SH_OR_R0_R0 0x200b       

/* SH sigreturn syscall numbers.  */
#define SH_NR_SIGRETURN 0x0077
#define SH_NR_RT_SIGRETURN 0x00ad

static struct tramp_frame sh_linux_sigreturn_tramp_frame = {
  SIGTRAMP_FRAME,
  2,
  {
    { SH_MOVW, 0xffff },
    { SH_TRAP, 0xff00 }, /* #imm argument part filtered out.  */
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_NR_SIGRETURN, 0xffff },
    { TRAMP_SENTINEL_INSN }
  },
  sh_linux_sigreturn_init
};

static struct tramp_frame sh_linux_rt_sigreturn_tramp_frame = {
  SIGTRAMP_FRAME,
  2,
  {
    { SH_MOVW, 0xffff },
    { SH_TRAP, 0xff00 }, /* #imm argument part filtered out.  */
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_OR_R0_R0, 0xffff },
    { SH_NR_RT_SIGRETURN, 0xffff },
    { TRAMP_SENTINEL_INSN }
  },
  sh_linux_rt_sigreturn_init
};

/* Recognizing signal handler frames.  */

/* GNU/Linux has two flavors of signals.  Normal signal handlers, and
   "realtime" (RT) signals.  The RT signals can provide additional
   information to the signal handler if the SA_SIGINFO flag is set
   when establishing a signal handler using `sigaction'.  It is not
   unlikely that future versions of GNU/Linux will support SA_SIGINFO
   for normal signals too.  */

/* When the SH Linux kernel calls a signal handler and the
   SA_RESTORER flag isn't set, the return address points to a bit of
   code on the stack.  This function returns whether the PC appears to
   be within this bit of code.

   The instruction sequence for normal signals is
       mov.w  1f,r3
       trapa  #16
       or     r0, r0
       or     r0, r0
       or     r0, r0
       or     r0, r0
       or     r0, r0
    1: .word  __NR_sigreturn
   or 0x9305 0xc310 0x200b 0x200b 0x200b 0x200b 0x200b 0x0077.

   Checking for the code sequence should be somewhat reliable, because
   the effect is to call the system call sigreturn.  This is unlikely
   to occur anywhere other than a signal trampoline.

   It kind of sucks that we have to read memory from the process in
   order to identify a signal trampoline, but there doesn't seem to be
   any other way.  The PC_IN_SIGTRAMP macro in tm-linux.h arranges to
   only call us if no function name could be identified, which should
   be the case since the code is on the stack.

   Detection of signal trampolines for handlers that set the
   SA_RESTORER flag is in general not possible.  Unfortunately this is
   what the GNU C Library has been doing for quite some time now.
   However, as of version 2.1.2, the GNU C Library uses signal
   trampolines (named __restore and __restore_rt) that are identical
   to the ones used by the kernel.  Therefore, these trampolines are
   supported too.  */

#define MOVW(n)	 (0x9300|((n)-2))	/* Move mem word at PC+n to R3 */
#define TRAP16	 0xc310			/* Syscall w/no args (NR in R3) */
#define OR_R0_R0 0x200b			/* or r0,r0 (insert to avoid hardware bug) */

#define LINUX_SIGTRAMP_INSN0	MOVW(7)		/* Move mem word at PC+7 to R3 */
#define LINUX_SIGTRAMP_INSN1	TRAP16		/* Syscall w/no args (NR in R3) */
#define LINUX_SIGTRAMP_INSN2	OR_R0_R0	/* or r0,r0 (insert to avoid hardware bug) */

static const unsigned short linux_sigtramp_code[] =
{
  LINUX_SIGTRAMP_INSN0,
  LINUX_SIGTRAMP_INSN1,
  LINUX_SIGTRAMP_INSN2,
  LINUX_SIGTRAMP_INSN2,
  LINUX_SIGTRAMP_INSN2,
  LINUX_SIGTRAMP_INSN2,
  LINUX_SIGTRAMP_INSN2,
  __NR_sigreturn
};

#define LINUX_SIGTRAMP_LEN (sizeof linux_sigtramp_code)

/* If PC is in a sigtramp routine, return the address of the start of
   the routine.  Otherwise, return 0.  */

static CORE_ADDR
sh_linux_sigtramp_start (struct frame_info *next_frame)
{
  CORE_ADDR pc = get_frame_pc (next_frame);
  gdb_byte buf[LINUX_SIGTRAMP_LEN];

  /* We only recognize a signal trampoline if PC is at the start of
     one of the three instructions.  We optimize for finding the PC at
     the start, as will be the case when the trampoline is not the
     first frame on the stack.  We assume that in the case where the
     PC is not at the start of the instruction sequence, there will be
     a few trailing readable bytes on the stack.  */

  if (!safe_frame_unwind_memory (next_frame, pc, buf, LINUX_SIGTRAMP_LEN))
    return 0;

  if (buf[0] != LINUX_SIGTRAMP_INSN0)
    {
      if (buf[0] != LINUX_SIGTRAMP_INSN1)
        return 0;

      pc -= 2;

      if (!safe_frame_unwind_memory (next_frame, pc, buf, LINUX_SIGTRAMP_LEN))
	return 0;
    }

  if (memcmp (buf, linux_sigtramp_code, LINUX_SIGTRAMP_LEN) != 0)
    return 0;

  return pc;
}

/* This function does the same for RT signals.  Here the instruction
   sequence is
       mov.w  1f,r3
       trapa  #16
       or     r0, r0
       or     r0, r0
       or     r0, r0
       or     r0, r0
       or     r0, r0
    1: .word  __NR_rt_sigreturn
   or 0x9305 0xc310 0x200b 0x200b 0x200b 0x200b 0x200b 0x00ad.

   The effect is to call the system call rt_sigreturn.  */

#define LINUX_RT_SIGTRAMP_INSN0		MOVW(7)		/* Move mem word at PC+7 to R3 */
#define LINUX_RT_SIGTRAMP_INSN1		TRAP16		/* Syscall w/no args (NR in R3) */
#define LINUX_RT_SIGTRAMP_INSN2		OR_R0_R0	/* or r0,r0 (insert to avoid hardware bug) */

static const unsigned short linux_rt_sigtramp_code[] =
{
  LINUX_RT_SIGTRAMP_INSN0,
  LINUX_RT_SIGTRAMP_INSN1,
  LINUX_RT_SIGTRAMP_INSN2,
  LINUX_RT_SIGTRAMP_INSN2,
  LINUX_RT_SIGTRAMP_INSN2,
  LINUX_RT_SIGTRAMP_INSN2,
  LINUX_RT_SIGTRAMP_INSN2,
  __NR_rt_sigreturn
};

#define LINUX_RT_SIGTRAMP_LEN (sizeof linux_rt_sigtramp_code)

/* If PC is in a RT sigtramp routine, return the address of the start
   of the routine.  Otherwise, return 0.  */

static CORE_ADDR
sh_linux_rt_sigtramp_start (struct frame_info *next_frame)
{
  CORE_ADDR pc = get_frame_pc (next_frame);
  gdb_byte buf[LINUX_RT_SIGTRAMP_LEN];

  /* We only recognize a signal trampoline if PC is at the start of
     one of the two instructions.  We optimize for finding the PC at
     the start, as will be the case when the trampoline is not the
     first frame on the stack.  We assume that in the case where the
     PC is not at the start of the instruction sequence, there will be
     a few trailing readable bytes on the stack.  */

  if (!safe_frame_unwind_memory (next_frame, pc, buf, LINUX_RT_SIGTRAMP_LEN))
    return 0;

  if (buf[0] != LINUX_RT_SIGTRAMP_INSN0)
    {
      if (buf[0] != LINUX_RT_SIGTRAMP_INSN1)
	return 0;

      pc -= 2;

      if (!safe_frame_unwind_memory (next_frame, pc, buf,
				     LINUX_RT_SIGTRAMP_LEN))
	return 0;
    }

  if (memcmp (buf, linux_rt_sigtramp_code, LINUX_RT_SIGTRAMP_LEN) != 0)
    return 0;

  return pc;
}

/* Return whether PC is in a GNU/Linux sigtramp routine.  */

static int
sh_linux_sigtramp_p (struct frame_info *this_frame)
{
  CORE_ADDR pc = get_frame_pc (this_frame);
  char *name;

  find_pc_partial_function (pc, &name, NULL, NULL);

  /* If we have NAME, we can optimize the search.  The trampolines are
     named __restore and __restore_rt.  However, they aren't dynamically
     exported from the shared C library, so the trampoline may appear to
     be part of the preceding function.  This should always be sigaction,
     __sigaction, or __libc_sigaction (all aliases to the same function).  */
  if (name == NULL || strstr (name, "sigaction") != NULL)
    return (sh_linux_sigtramp_start (this_frame) != 0
	    || sh_linux_rt_sigtramp_start (this_frame) != 0);

  return (strcmp ("__restore", name) == 0
	  || strcmp ("__restore_rt", name) == 0);
}

/* Offset to struct sigcontext in ucontext, from <asm/ucontext.h>.  */
#define SH_LINUX_UCONTEXT_SIGCONTEXT_OFFSET 12


/* Assuming NEXT_FRAME is a frame following a GNU/Linux sigtramp
   routine, return the address of the associated sigcontext structure.  */

static CORE_ADDR
sh_linux_sigcontext_addr (struct frame_info *this_frame)
{
  CORE_ADDR pc;
  CORE_ADDR sp;

  sp = get_frame_register_unsigned (this_frame, SP_REGNUM);

  pc = sh_linux_sigtramp_start (this_frame);
  if (pc)
    {
      return sp;
    }

  pc = sh_linux_rt_sigtramp_start (this_frame);
  if (pc)
    {
      CORE_ADDR ucontext_addr;

      /* The sigcontext structure is part of the user context.  A
	 pointer to the user context is passed as the third argument
	 to the signal handler.  */
      ucontext_addr = get_frame_register_unsigned (this_frame, ARG0_REGNUM+2);
      return ucontext_addr + SH_LINUX_UCONTEXT_SIGCONTEXT_OFFSET;
    }

  error ("Couldn't recognize signal trampoline.");
  return 0;
}

/* Signal trampolines.  */
extern struct sh_frame_cache *sh_alloc_frame_cache (void);

static struct sh_frame_cache *
sh_linux_sigtramp_frame_cache (struct frame_info *this_frame, void **this_cache)
{
  struct sh_frame_cache *cache;
  struct gdbarch_tdep *tdep = gdbarch_tdep (get_current_arch ());
  CORE_ADDR sigcontext_addr;

  if (*this_cache)
    return *this_cache;

  cache = sh_alloc_frame_cache ();

  cache->base = get_frame_register_unsigned (this_frame, SP_REGNUM);
  sigcontext_addr = tdep->sigcontext_addr (this_frame);
  if (tdep->sc_reg_offset)
    {
      int i;

      gdb_assert (tdep->sc_num_regs <= SH_NUM_REGS);

      for (i = 0; i < tdep->sc_num_regs; i++)
	if (tdep->sc_reg_offset[i] != -1)
	  cache->saved_regs[i] = sigcontext_addr + tdep->sc_reg_offset[i];
    }

  *this_cache = cache;
  return cache;
}

static void
sh_linux_sigtramp_frame_this_id (struct frame_info *this_frame, void **this_cache,
			     struct frame_id *this_id)
{
  struct sh_frame_cache *cache =
    sh_linux_sigtramp_frame_cache (this_frame, this_cache);

  (*this_id) = frame_id_build (cache->base + 64, cache->pc);
}

extern struct value * sh_frame_prev_register ();
static struct value *
sh_linux_sigtramp_frame_prev_register (struct frame_info *this_frame,
                   void **this_cache, int regnum)
{
  sh_linux_sigtramp_frame_cache (this_frame, this_cache);

  return sh_frame_prev_register (this_frame, this_cache, regnum);
}

static int
sh_linux_sigtramp_frame_sniffer (const struct frame_unwind *self,
                 struct frame_info *this_frame,
                 void **this_prologue_cache)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (get_frame_arch (this_frame));

  /* We shouldn't even bother if we don't have a sigcontext_addr
     handler.  */
  if (tdep->sigcontext_addr == NULL)
    return 0;

  if (tdep->sigtramp_p != NULL)
    {
      if (tdep->sigtramp_p (this_frame))
    return 1;
    }

  return 0;
}

static const struct frame_unwind sh_linux_sigtramp_frame_unwind =
{
  SIGTRAMP_FRAME,
  sh_linux_sigtramp_frame_this_id,
  sh_linux_sigtramp_frame_prev_register,
  NULL,
  sh_linux_sigtramp_frame_sniffer
};

/* Supply register REGNUM from the buffer specified by GREGS and LEN
   in the general-purpose register set REGSET to register cache
   REGCACHE.  If REGNUM is -1, do this for all registers in REGSET.  */

void
sh_supply_gregset (const struct regset *regset, struct regcache *regcache,
             int regnum, const void *gregs, size_t len)
{
  const struct gdbarch_tdep *tdep = gdbarch_tdep (regset->arch);
  const char *regs = gregs;
  int i;

  gdb_assert (len == tdep->sizeof_gregset);

  for (i = 0; i < tdep->gregset_num_regs; i++)
    {
      if ((regnum == i || regnum == -1)
      && tdep->gregset_reg_offset[i] != -1)
    regcache_raw_supply (regcache, i, regs + tdep->gregset_reg_offset[i]);
    }
}

/* Collect register REGNUM from the register cache REGCACHE and store
   it in the buffer specified by GREGS and LEN as described by the
   general-purpose register set REGSET.  If REGNUM is -1, do this for
   all registers in REGSET.  */

void
sh_collect_gregset (const struct regset *regset,
              const struct regcache *regcache,
              int regnum, void *gregs, size_t len)
{
  const struct gdbarch_tdep *tdep = gdbarch_tdep (regset->arch);
  char *regs = gregs;
  int i;

  gdb_assert (len == tdep->sizeof_gregset);

  for (i = 0; i < tdep->gregset_num_regs; i++)
    {
      if ((regnum == i || regnum == -1)
      && tdep->gregset_reg_offset[i] != -1)
    regcache_raw_collect (regcache, i, regs + tdep->gregset_reg_offset[i]);
    }
}

/* Supply register REGNUM from the buffer specified by FPREGS and LEN
   in the floating-point register set REGSET to register cache
   REGCACHE.  If REGNUM is -1, do this for all registers in REGSET.  */

static void
sh_supply_fpregset (const struct regset *regset, struct regcache *regcache,
              int regnum, const void *fpregs, size_t len)
{
  const struct gdbarch_tdep *tdep = gdbarch_tdep (regset->arch);
  const char *regs = fpregs;
  int i;

  gdb_assert (len == tdep->sizeof_fpregset);
  for (i = 0; i < 16; i++)
    {
      if (regnum == i+25 || regnum == -1)
    regcache_raw_supply (regcache, i+25, regs + i*4);
    }
  if (regnum == FPSCR_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, FPSCR_REGNUM, regs + 32*4);
  if (regnum == FPUL_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, FPUL_REGNUM, regs + 33*4);
}

/* Collect register REGNUM from the register cache REGCACHE and store
   it in the buffer specified by FPREGS and LEN as described by the
   floating-point register set REGSET.  If REGNUM is -1, do this for
   all registers in REGSET.  */

static void
sh_collect_fpregset (const struct regset *regset,
               const struct regcache *regcache,
               int regnum, void *fpregs, size_t len)
{
  const struct gdbarch_tdep *tdep = gdbarch_tdep (regset->arch);
  char *regs = fpregs;
  int i;

  gdb_assert (len == tdep->sizeof_fpregset);
  for (i = 0; i < 16; i++)
    {
      if (regnum == i+25 || regnum == -1)
    regcache_raw_collect (regcache, i+25, regs + i*4);
    }
  if (regnum == FPSCR_REGNUM || regnum == -1)
    regcache_raw_collect (regcache, FPSCR_REGNUM, regs + 32*4);
  if (regnum == FPUL_REGNUM || regnum == -1)
    regcache_raw_collect (regcache, FPUL_REGNUM, regs + 33*4);
}

/* Return the appropriate register set for the core section identified
   by SECT_NAME and SECT_SIZE.  */

const struct regset *
sh_linux_regset_from_core_section (struct gdbarch *gdbarch,
                   const char *sect_name, size_t sect_size)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  if (strcmp (sect_name, ".reg") == 0 && sect_size == tdep->sizeof_gregset)
    {
      if (tdep->gregset == NULL)
    tdep->gregset = regset_alloc (gdbarch, sh_supply_gregset,
                      sh_collect_gregset);
      return tdep->gregset;
    }

  if ((strcmp (sect_name, ".reg2") == 0 && sect_size == tdep->sizeof_fpregset))
    {
      if (tdep->fpregset == NULL)
    tdep->fpregset = regset_alloc (gdbarch, sh_supply_fpregset,
                       sh_collect_fpregset);
      return tdep->fpregset;
    }

  return NULL;
}

/* The register sets used in GNU/Linux ELF core-dumps are identical to
   the register sets in `struct user' that are used for a.out
   core-dumps.  These are also used by ptrace(2).  The corresponding
   types are `elf_gregset_t' for the general-purpose registers (with
   `elf_greg_t' the type of a single GP register) and `elf_fpregset_t'
   for the floating-point registers.

   Those types used to be available under the names `gregset_t' and
   `fpregset_t' too, and GDB used those names in the past.  But those
   names are now used for the register sets used in the `mcontext_t'
   type, which have a different size and layout.  */

/* Mapping between the general-purpose registers in `struct user'
   format and GDB's register cache layout.  */

/* From <sys/reg.h>.  */
static int sh_linux_gregset_reg_offset[] =
{
 0,	4,	8,	12,	16,	20,	24,	28,
 32,	36,	40,	44,	48,	52,	56,	60,

 REG_PC*4,   REG_PR*4,   REG_GBR*4,  -1,
 REG_MACH*4, REG_MACL*4, REG_SR*4,
};

/* Mapping between the general-purpose registers in `struct
   sigcontext' format and GDB's register cache layout.  */

/* From <asm/sigcontext.h>.  */
static int sh_linux_sc_reg_offset[] =
{
 4,	8,	12,	16,	20,	24,	28,	32,
 36,	40,	44,	48,	52,	56,	60,	64,
 68,	72,	80,	-1,
 84,	88,	76
};

static void
sh_linux_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  bfd abfd;

  tdep->gregset_reg_offset = sh_linux_gregset_reg_offset;
  tdep->gregset_num_regs = ARRAY_SIZE (sh_linux_gregset_reg_offset);
  tdep->sizeof_gregset = 23 * 4;

  tdep->jb_pc_offset = 32;     /* From <bits/setjmp.h>.  */

  tdep->sigtramp_p = sh_linux_sigtramp_p;
  tdep->sigcontext_addr = sh_linux_sigcontext_addr;
  tdep->sc_reg_offset = sh_linux_sc_reg_offset;
  tdep->sc_num_regs = ARRAY_SIZE (sh_linux_sc_reg_offset);

  frame_unwind_append_unwinder(gdbarch, &sh_linux_sigtramp_frame_unwind);

  /* If we have a register mapping, enable the generic core file
     support, unless it has already been enabled.  */
  if (tdep->gregset_reg_offset
      && !gdbarch_regset_from_core_section_p (gdbarch))
    set_gdbarch_regset_from_core_section (gdbarch,
                                         sh_linux_regset_from_core_section);

  linux_init_abi (info, gdbarch);

  /* GNU/Linux uses SVR4-style shared libraries.  */
  set_gdbarch_skip_trampoline_code (gdbarch, find_solib_trampoline_target);
  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, svr4_ilp32_fetch_link_map_offsets);
  set_gdbarch_skip_solib_resolver (gdbarch, glibc_skip_solib_resolver);

  set_gdbarch_fetch_tls_load_module_address (gdbarch,
                                             svr4_fetch_objfile_link_map);

  /* Core files and signal handler frame unwinding are supported for
     32-bit SH only, at present.  */
  if (info.bfd_arch_info->mach != bfd_mach_sh5)
    {
      struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

      /* Remember regset characteristics.  The sizes should match
	 elf_gregset_t and elf_fpregset_t from Linux.  */
      tdep->core_gregmap = (struct sh_corefile_regmap *)gregs_table;
      tdep->sizeof_gregset = 92;
      tdep->core_fpregmap = (struct sh_corefile_regmap *)fpregs_table;
      tdep->sizeof_fpregset = 136;

      tramp_frame_prepend_unwinder (gdbarch, &sh_linux_sigreturn_tramp_frame);
      tramp_frame_prepend_unwinder (gdbarch, &sh_linux_rt_sigreturn_tramp_frame);
    }
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
extern void _initialize_sh_linux_tdep (void);

void
_initialize_sh_linux_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_sh, 0, GDB_OSABI_LINUX, sh_linux_init_abi);
}
