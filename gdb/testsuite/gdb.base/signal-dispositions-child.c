/* Copyright 2016 Free Software Foundation, Inc.

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

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#ifndef OUTPUT_TXT
# define OUTPUT_TXT "output.txt"
#endif

int
main (int argc, char **argv)
{
  int i;
  FILE *out;

  if (argc > 1)
    out = stdout;
  else
    {
      out = fopen (OUTPUT_TXT, "w");
      if (out == NULL)
	{
	  fprintf (stderr, "File open failed\n");
	  exit (1);
	}
    }

  for (i = 1; i < NSIG; i++)
    {
      struct sigaction oldact;

      sigaction (i, NULL, &oldact);

      if (oldact.sa_handler == SIG_DFL)
	fprintf (out, "%d: SIG_DFL\n", i);
      else if (oldact.sa_handler == SIG_IGN)
	fprintf (out, "%d: SIG_IGN\n", i);
      else
	abort ();
    }

  if (out != stdout)
    fclose (out);

  return 0;
}
