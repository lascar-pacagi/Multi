#include "time.h"
#include "scheduler.h"
#include "interrupt.h"
#include "sleep.h"
#include <stdio.h>

void clock_handler(int sig)
{
  time_counter++;
  wake_up();
#ifdef PREEMPT
  if (--preempt <= 0) { reschedule(); }
#endif
}
