//========================================================================
// list-adhoc.c
//========================================================================
// This file contains an ad-hoc test for list-related functions

#include "list.h"
#include <stdio.h>

int main() {

  list_int_t lst;
  list_int_construct ( &lst );
  list_int_push_back ( &lst, 17 );
  list_int_push_back ( &lst, 12 );
  list_int_push_back ( &lst, 21 );
  list_int_push_back ( &lst, 30 );

  printf( "Value stored at index 0 is %d\n", list_int_find_closest(&lst, 0) );
  printf( "Value stored at index 1 is %d\n", list_int_at( &lst, 1 ) );
  printf( "Value stored at index 2 is %d\n", list_int_at( &lst, 2 ) );
  printf( "Value stored at index 3 is %d\n", list_int_at( &lst, 3 ) );

  list_int_destruct  ( &lst );

  return 0;
}
