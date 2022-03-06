//========================================================================
// vector-adhoc.c
//========================================================================
// This file contains an ad-hoc test for vector-related functions

#include "vector.h"
#include <stdio.h>

int main() {

  vector_int_t vec;
  vector_int_construct    ( &vec  );
  vector_int_push_back_v2 ( &vec, 11 );
  vector_int_push_back_v2 ( &vec, 12 );
  //vector_int_push_back_v1 ( &vec, 13 );

  //printf( "Value stored at index 0 is %d\n", vector_int_find_closest( &vec, 2000 ) );
  printf( "Value stored at index 1 is %d\n", vector_int_at( &vec, 0 ) );
  printf( "Value stored at index 2 is %d\n", vector_int_at( &vec, 1 ) );

  vector_int_destruct  ( &vec );

  return 0;
}
