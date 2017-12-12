/* This testcase is part of GDB, the GNU debugger.

   Copyright 2017 Free Software Foundation, Inc.

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

/* This file will be used to test 'ptype /o' on x86_64 only.  */

#include <stdint.h>

/* A struct with many types of fields, in order to test 'ptype
   /o'.  */

struct abc
{
  /* Virtual destructor.  */
  virtual ~abc ()
  {}

  /* 8-byte address.  Because of the virtual destructor above, this
     field's offset will be 8.  */
  void *field1;

  /* No hole here.  */

  /* 4-byte int bitfield of 1-bit.  */
  unsigned int field2 : 1;

  /* 31-bit hole here.  */

  /* 4-byte int.  */
  int field3;

  /* No hole here.  */

  /* 1-byte char.  */
  char field4;

  /* 7-byte hole here.  */

  /* 8-byte int.  */
  uint64_t field5;

  /* We just print the offset and size of a union, ignoring its
     fields.  */
  union
  {
    /* 8-byte address.  */
    void *field6;

    /* 4-byte int.  */
    int field7;
  } field8;

  /* Empty constructor.  */
  abc ()
  {}
};

/* This struct will be nested inside 'struct xyz'.  */

struct tuv
{
  int a1;

  char *a2;

  int a3;
};

/* This struct will be nested inside 'struct pqr'.  */

struct xyz
{
  int f1;

  char f2;

  void *f3;

  struct tuv f4;
};

/* A struct with a nested struct.  */

struct pqr
{
  int ff1;

  struct xyz ff2;

  char ff3;
};

/* A union with two nested structs.  */

union qwe
{
  struct tuv fff1;

  struct xyz fff2;
};

/* A struct with an union.  */

struct poi
{
  int f1;

  union qwe f2;

  uint16_t f3;

  struct pqr f4;
};

int
main (int argc, char *argv[])
{
  struct abc foo;
  struct pqr bar;
  union qwe c;
  struct poi d;
  uint8_t i;

  return 0;
}
