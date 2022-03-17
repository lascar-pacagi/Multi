#ifndef SLEEP_H
#define SLEEP_H

#include "utility.h"
#include "time.h"
#include "list.h"

extern list sleep_list;

/* wait for n * 10 ms */
bool sleep(int n);
void wake_up();

#endif
