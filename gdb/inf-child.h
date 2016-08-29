/* Base/prototype target for default child (native) targets.

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

#ifndef INF_CHILD_H
#define INF_CHILD_H

/* A prototype child target.  The client can override it with local
   methods.  */

struct inf_child_target
  : public memory_breakpoint_target<target_ops>
{
  inf_child_target ();
  ~inf_child_target () OVERRIDE = 0;

  const char *shortname () OVERRIDE
  { return "native"; }

  const char *longname () OVERRIDE
  { return _("Native process"); }

  const char *doc () OVERRIDE
  { return _("Native process (started by the \"run\" command)."); }

  void open (const char *arg, int from_tty) OVERRIDE;
  void close () OVERRIDE;

  void disconnect (const char *, int) OVERRIDE;

  void fetch_registers (struct regcache *, int) OVERRIDE = 0;
  void store_registers (struct regcache *, int) OVERRIDE = 0;

  void prepare_to_store (struct regcache *) OVERRIDE;

  bool supports_terminal_ours () OVERRIDE;
  void terminal_init () OVERRIDE;
  void terminal_inferior () OVERRIDE;
  void terminal_ours_for_output () OVERRIDE;
  void terminal_ours () OVERRIDE;
  void terminal_info (const char *, int) OVERRIDE;

  void post_startup_inferior (ptid_t) OVERRIDE;

  void mourn_inferior () OVERRIDE;

  bool can_run () OVERRIDE;

  bool can_create_inferior () OVERRIDE;
  void create_inferior (char *, char *, char **, int) OVERRIDE = 0;

  bool can_attach () OVERRIDE;
  void attach (const char *, int) OVERRIDE = 0;

  void post_attach (int);

  /* We must default these because they must be implemented by any
     target that can run.  */
  bool can_async_p ()  OVERRIDE { return false; }
  bool supports_non_stop ()  OVERRIDE { return false; }

  char *pid_to_exec_file (int pid) OVERRIDE;

  bool has_all_memory () OVERRIDE;
  bool has_memory () OVERRIDE;
  bool has_stack () OVERRIDE;
  bool has_registers () OVERRIDE;
  bool has_execution (ptid_t) OVERRIDE;

  int fileio_open (struct inferior *inf, const char *filename,
		   int flags, int mode, int warn_if_slow,
		   int *target_errno) OVERRIDE;
  int fileio_pwrite (int fd, const gdb_byte *write_buf, int len,
		     ULONGEST offset, int *target_errno) OVERRIDE;
  int fileio_pread (int fd, gdb_byte *read_buf, int len,
		    ULONGEST offset, int *target_errno) OVERRIDE;
  int fileio_fstat (int fd, struct stat *sb, int *target_errno) OVERRIDE;
  int fileio_close (int fd, int *target_errno) OVERRIDE;
  int fileio_unlink (struct inferior *inf,
		     const char *filename,
		     int *target_errno) OVERRIDE;
  char *fileio_readlink (struct inferior *inf,
			 const char *filename,
			 int *target_errno) OVERRIDE;
  bool use_agent (int use) OVERRIDE;

  bool can_use_agent () OVERRIDE;

 protected:
  /* Unpush the target if it wasn't explicitly open with "target native"
     and there are no live inferiors left.  Note: if calling this as a
     result of a mourn or detach, the current inferior shall already
     have its PID cleared, so it isn't counted as live.  That's usually
     done by calling either generic_mourn_inferior or
     detach_inferior.  */
  void maybe_unpush_target ();
};

/* Functions for helping to write a native target.  */

/* This is for native targets which use a unix/POSIX-style waitstatus.  */
extern void store_waitstatus (struct target_waitstatus *, int);

#endif
