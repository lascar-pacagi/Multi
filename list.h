#ifndef LIST_H
#define LIST_H

#include "utility.h"
#include <stdlib.h>

struct list_block {
  int priority;
  int element;
  struct list_block* previous;
  struct list_block* next;
};

typedef struct list_block* list;

#define EMPTY_LIST ((struct list_block*)NULL)

/*
  insère l'élement 'element' de priorité 'priority' dans la list 'l' et retourne
  la liste ainsi modifiée. Les éléments de plus forte priorité sont placés en début de liste.
  Exemple :
    list l = EMPTY_LIST;       // l = EMPTY_LIST
    l = insert_list(l, 10, 4); // l = [10,4]->EMPTY_LIST
    l = insert(l, 1, 8);       // l = [1,8]->[10,4]->EMPTY_LIST
*/
list insert_list(list l, int priority, int element);

/*
  retire l'élement 'element' de la list 'l' et retourne
  la liste ainsi modifiée.
  Exemple :
    list l = EMPTY_LIST;       // l = EMPTY_LIST
    l = insert_list(l, 10, 4); // l = [10,4]->EMPTY_LIST
    l = insert(l, 1, 8);       // l = [1,8]->[10,4]->EMPTY_LIST
    l = remove_list(l, 4);     // l = [1,8]->EMPTY_LIST
*/
list remove_list(list l, int element);

/* libére la place allouée aux éléments de la liste 'l' et retourne la liste EMPTY_LIST */
list erase_list(list l);

/* rend vrai ssi 'l' est la liste vide */
bool is_empty_list(list l);

/* rend vrai ssi 'l' contient l'élément 'element' */
bool is_in_list(list l, int element);

/* affiche la liste 'l' */
void display_list(list l);

/* retourne le premier élément de la list ou -1 si la liste est vide */
int get_first_element(list l);

/* retourne la priorité du premier élément de la list ou -1 si la liste est vide */
int get_first_priority(list l);

#endif
