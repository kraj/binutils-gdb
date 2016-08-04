/* Copyright (C) 2016 Free Software Foundation, Inc.

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

#include "common-defs.h"
#include "signal-dispositions-save-restore.h"

#include <signal.h>

/* The original signal handlers.  */

#ifdef HAVE_SIGACTION
static sighandler_t original_signal_handlers[NSIG];
#endif

/* See signal-dispositions-save-restore.h.   */

void
save_original_signal_dispositions (void)
{
#ifdef HAVE_SIGACTION
  int i;

  for (i = 1; i < NSIG; i++)
    {
      struct sigaction oldact;

      sigaction (i, NULL, &oldact);

      original_signal_handlers[i] = oldact.sa_handler;

      /* If we find a signal handler already installed, then this
	 function was called too late.  */
      if (oldact.sa_handler != SIG_DFL
	  && oldact.sa_handler != SIG_IGN)
	internal_error (__FILE__, __LINE__, _("unexpected signal handler"));
    }
#endif
}

/* See signal-dispositions-save-restore.h.   */

void
restore_original_signal_dispositions (void)
{
#ifdef HAVE_SIGACTION
  int i;

  for (i = 1; i < NSIG; i++)
    signal (i, original_signal_handlers[i]);
#endif
}
