/* Low level child interface to ptrace.

   Copyright (C) 2004-2016 Free Software Foundation, Inc.

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

#ifndef INF_PTRACE_H
#define INF_PTRACE_H

#include "inf-child.h"

/* An abstract prototype ptrace target.  The client can override it
   with local methods.  */

struct inf_ptrace_target : public inf_child_target
{
  ~inf_ptrace_target () OVERRIDE = 0;

  void attach (const char *, int) OVERRIDE;

  void detach (const char *, int) OVERRIDE;

  void resume (ptid_t, int, enum gdb_signal) OVERRIDE;

  ptid_t wait (ptid_t, struct target_waitstatus *, int) OVERRIDE;

  void files_info () OVERRIDE;

  void kill () OVERRIDE;

  void create_inferior (char *, char *, char **, int) OVERRIDE;
#ifdef PT_GET_PROCESS_STATE
  int follow_fork (int, int) OVERRIDE;

  int insert_fork_catchpoint (int) OVERRIDE;

  int remove_fork_catchpoint (int) OVERRIDE;

  void post_startup_inferior (ptid_t) OVERRIDE;

  void post_attach (int) OVERRIDE;
#endif

  void mourn_inferior () OVERRIDE;

  int thread_alive (ptid_t ptid) OVERRIDE;

  char *pid_to_str (ptid_t) OVERRIDE;

  void interrupt (ptid_t) OVERRIDE;

  enum target_xfer_status xfer_partial (enum target_object object,
					const char *annex,
					gdb_byte *readbuf,
					const gdb_byte *writebuf,
					ULONGEST offset, ULONGEST len,
					ULONGEST *xfered_len) OVERRIDE;

#if defined (PT_IO) && defined (PIOD_READ_AUXV)
  int auxv_parse (gdb_byte **readptr,
		  gdb_byte *endptr, CORE_ADDR *typep, CORE_ADDR *valp) OVERRIDE;
#endif

 protected:
  /* Cleanup the inferior after a successful ptrace detach.  */
  void detach_success ();
};

/* Return which PID to pass to ptrace in order to observe/control the
   tracee identified by PTID.  */

extern pid_t get_ptrace_pid (ptid_t);

#endif
