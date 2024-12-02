/* Copyright 2024 Free Software Foundation, Inc.

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

/* Used to insert labels with which we can build a fake line table.  */
#define LL(N) asm ("line_label_" #N ": .globl line_label_" #N)

/* The following non-compiled code exists for the generated line table to
   point at.  */

#if 0

volatile int global = 0;

__attribute__((noinline, noclone)) void
foo (int arg)
{			/* foo prologue */
  asm ("");
  global += arg;
}

inline __attribute__((always_inline)) int
bar (void)
{
  return 1;		/* bar body */
}

int
main (void)
{			/* main prologue */
  foo (bar ());		/* call line */
  return 0;
}

#endif	/* 0 */

volatile int var;

/* Generate some code to take up some space.  */
#define FILLER do { \
    var = 99;	    \
} while (0)

void
func (void)
{
  asm ("func_label: .globl func_label");
  FILLER;
  LL (1);
  FILLER;
  LL (2);
  return;
}

int
main (void)
{
  asm ("main_label: .globl main_label");
  FILLER;
  LL (4);
  FILLER;
  LL (5);
  func ();
  FILLER;
  LL (6);
  FILLER;
  return 0;
}
