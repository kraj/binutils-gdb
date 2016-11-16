/* User/system CPU time clocks that follow the std::chrono interface.
   Copyright (C) 2016 Free Software Foundation, Inc.

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

#ifndef CPU_TIME_CLOCK_H
#define CPU_TIME_CLOCK_H

#include <chrono>
#include <sys/time.h>
#if defined HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

/* Count the total amount of time spent executing in user mode.  */

struct user_cpu_time_clock
{
  using duration = std::chrono::microseconds;
  using rep = duration::rep;
  using period = duration::period;
  using time_point = std::chrono::time_point<user_cpu_time_clock>;

  static const bool is_steady = true;

  static time_point now () noexcept
  {
    using namespace std::chrono;
    return time_point (microseconds (get_run_time ()));
  }
};

/* Count the total amount of time spent executing in kernel mode.  */

struct system_cpu_time_clock
{
  using duration = std::chrono::microseconds;
  using rep = duration::rep;
  using period = duration::period;
  using time_point = std::chrono::time_point<system_cpu_time_clock>;

  static const bool is_steady = true;

  static time_point now () noexcept
  {
    using namespace std::chrono;
#ifdef HAVE_GETRUSAGE
    struct rusage rusage;
    getrusage (RUSAGE_SELF, &rusage);
    return time_point (seconds (rusage.ru_stime.tv_sec)
		       + microseconds (rusage.ru_stime.tv_usec));
#else
    return microseconds::zero ();
#endif
  }
};

#endif
