#include "scheduler.h"
#include "ctxsw.h"
#include "thread.h"
#include "time.h"
#include "interrupt.h"
#include <stdio.h>

bool reschedule()
{
  thread *oldptr, *newptr;

  if ((oldptr = &thread_table[current_thread])->state == CURRENT && !is_empty_list(ready_list) &&
      get_first_priority(ready_list) < oldptr->priority)
    return false;

  if (oldptr->state == CURRENT)
    {
      oldptr->state = READY;
      ready_list = insert_list(ready_list, oldptr->priority, current_thread);
    }

  newptr = &thread_table[current_thread = get_first_element(ready_list)];
  ready_list = remove_list(ready_list, current_thread);
  newptr->state = CURRENT;

#ifdef PREEMPT
  preempt = QUANTUM;
#endif

  ctxsw(oldptr->registers, newptr->registers);

  return true;
}

bool ready(int thread_id, bool to_switch)
{
  thread* threadptr;
  
  if (is_bad_thread_id(thread_id) || (threadptr = &thread_table[thread_id])->state == FREE)
    return false;

  threadptr->state = READY;
  ready_list = insert_list(ready_list, threadptr->priority, thread_id);
  if (to_switch) reschedule();
  return true;
}
