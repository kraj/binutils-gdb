#include <stdio.h>
#include <syscall.h>
#include <asm/prctl.h>

extern int foo;
extern int __gp;
extern int foo_gprel;
extern int get_foo (void);

int
setup_gp (void *p)
{
  int result;
  asm volatile ("syscall"
		: "=a" (result)
		: "0" ((unsigned long int) SYS_arch_prctl),
		  "D" ((unsigned long int) ARCH_SET_GS),
		  "S" (p)
		: "memory", "cc", "r11", "cx");
  return result;
}

int
main ()
{
  setup_gp (&__gp);
  if (foo == 0x12345678
      && *(int *) ((char *) &__gp + foo_gprel) == 0x12345678
      && get_foo () == 0x12345678)
    printf ("PASS\n");
  return 0;
}
