//========================================================================
// list.c
//========================================================================
// Implementation of the list functions.

#include "list.h"
#include "ece2400-stdlib.h"
#include <assert.h>
//------------------------------------------------------------------------
// list_int_construct
//------------------------------------------------------------------------
// Construct the list_int_t and initialize the fields inside.


void list_int_construct( list_int_t* this )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_construct(%p) called!", this );
  // initialized list
  this->head_p = NULL;
  this->tail_p = NULL;
  this->size   = 0;
}

//------------------------------------------------------------------------
// list_int_destruct
//------------------------------------------------------------------------
// Destruct the list_int_t, freeing any dynamically allocated memory if
// necessary.

void list_int_destruct( list_int_t* this )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_destruct(%p) called!", this );
  list_int_node_t *helper = this->tail_p;
  // frees nodes in which helper is pointing 
  while(this->tail_p != NULL){
      this->tail_p = helper->prev_p;
      ece2400_free(helper);
      this->size--;
      helper = this->tail_p;
  }
  ece2400_free(helper);
}

//------------------------------------------------------------------------
// list_int_size
//------------------------------------------------------------------------
// Get the number of elements in the list.

size_t list_int_size( list_int_t* this )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_size(%p) called!", this );
  // returns sise using pointer
  return this->size;
}

//------------------------------------------------------------------------
// list_int_push_back
//------------------------------------------------------------------------
// Push a new value into the list_int_t.

void list_int_push_back( list_int_t* this, int value )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_push_back(%p, %d) called!", (void*) this, value );
  list_int_node_t *new_node = (list_int_node_t*) ece2400_malloc(sizeof(list_int_node_t));
  new_node->value  = value;
  new_node->next_p = NULL;
  // case when no nodes preent
  if(this->head_p == NULL){
    new_node->prev_p = NULL;
    this->head_p     = new_node;
    this->size       = 1;
    this->tail_p     = new_node;
  }
  // case when there are nodes in list
  else{
    this->tail_p->next_p = new_node;
    new_node->prev_p     = this->tail_p;
    this->size           = this->size + 1;
    this->tail_p         = new_node;
  }
  
}

//------------------------------------------------------------------------
// list_int_at
//------------------------------------------------------------------------
// Pointer chase and return the value at the given index
// If the index is out of bound, then return 0.

int list_int_at( list_int_t* this, size_t idx )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_at(%p, %lu) called!", this, idx );
  list_int_node_t *traverser;
  unsigned int counter;
  unsigned int middle_list = ( this->size )/2;
  //case when index out of bounds or size of list is zero
  if( idx >= this->size || this->size == 0 ){
    return 0;
  }
  // case when index is lower than the middle of the list
  else if(middle_list> idx ){
    counter = 0;
    traverser = this->head_p;
    while( counter != idx ){
      traverser = traverser->next_p;
      counter++;
    }
  }
  //case when index is greater than the middle of the list
  else{
    counter = this->size - 1;
    traverser = this->tail_p;
    while( counter != idx ){
      traverser = traverser->prev_p;
      counter--;
  }
  }
  return traverser->value;
}

//------------------------------------------------------------------------
// list_int_contains
//------------------------------------------------------------------------
// Search the list for a value and return whether a value is found or not.
// Returning 1 means found, and 0 means not found.

int list_int_contains( list_int_t* this, int value )
{
  //assert( this != NULL );
  //ECE2400_DEBUG( "list_int_contains(%p, %lu) called!", this, value );
  list_int_node_t *comparison = this->head_p; 
  for( size_t i = 0; i < this->size; i++ ) {
    // returns 1 if contains or 0 if it doesn't by traversing list
    if( comparison->value == value ){
      return 1;
    }
    comparison = comparison->next_p;
  }
  return 0;

}

//------------------------------------------------------------------------
// list_int_find_closest
//------------------------------------------------------------------------
// Search the list for a value that is closest to the given value.
// If there are multiple values that are closest, return the one with the
// smallest index.
// Return -1 when the list is empty. Otherwise return the closest value.

int list_int_find_closest( list_int_t* this, int value )
{
  assert( this != NULL );
  ECE2400_DEBUG( "list_int_find_closest(%p, %d) called!", this, value );
  
  list_int_node_t *traverser = this->head_p;
  // case when size of list is zero
  if( this->size == 0 ){
    return -1;
  }
  // calulates difference in list value and value being compared
  int difference = traverser->value - value;
  if ( difference < 0 ){
    difference = difference*-1;
  }
  // searches through list to find closest value
  int answer = traverser->value;
  for( size_t i = 0; i < this->size; i++ ){
    int comparison = traverser->value - value;
    if( comparison < 0 ){
      comparison = comparison*-1;
    }
    if( difference > comparison ){
      difference = comparison;
      answer     = traverser->value;
    }
    traverser = traverser->next_p;
  }

  return answer;

}


//------------------------------------------------------------------------
// list_int_print
//------------------------------------------------------------------------
// Print out the content of list_int_t.

//void list_int_print( list_int_t* this )
//{
  //assert( this != NULL );
//}
