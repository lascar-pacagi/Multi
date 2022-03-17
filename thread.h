#ifndef THREAD_H
#define THREAD_H

#include "utility.h"
#include "list.h"
#include <stdalign.h>

#define DEFAULT_PRIORITY 10
#define MAX_NB_THREAD 16
#define STACK_SIZE 65536
#define NULL_THREAD 0

#define is_bad_thread_id(x) (x <= 0 || x >= MAX_NB_THREAD)

#define NB_REGISTERS 16

enum {CURRENT, READY, WAITING, JOIN, ASLEEP, SUSPENDED, RECEIVE, FREE};

typedef struct {
  int   state;                   // thread state: CURRENT, READY, ...
  int   priority;                // thread priority
  int   semaphore;               // semaphore if thread wainting on a semaphore
  char* name;                    // thread name
  long  registers[NB_REGISTERS]; // saved registers
  long  stack[STACK_SIZE];       // lowest address of run time stack
  list  join_list;
  int   join_thread;
  int   message;
  bool  received;
} thread;

extern thread thread_table[];
extern int nb_thread;
extern int current_thread;
extern list alive_list;

#define get_thread_id() current_thread

void initialize_thread();
int create_thread(long initial_address, int priority, char* name, int nb_args, ...);
bool destroy_thread(int thread_id);
void yield();
bool join(int thread_id);
bool suspend(int thread_id);
bool resume(int thread_id);
int get_priority(int thread_id);

#endif
