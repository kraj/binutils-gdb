/* Native-dependent code for GNU/Linux x86 (i386 and x86-64).

   Copyright (C) 1999-2025 Free Software Foundation, Inc.

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

#include "inferior.h"
#include "elf/common.h"
#include "gdb_proc_service.h"
#include "nat/gdb_ptrace.h"
#include <sys/user.h>
#include <sys/procfs.h>
#include <sys/uio.h>

#include "x86-nat.h"
#ifndef __x86_64__
#include "nat/i386-linux.h"
#endif
#include "x86-linux-nat.h"
#include "i386-linux-tdep.h"
#ifdef __x86_64__
#include "amd64-linux-tdep.h"
#endif
#include "gdbsupport/x86-xstate.h"
#include "nat/x86-xstate.h"
#include "nat/linux-btrace.h"
#include "nat/linux-nat.h"
#include "nat/x86-linux.h"
#include "nat/x86-linux-dregs.h"
#include "nat/linux-ptrace.h"
#include "x86-tdep.h"
#include "nat/x86-linux-tdesc.h"

/* linux_nat_target::low_new_fork implementation.  */

void
x86_linux_nat_target::low_new_fork (struct lwp_info *parent, pid_t child_pid)
{
  pid_t parent_pid;
  struct x86_debug_reg_state *parent_state;
  struct x86_debug_reg_state *child_state;

  /* NULL means no watchpoint has ever been set in the parent.  In
     that case, there's nothing to do.  */
  if (parent->arch_private == NULL)
    return;

  /* Linux kernel before 2.6.33 commit
     72f674d203cd230426437cdcf7dd6f681dad8b0d
     will inherit hardware debug registers from parent
     on fork/vfork/clone.  Newer Linux kernels create such tasks with
     zeroed debug registers.

     GDB core assumes the child inherits the watchpoints/hw
     breakpoints of the parent, and will remove them all from the
     forked off process.  Copy the debug registers mirrors into the
     new process so that all breakpoints and watchpoints can be
     removed together.  The debug registers mirror will become zeroed
     in the end before detaching the forked off process, thus making
     this compatible with older Linux kernels too.  */

  parent_pid = parent->ptid.pid ();
  parent_state = x86_debug_reg_state (parent_pid);
  child_state = x86_debug_reg_state (child_pid);
  *child_state = *parent_state;
}


x86_linux_nat_target::~x86_linux_nat_target ()
{
}

/* Implement the virtual inf_ptrace_target::post_startup_inferior method.  */

void
x86_linux_nat_target::post_startup_inferior (ptid_t ptid)
{
  x86_cleanup_dregs ();
  linux_nat_target::post_startup_inferior (ptid);
}

/* Get Linux/x86 target description from running target.  */

const struct target_desc *
x86_linux_nat_target::read_description ()
{
  /* The x86_linux_tdesc_for_tid call only reads xcr0 the first time it is
     called.  Also it checks the enablement state of features which are
     not configured in xcr0, such as CET shadow stack.  Once the supported
     features are identified, the XSTATE_BV_STORAGE value is configured
     accordingly and preserved for subsequent calls of this function.  */
  static uint64_t xstate_bv_storage;

  if (inferior_ptid == null_ptid)
    return this->beneath ()->read_description ();

  int tid = inferior_ptid.pid ();

  return x86_linux_tdesc_for_tid (tid, &xstate_bv_storage,
				  &this->m_xsave_layout);
}


/* Enable branch tracing.  */

struct btrace_target_info *
x86_linux_nat_target::enable_btrace (thread_info *tp,
				     const struct btrace_config *conf)
{
  struct btrace_target_info *tinfo = nullptr;
  ptid_t ptid = tp->ptid;
  try
    {
      tinfo = linux_enable_btrace (ptid, conf);
    }
  catch (const gdb_exception_error &exception)
    {
      error (_("Could not enable branch tracing for %s: %s"),
	     target_pid_to_str (ptid).c_str (), exception.what ());
    }

  return tinfo;
}

/* Disable branch tracing.  */

void
x86_linux_nat_target::disable_btrace (struct btrace_target_info *tinfo)
{
  enum btrace_error errcode = linux_disable_btrace (tinfo);

  if (errcode != BTRACE_ERR_NONE)
    error (_("Could not disable branch tracing."));
}

/* Teardown branch tracing.  */

void
x86_linux_nat_target::teardown_btrace (struct btrace_target_info *tinfo)
{
  /* Ignore errors.  */
  linux_disable_btrace (tinfo);
}

enum btrace_error
x86_linux_nat_target::read_btrace (struct btrace_data *data,
				   struct btrace_target_info *btinfo,
				   enum btrace_read_type type)
{
  return linux_read_btrace (data, btinfo, type);
}

/* See to_btrace_conf in target.h.  */

const struct btrace_config *
x86_linux_nat_target::btrace_conf (const struct btrace_target_info *btinfo)
{
  return linux_btrace_conf (btinfo);
}



/* Helper for ps_get_thread_area.  Sets BASE_ADDR to a pointer to
   the thread local storage (or its descriptor) and returns PS_OK
   on success.  Returns PS_ERR on failure.  */

ps_err_e
x86_linux_get_thread_area (pid_t pid, void *addr, unsigned int *base_addr)
{
  /* NOTE: cagney/2003-08-26: The definition of this buffer is found
     in the kernel header <asm-i386/ldt.h>.  It, after padding, is 4 x
     4 byte integers in size: `entry_number', `base_addr', `limit',
     and a bunch of status bits.

     The values returned by this ptrace call should be part of the
     regcache buffer, and ps_get_thread_area should channel its
     request through the regcache.  That way remote targets could
     provide the value using the remote protocol and not this direct
     call.

     Is this function needed?  I'm guessing that the `base' is the
     address of a descriptor that libthread_db uses to find the
     thread local address base that GDB needs.  Perhaps that
     descriptor is defined by the ABI.  Anyway, given that
     libthread_db calls this function without prompting (gdb
     requesting tls base) I guess it needs info in there anyway.  */
  unsigned int desc[4];

  /* This code assumes that "int" is 32 bits and that
     GET_THREAD_AREA returns no more than 4 int values.  */
  gdb_assert (sizeof (int) == 4);

#ifndef PTRACE_GET_THREAD_AREA
#define PTRACE_GET_THREAD_AREA 25
#endif

  if (ptrace (PTRACE_GET_THREAD_AREA, pid, addr, &desc) < 0)
    return PS_ERR;

  *base_addr = desc[1];
  return PS_OK;
}


/* See x86-linux-nat.h.  */

void
x86_linux_fetch_ssp (regcache *regcache, const int tid)
{
  uint64_t ssp = 0x0;
  iovec iov {&ssp, sizeof (ssp)};

  /* The shadow stack may be enabled and disabled at runtime.  Reading the
     ssp might fail as shadow stack was not activated for the current
     thread.  We don't want to show a warning but silently return.  The
     register will be shown as unavailable for the user.  */
  if (ptrace (PTRACE_GETREGSET, tid, NT_X86_SHSTK, &iov) != 0)
    return;

  x86_supply_ssp (regcache, ssp);
}

/* See x86-linux-nat.h.  */

void
x86_linux_store_ssp (const regcache *regcache, const int tid)
{
  uint64_t ssp = 0x0;
  iovec iov {&ssp, sizeof (ssp)};
  x86_collect_ssp (regcache, ssp);

  /* Starting with v6.6., the Linux kernel supports CET shadow stack.
     Dependent on the target the ssp register can be unavailable or
     nullptr when shadow stack is supported by HW and the Linux kernel but
     not enabled for the current thread.  In case of nullptr, GDB tries to
     restore the shadow stack pointer after an inferior call.  The ptrace
     call with PTRACE_SETREGSET will fail here with errno ENODEV.  We
     don't want to throw an error in this case but silently continue.  */
  errno = 0;
  if ((ptrace (PTRACE_SETREGSET, tid, NT_X86_SHSTK, &iov) != 0)
      && (errno != ENODEV))
    perror_with_name (_("Failed to write pl3_ssp register"));
}

void _initialize_x86_linux_nat ();
void
_initialize_x86_linux_nat ()
{
  /* Initialize the debug register function vectors.  */
  x86_dr_low.set_control = x86_linux_dr_set_control;
  x86_dr_low.set_addr = x86_linux_dr_set_addr;
  x86_dr_low.get_addr = x86_linux_dr_get_addr;
  x86_dr_low.get_status = x86_linux_dr_get_status;
  x86_dr_low.get_control = x86_linux_dr_get_control;
  x86_set_debug_register_length (sizeof (void *));
}
