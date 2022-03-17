#include <stdio.h>
#include "thread.h"
#include "sleep.h"

void fct(long n)
{
  while (true)
    {
      sleep(5);
      printf("%ld\n", n);
    }
}

int main()
{
  printf("start of main\n");
  resume(create_thread((long)fct, DEFAULT_PRIORITY, "thread1", 1, 1));
  resume(create_thread((long)fct, DEFAULT_PRIORITY, "thread2", 1, 2));
  resume(create_thread((long)fct, DEFAULT_PRIORITY, "thread3", 1, 3));
  printf("end of main\n");
  return 0;
}
