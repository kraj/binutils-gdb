#include <stdio.h>

int foo[1];

extern int *foo_p (void);

int
main ()
{
  if (foo[0] == 0 && foo == foo_p ())
    printf ("PASS\n");
  return 0;
}
