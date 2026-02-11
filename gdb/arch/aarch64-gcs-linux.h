/* Common Linux target-dependent definitions for AArch64 GCS

   Copyright (C) 2025 Free Software Foundation, Inc.

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

#ifndef GDB_ARCH_AARCH64_GCS_LINUX_H
#define GDB_ARCH_AARCH64_GCS_LINUX_H

#include <stdint.h>

/* Feature check for Guarded Control Stack.  */
#ifndef HWCAP_GCS
#define HWCAP_GCS (1ULL << 32)
#endif

#ifndef HAVE_STRUCT_USER_GCS

/* GCS state (NT_ARM_GCS).  */

struct user_gcs
{
  uint64_t features_enabled;
  uint64_t features_locked;
  uint64_t gcspr_el0;
};

#endif /* HAVE_STRUCT_USER_GCS */

/* The GCS regset consists of 3 64-bit registers.  */
#define AARCH64_LINUX_SIZEOF_GCS_REGSET (3 * 8)

#endif /* GDB_ARCH_AARCH64_GCS_LINUX_H */
