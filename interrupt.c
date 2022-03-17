#include "interrupt.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

status disable()
{
  sigset_t set;
  sigset_t old;
  sigemptyset(&set);
  sigaddset(&set, SIGALRM);

  sigprocmask(SIG_SETMASK, &set, &old);
  return old;
}

void enable()
{
  sigset_t set;
  sigemptyset(&set);

  sigprocmask(SIG_SETMASK, &set, NULL);
}

void restore(status old)
{
  sigprocmask(SIG_SETMASK, &old, NULL);
}

