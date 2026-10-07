/* Copyright 2026 Free Software Foundation, Inc.

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

/* Minimal HIP program to reproduce duplicate MI notification bug.

   The bug: When a regular breakpoint is hit in MI mode with HIP runtime
   initialized, the entire notification sequence appears TWICE:
   - =breakpoint-modified
   - Console output (~"...")
   - *stopped

   This test is a stripped-down version of solib-event.exp that focuses
   only on reproducing the duplicate, without any solib-event specific code. */

#include <hip/hip_runtime.h>
#include <cstdio>
#include <cstdlib>

__global__ void
warm_up ()
{
}

static void
test_function ()
{
  printf ("Inside test_function\n");  /* BREAKPOINT_HERE */
}

int
main ()
{
  /* Submit an empty kernel to initialize HIP runtime.
     This is what triggers the duplicate MI notification bug. */
  warm_up<<<1, 1>>>();

  hipError_t err = hipDeviceSynchronize ();
  if (err != hipSuccess)
    {
      fprintf (stderr, "hipDeviceSynchronize failed: %d\n", err);
      return EXIT_FAILURE;
    }

  printf ("HIP runtime initialized\n");

  /* Call function where we set breakpoint.
     In MI mode, hitting this breakpoint will show duplicate notifications. */
  test_function ();

  return 0;
}
