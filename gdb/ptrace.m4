dnl Copyright (C) 2012-2016 Free Software Foundation, Inc.
dnl
dnl This file is part of GDB.
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.

dnl Check the return and argument types of ptrace.

AC_DEFUN([GDB_AC_PTRACE],
[

AC_CHECK_HEADERS([sys/ptrace.h ptrace.h])

# Needs to be tested in C++ mode, to detect whether we need to cast
# the first argument to enum __ptrace_request.
if test "$enable_build_with_cxx" = "yes"; then
    AC_LANG_PUSH([C++])
fi

gdb_ptrace_headers='
#include <sys/types.h>
#if HAVE_SYS_PTRACE_H
# include <sys/ptrace.h>
#endif
#if HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef __cplusplus
#  define EXTERN_C extern "C"
#else
#  define EXTERN_C extern
#endif
'
# There is no point in checking if we don't have a prototype.
AC_CHECK_DECLS(ptrace, [], [
  : ${gdb_cv_func_ptrace_proto='int,int,int,long,long'}
], $gdb_ptrace_headers)

# GNU/Linux uses a varargs prototype, so check for that explicitly.
AC_CACHE_CHECK([return type of ptrace], gdb_cv_func_ptrace_proto, [
  AC_TRY_COMPILE($gdb_ptrace_headers [
EXTERN_C long ptrace (enum __ptrace_request, ...);
      ],,
    [gdb_cv_func_ptrace_proto='long,enum __ptrace_request,int,long,long'])
])

# Test all possible return and argument types combinations.
AC_CACHE_CHECK([types of arguments for ptrace], gdb_cv_func_ptrace_proto, [

# Provide a safe default value.
gdb_cv_func_ptrace_proto='int,int,int,long,long'

for gdb_ret in 'int' 'long'; do
 for gdb_arg1 in 'int' 'long'; do
  for gdb_arg2 in 'pid_t' 'int' 'long'; do
   for gdb_arg3 in 'int *' 'caddr_t' 'int' 'long' 'void *'; do
    for gdb_arg4 in 'int' 'long' 'void *'; do
     AC_TRY_COMPILE($gdb_ptrace_headers [
EXTERN_C $gdb_ret
  ptrace ($gdb_arg1, $gdb_arg2, $gdb_arg3, $gdb_arg4);
], [],
      [gdb_cv_func_ptrace_proto="$gdb_ret,$gdb_arg1,$gdb_arg2,$gdb_arg3,$gdb_arg4";
       break 5;])
     for gdb_arg5 in 'int *' 'int' 'long'; do
      AC_TRY_COMPILE($gdb_ptrace_headers [
EXTERN_C $gdb_ret
  ptrace ($gdb_arg1, $gdb_arg2, $gdb_arg3, $gdb_arg4, $gdb_arg5);
],,
       [gdb_cv_func_ptrace_proto="$gdb_ret,$gdb_arg1,$gdb_arg2,$gdb_arg3,$gdb_arg4,$gdb_arg5";
        break 6;])
     done
    done
   done
  done
 done
done

])

ac_save_IFS=$IFS; IFS=','
set dummy `echo "$gdb_cv_func_ptrace_proto" | sed 's/\*/\*/g'`
IFS=$ac_save_IFS
shift
AC_DEFINE_UNQUOTED(PTRACE_TYPE_RET, $[1],
  [Define as the return type of ptrace.])
AC_DEFINE_UNQUOTED(PTRACE_TYPE_ARG1, $[2],
  [Define to the type of arg 1 for ptrace.])
AC_DEFINE_UNQUOTED(PTRACE_TYPE_ARG3, $[4],
  [Define to the type of arg 3 for ptrace.])
AC_DEFINE_UNQUOTED(PTRACE_TYPE_ARG4, $[5],
  [Define to the type of arg 4 for ptrace.])
if test -n "$[6]"; then
  AC_DEFINE_UNQUOTED(PTRACE_TYPE_ARG5, $[6],
    [Define to the type of arg 5 for ptrace.])
fi

if test "$enable_build_with_cxx" = "yes"; then
    AC_LANG_POP([C++])
fi
])
