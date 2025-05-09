/* Copyright 2023-2025 Free Software Foundation, Inc.

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

struct special_type
{
  /* Discriminator used by the pretty-printer.  When zero, no fields
     are shown; when non-zero, shows the datum.  */
  int disc;
  int datum;
};

struct special_type empty = { 0, 23 };
struct special_type full = { 1, 23 };

int
main ()
{
  struct special_type value = full;

  return 0;			/* STOP */
}
