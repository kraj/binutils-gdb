/* Exception (throw catch) mechanism, for GDB, the GNU debugger.

   Copyright (C) 1986-2016 Free Software Foundation, Inc.

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
#include "common-exceptions.h"

const struct gdb_exception exception_none;

/* Possible catcher states.  */
enum catcher_state {
  /* Initial state, a new catcher has just been created.  */
  CATCHER_CREATED,
  /* The catch code is running.  */
  CATCHER_RUNNING,
  CATCHER_RUNNING_1,
  /* The catch code threw an exception.  */
  CATCHER_ABORTING
};

/* Possible catcher actions.  */
enum catcher_action {
  CATCH_ITER,
  CATCH_ITER_1,
  CATCH_THROWING
};

struct catcher
{
  enum catcher_state state;
  /* Jump buffer pointing back at the exception handler.  */
  jmp_buf buf;
  /* Status buffer belonging to the exception handler.  */
  struct gdb_exception exception;
  struct cleanup *saved_cleanup_chain;
  /* Back link.  */
  struct catcher *prev;
};

/* Where to go for throw_exception().  */
static struct catcher *current_catcher;

jmp_buf *
exceptions_state_mc_init (void)
{
  struct catcher *new_catcher = XCNEW (struct catcher);

  /* Start with no exception.  */
  new_catcher->exception = exception_none;

  /* Prevent error/quit during FUNC from calling cleanups established
     prior to here.  */
  new_catcher->saved_cleanup_chain = save_cleanups ();

  /* Push this new catcher on the top.  */
  new_catcher->prev = current_catcher;
  current_catcher = new_catcher;
  new_catcher->state = CATCHER_CREATED;

  return &new_catcher->buf;
}

static void
catcher_pop (void)
{
  struct catcher *old_catcher = current_catcher;

  current_catcher = old_catcher->prev;

  /* Restore the cleanup chain, the error/quit messages, and the uiout
     builder, to their original states.  */

  restore_cleanups (old_catcher->saved_cleanup_chain);

  xfree (old_catcher);
}

/* Catcher state machine.  Returns non-zero if the m/c should be run
   again, zero if it should abort.  */

static int
exceptions_state_mc (enum catcher_action action)
{
  switch (current_catcher->state)
    {
    case CATCHER_CREATED:
      switch (action)
	{
	case CATCH_ITER:
	  /* Allow the code to run the catcher.  */
	  current_catcher->state = CATCHER_RUNNING;
	  return 1;
	default:
	  internal_error (__FILE__, __LINE__, _("bad state"));
	}
    case CATCHER_RUNNING:
      switch (action)
	{
	case CATCH_ITER:
	  /* No error/quit has occured.  */
	  return 0;
	case CATCH_ITER_1:
	  current_catcher->state = CATCHER_RUNNING_1;
	  return 1;
	case CATCH_THROWING:
	  current_catcher->state = CATCHER_ABORTING;
	  /* See also throw_exception.  */
	  return 1;
	default:
	  internal_error (__FILE__, __LINE__, _("bad switch"));
	}
    case CATCHER_RUNNING_1:
      switch (action)
	{
	case CATCH_ITER:
	  /* The did a "break" from the inner while loop.  */
	  return 0;
	case CATCH_ITER_1:
	  current_catcher->state = CATCHER_RUNNING;
	  return 0;
	case CATCH_THROWING:
	  current_catcher->state = CATCHER_ABORTING;
	  /* See also throw_exception.  */
	  return 1;
	default:
	  internal_error (__FILE__, __LINE__, _("bad switch"));
	}
    case CATCHER_ABORTING:
      switch (action)
	{
	case CATCH_ITER:
	  {
	    /* Exit normally if this catcher can handle this
	       exception.  The caller analyses the func return
	       values.  */
	    return 0;
	  }
	default:
	  internal_error (__FILE__, __LINE__, _("bad state"));
	}
    default:
      internal_error (__FILE__, __LINE__, _("bad switch"));
    }
}

struct gdb_exception
exceptions_state_mc_catch ()
{
  struct gdb_exception res = gdb::move (current_catcher->exception);

  catcher_pop ();
  return res;
}

int
exceptions_state_mc_action_iter (void)
{
  return exceptions_state_mc (CATCH_ITER);
}

int
exceptions_state_mc_action_iter_1 (void)
{
  return exceptions_state_mc (CATCH_ITER_1);
}

/* How many nested TRY blocks we have.  See exception_messages and
   throw_it.  */

static int try_scope_depth;

/* Called on entry to a TRY scope.  */

void *
exception_try_scope_entry (void)
{
  ++try_scope_depth;
  return (void *) save_cleanups ();
}

/* Called on exit of a TRY scope, either normal exit or exception
   exit.  */

void
exception_try_scope_exit (void *saved_state)
{
  restore_cleanups ((struct cleanup *) saved_state);
  --try_scope_depth;
}

/* Called by the default catch block.  IOW, we'll get here before
   jumping out to the next outermost scope an exception if a GDB
   exception is not caught.  */

void
exception_rethrow (void)
{
  /* Run this scope's cleanups before re-throwing to the next
     outermost scope.  */
  do_cleanups (all_cleanups ());
  throw;
}

/* Return EXCEPTION to the nearest containing catch_errors().  */

void
throw_exception_sjlj (gdb_exception_rval_ref exception)
{
  do_cleanups (all_cleanups ());

  /* Jump to the containing catch_errors() call, communicating REASON
     to that call via setjmp's return value.  Note that REASON can't
     be zero, by definition in defs.h.  */
  exceptions_state_mc (CATCH_THROWING);
  current_catcher->exception = gdb::move (exception);
  longjmp (current_catcher->buf, exception.reason);
}

static void ATTRIBUTE_NORETURN
throw_exception (enum return_reason reason,
		 enum errors error,
		 const char *message)
{
  /* Throw the exception.  */
  do_cleanups (all_cleanups ());

  if (reason == RETURN_QUIT)
    throw gdb_quit (message);
  else if (reason == RETURN_ERROR)
    throw gdb_error (error, message);
  else
    gdb_assert_not_reached ("invalid return reason");
}

static void ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (3, 0)
throw_it (enum return_reason reason, enum errors error, const char *fmt,
	  va_list ap)
{
  const char *message = xstrvprintf (fmt, ap);

  throw_exception (reason, error, message);
}

void
throw_exception (const gdb_exception &exception)
{
  const char *message = (exception.message != NULL
			 ? xstrdup (exception.message)
			 : NULL);

  throw_exception (exception.reason, exception.error, message);
}

void
throw_exception (gdb_exception_rval_ref exception)
{
  const char *message = exception.message;

  exception.message = NULL;
  throw_exception (exception.reason, exception.error, message);
}

void
throw_verror (enum errors error, const char *fmt, va_list ap)
{
  throw_it (RETURN_ERROR, error, fmt, ap);
}

void
throw_vquit (const char *fmt, va_list ap)
{
  throw_it (RETURN_QUIT, GDB_NO_ERROR, fmt, ap);
}

void
throw_error (enum errors error, const char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);
  throw_verror (error, fmt, args);
  va_end (args);
}

void
throw_quit (const char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);
  throw_vquit (fmt, args);
  va_end (args);
}
