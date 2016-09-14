/* This testcase is part of GDB, the GNU debugger.

   Copyright 2016 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

static int volatile quit = 0;

static void
child_sub_function (void)
{
  while (!quit); /* thread loop line */
}

static void *
child_function (void *args)
{
  child_sub_function (); /* thread caller line */

  return NULL;
}

int
main (void)
{
  int i = 0;
  pthread_t threads[NUM_THREADS];

  for (i = 0; i < NUM_THREADS; i++)
    pthread_create (&threads[i], NULL, child_function, NULL);

  /* Leave enough time for the threads to reach their infinite loop. */
  sleep (1);
  
  i = 0; /* main break line */

  sleep (2);
  
  /* Allow the test to exit cleanly.  */
  quit = 1;

  for (i = 0; i < NUM_THREADS; i++)
    pthread_join (threads[i], NULL);

  return 0;
}
