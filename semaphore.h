#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "list.h"

#define MAX_NB_SEMAPHORE 1024

enum {SFREE=0, SUSED=1};

#define is_bad_sem_id(x) (x < 0 || x >= MAX_NB_SEMAPHORE)

typedef struct {
  int state;
  int count;
  list waiting_list;
} semaphore;

extern semaphore semaphore_table[];

void initialize_semaphore();
int create_semaphore(int count);
bool destroy_semaphore(int sem);
bool p(int sem);
bool v(int sem);

#endif 
