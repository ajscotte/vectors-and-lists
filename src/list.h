//========================================================================
// list.h
//========================================================================
// Interface for doubly linked list

#ifndef LIST_H
#define LIST_H

#include <stddef.h> // for size_t

typedef struct _list_int_node_t 
{
  int                      value;
  struct _list_int_node_t* next_p;
  struct _list_int_node_t* prev_p;
}
list_int_node_t;
typedef struct
{
  list_int_node_t* head_p;
  list_int_node_t* tail_p;
  size_t           size;
}
list_int_t;

void   list_int_construct    ( list_int_t* this  );
void   list_int_destruct     ( list_int_t* this  );
size_t list_int_size         ( list_int_t* this  );
void   list_int_push_back    ( list_int_t* this, int    value );
int    list_int_at           ( list_int_t* this, size_t idx   );
int    list_int_contains     ( list_int_t* this, int    value );
int    list_int_find_closest ( list_int_t* this, int    value );
void   list_int_print        ( list_int_t* this  );

#endif // LIST_H
