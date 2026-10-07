#include <stdio.h>

void test_function(void)
{
  printf("Inside test_function\n");
}

int main(void)
{
  printf("Starting program\n");
  test_function();
  printf("Exiting program\n");
  return 0;
}
