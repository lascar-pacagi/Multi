#ifndef TIME_H
#define TIME_H

#define QUANTUM 10

extern int time_counter;
#ifdef PREEMPT
extern int preempt;
#endif

void clock_handler(int sig);

#endif
