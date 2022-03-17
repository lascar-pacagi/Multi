#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "list.h"

extern list ready_list;

bool ready(int thread_id, bool resched); 
bool reschedule();

#endif
