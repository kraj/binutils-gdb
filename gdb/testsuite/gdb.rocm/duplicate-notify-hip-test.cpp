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

/* Minimal HIP program to test for duplicate MI notifications bug. */

#include <hip/hip_runtime.h>
#include <stdio.h>

void test_function()
{
  printf("Inside test_function\n");  /* Breakpoint here. */
}

int main()
{
  int device_count = 0;
  hipError_t err;

  printf("Starting HIP program\n");

  /* Initialize HIP runtime. */
  err = hipGetDeviceCount(&device_count);
  if (err != hipSuccess)
    {
      fprintf(stderr, "hipGetDeviceCount failed: %d\n", err);
      return 1;
    }

  printf("Found %d GPU devices\n", device_count);

  /* Call function where we'll set breakpoint. */
  test_function();

  printf("Exiting HIP program\n");
  return 0;
}
