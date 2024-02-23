/* Common definitions.

   Copyright (C) 1986-2024 Free Software Foundation, Inc.

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

#ifndef COMMON_COMMON_DEFS_H
#define COMMON_COMMON_DEFS_H

#include <stdarg.h>
#include <stdio.h>

/* Include both cstdlib and stdlib.h to ensure we have standard functions
   defined both in the std:: namespace and in the global namespace.  */
#include <cstdlib>
#include <stdlib.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#include <errno.h>
#if HAVE_ALLOCA_H
#include <alloca.h>
#endif


#define ATTRIBUTE_UNUSED_RESULT __attribute__ ((__warn_unused_result__))
#define ATTRIBUTE_USED __attribute__ ((__used__))

#include "libiberty.h"
#include "pathmax.h"
#include "gdb/signals.h"
#include "gdb_locale.h"
#include "ptid.h"
#include "common-types.h"
#include "common-utils.h"
#include "gdb_assert.h"
#include "errors.h"
#include "print-utils.h"
#include "common-debug.h"
#include "cleanups.h"
#include "common-exceptions.h"

/* Pull in gdb::unique_xmalloc_ptr.  */
#include "gdbsupport/gdb_unique_ptr.h"

#endif /* COMMON_COMMON_DEFS_H */
