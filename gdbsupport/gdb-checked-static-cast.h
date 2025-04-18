/* Copyright (C) 2022-2025 Free Software Foundation, Inc.

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

#ifndef GDBSUPPORT_GDB_CHECKED_STATIC_CAST_H
#define GDBSUPPORT_GDB_CHECKED_STATIC_CAST_H

#include "gdbsupport/traits.h"

namespace gdb
{

/* This function can be used in place of static_cast when casting between
   pointers of polymorphic types.  The benefit of using this call is that,
   when compiling in developer mode, dynamic_cast will be used to validate
   the cast.  This use of dynamic_cast is why this function will only
   work for polymorphic types.

   In non-developer (i.e. production) builds, the dynamic_cast is replaced
   with a static_cast which is usually significantly faster.  */

template<typename T, typename V>
T
checked_static_cast (V *v)
{
  /* We only support casting to pointer types.  */
  static_assert (std::is_pointer<T>::value, "target must be a pointer type");

  /* Check for polymorphic types explicitly in case we're in release mode.  */
  static_assert (std::is_polymorphic<V>::value, "types must be polymorphic");

  /* Figure out the type that T points to.  */
  using T_no_P = typename std::remove_pointer<T>::type;

  /* In developer mode this cast uses dynamic_cast to confirm at run-time
     that the cast from V* to T is valid.  However, we can catch some
     mistakes at compile time, this assert prevents anything other than
     downcasts, or casts to same type.  */
  static_assert (std::is_base_of<V, T_no_P>::value
		 || std::is_base_of<T_no_P, V>::value,
		 "types must be related");

#ifdef DEVELOPMENT
  gdb_assert (v == nullptr || dynamic_cast<T> (v) != nullptr);
#endif

  /* If a base class of V is virtual then the dynamic_cast above will
     succeed, but this static_cast will fail.  */
  return static_cast<T> (v);
}

/* Same as the above, but to cast from a reference type to another.  */

template<typename T, typename V, typename = gdb::Requires<std::is_reference<T>>>
T
checked_static_cast (V &v)
{
  static_assert (std::is_reference<T>::value, "target must be a reference type");

  using T_no_R = typename std::remove_reference<T>::type;
  using T_P = typename std::add_pointer<T_no_R>::type;

  using V_no_R = typename std::remove_reference<V>::type;

  return *checked_static_cast<T_P, V_no_R> (&v);
}

}

#endif /* GDBSUPPORT_GDB_CHECKED_STATIC_CAST_H */
