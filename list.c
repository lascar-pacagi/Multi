#include "list.h"
#include <stdio.h>

list insert_list(list l, int priority, int element) 
{
  list prev = EMPTY_LIST, curr = l;

  while (curr != EMPTY_LIST && curr->priority >= priority)
    {
      prev = curr; curr = curr->next;
    }
  
  list b = (list)malloc(sizeof(struct list_block));
  
  b->priority = priority;
  b->element = element;
  b->previous = prev;
  b->next = curr;
  
  if (prev != EMPTY_LIST) prev->next = b;
  if (b->next != EMPTY_LIST) b->next->previous = b;
  return (l == EMPTY_LIST || b->next == l ? b : l);
}

list remove_list(list l, int element)
{
  list prev = EMPTY_LIST, curr = l;
  
  while (curr != EMPTY_LIST && curr->element != element)
    {
      prev = curr; curr = curr->next;
    }
  
  if (curr != EMPTY_LIST)
    {
      if (prev != EMPTY_LIST) prev->next = curr->next;
      if (curr->next != EMPTY_LIST) curr->next->previous = prev;
      list ret = (l != curr ? l : curr->next);
      free(curr);
      return ret;
    }
  return l;
}

int get_first_element(list l)
{
  if (l == EMPTY_LIST) return -1;
  return l->element;
}

int get_first_priority(list l)
{
  if (l == EMPTY_LIST) return -1;
  return l->priority;
}

list erase_list(list l)
{
  list curr = l, tmp;
  
  while (curr != EMPTY_LIST)
    {
      tmp = curr; curr = curr->next;
      free(tmp);
    }

  return EMPTY_LIST;
}

bool is_empty_list(list l)
{
  return l == EMPTY_LIST;
}

bool is_in_list(list l, int element)
{
  list curr = l;

  while (curr != EMPTY_LIST)
    {
      if (curr->element == element) return true;
      curr = curr->next;      
    }

  return false;
}

void display_list(list l)
{
  list curr = l;
  printf("[");
  while (curr != EMPTY_LIST)
    {
      printf("(%d,%d)",curr->priority,curr->element);
      curr = curr->next;
    }
  printf("]\n");
}

/*
int main()
{
  list l = EMPTY_LIST;
  l = insert_list(l,1,1);
  display_list(l);
  l = insert_list(l,3,3);
  display_list(l);
  l = insert_list(l,0,0);
  display_list(l);
  l = insert_list(l,2,2);
  display_list(l);
  l = remove_list(l,1);
  l = remove_list(l,2);
  l = remove_list(l,3);
  l = remove_list(l,0);
  //l = erase_list(l);
  printf("%d\n",l);
  return 0;
}
*/
