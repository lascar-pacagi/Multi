#include "utility.h"
#include "thread.h"
#include "semaphore.h"
#include "ctxsw.h"
#include "time.h"
#include "interrupt.h"
#include "scheduler.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

extern int main();

thread thread_table[MAX_NB_THREAD+1];
int nb_thread;
int current_thread;
semaphore semaphore_table[MAX_NB_SEMAPHORE];
list ready_list;
list alive_list;
list sleep_list;
int time_counter;
#ifdef PREEMPT
int preempt;
#endif

void sysinit();

/*
La procédure nulluser est le point d'entrée du programme.
nulluser est le code de NULL_THREAD, le thread qui
prend la main lorsqu'aucun thread n'est prêt à s'exécuter. Ce thread
ne peut pas être tué ou mis en attente. Lorsqu'il prend
la main ce thread vérifie que la liste 'alive_list' n'est pas vide. Si elle n'est
pas vide, il y a une attente active pour attendre qu'un thread soit réveillé
par le clock_handler, sinon multi se termine.
*/
void nulluser()
{
  sysinit();
  int t = create_thread((long)main, DEFAULT_PRIORITY, "main", 0);
  if (t != -1) {
    resume(t);
    bool stop = false;
    while (!stop)
      {
        status flag = disable();
        stop = is_empty_list(alive_list);
        restore(flag);
      }
    free(thread_table[NULL_THREAD].name);
    printf("no more thread to run... bye\n");
  } else {
    printf("impossible to create the main thread... bye\n");
  }
  _exit(0);
}

/*
Cette méthode permet d'initialiser les structures de données globales
du système. Notons que la pile de NULL_THREAD n'est pas celle dans thread_table[NULL_THREAD],
mais la pile allouée au programme multi.
*/
void sysinit()
{
  thread* threadptr;
  struct itimerval t;

  initialize_thread();
  initialize_semaphore();
  ready_list = EMPTY_LIST;
  alive_list = EMPTY_LIST;
  sleep_list = EMPTY_LIST;

  threadptr = &thread_table[NULL_THREAD];
  threadptr->state = CURRENT;
  threadptr->priority = -1;
  threadptr->name = malloc(10 * sizeof(char));
  strcpy(threadptr->name, "null user");
  current_thread = NULL_THREAD;
  nb_thread = 0;

  time_counter = 0;
#ifdef PREEMPT
  preempt = 1;
#endif  

  t.it_value.tv_sec = 0;
  t.it_value.tv_usec = 10000;
  t.it_interval.tv_sec = 0;
  t.it_interval.tv_usec = 10000;

  signal(SIGALRM, clock_handler);   //la procédure clock_handler
  setitimer(ITIMER_REAL, &t, NULL); //est appelée toutes les 10ms
}
