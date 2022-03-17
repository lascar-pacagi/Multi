#include "message.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"

bool send(int thread_id, int message) {
  thread* threadptr;
  status old = disable();
  
  if (is_bad_thread_id(thread_id) || (threadptr = &thread_table[thread_id])->state == FREE || threadptr->received)
    {
      restore(old);
      return false;
    }

  threadptr->received = true;
  threadptr->message = message;
  if (threadptr->state == RECEIVE)
    ready(thread_id, true);

  restore(old);
  return true;
}


int receive() {
  thread* threadptr;
  status old = disable();
  int msg;

  threadptr = &thread_table[current_thread];
  if (threadptr->received == false) {
    threadptr->state = RECEIVE;
    reschedule();
  }
  msg = threadptr->message;
  threadptr->received = false;
  restore(old);
  return msg;
}
