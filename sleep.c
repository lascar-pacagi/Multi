#include "sleep.h"
#include "interrupt.h"
#include "scheduler.h"
#include "thread.h"
#include <stdio.h>

bool sleep(int n)
{
  status old = disable();
  if (n <= 0) 
    {
      restore(old);
      return false;
    }

  thread_table[current_thread].state = ASLEEP;
  sleep_list = insert_list(sleep_list, -(time_counter + n), current_thread);
  reschedule();

  restore(old);
  return true;
}

void wake_up()
{
  if (is_empty_list(sleep_list)) return;
  if (-get_first_priority(sleep_list) > time_counter) return;

  while (-get_first_priority(sleep_list) == time_counter)
    {
      ready(get_first_element(sleep_list), false);
      sleep_list = remove_list(sleep_list, get_first_element(sleep_list));
      if (is_empty_list(sleep_list)) break;
    }
  reschedule();
}

