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

/* Minimal reproducer for duplicate MI notification bug.

   Matches solib-event.cpp but only tests for duplicate notifications
   at the breakpoint, not solib-event functionality. */

#include <hip/hip_runtime.h>
#include <cstdio>
#include <cstdlib>

#define CHECK(cmd)                                                            \
  do                                                                          \
    {                                                                         \
      hipError_t error = (cmd);                                               \
      if (error != hipSuccess)                                                \
	{                                                                     \
	  fprintf (stderr, "error: '%s'(%d) at %s:%d\n",                      \
		   hipGetErrorString (error), error, __FILE__, __LINE__);    \
	  exit (EXIT_FAILURE);                                                \
	}                                                                     \
    }                                                                         \
  while (0)

__global__ void
warm_up ()
{
}

static void
test_function (const char *module_path)
{
  hipModule_t module;
  CHECK (hipModuleLoad (&module, module_path));  /* BREAKPOINT_HERE */

  hipFunction_t function;
  CHECK (hipModuleGetFunction (&function, module, "test_kernel"));

  CHECK (hipModuleLaunchKernel (function, 1, 1, 1, 1, 1, 1,
				0, nullptr, nullptr, nullptr));

  CHECK (hipDeviceSynchronize ());
  CHECK (hipModuleUnload (module));
}

int
main (int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s <module_path>\n", argv[0]);
      return EXIT_FAILURE;
    }

  const char *module_path = argv[1];

  /* Initialize HIP runtime. */
  warm_up<<<1, 1>>>();
  CHECK (hipDeviceSynchronize ());

  /* Enable SOLIB events here.  */

  test_function (module_path);

  return 0;
}
