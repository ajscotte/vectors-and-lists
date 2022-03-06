//========================================================================
// list-directed-test.c
//========================================================================
// This section contains directed tests for list-related functions.

// comment to self: pointer ,ust be null if doesn't point to any other node
// test for pointing to both nodes
//test every function
//test construct
//test destruct
// test pushback  will never return NULL).
//test size
// test at
// test contains
// test find closest

#include "list.h"
#include "ece2400-stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//------------------------------------------------------------------------
// test_case_1_simple_push_back
//------------------------------------------------------------------------
// A simple test case that tests one element push back.

void test_case_1_simple_push_back()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  list_int_push_back( &lst, 0x22222bad );
  ECE2400_CHECK_INT_EQ( list_int_size( &lst    ), 1          );
  ECE2400_CHECK_INT_EQ( list_int_at  ( &lst, 0 ), 0x22222bad );

  list_int_destruct( &lst );
}


//------------------------------------------------------------------------
// test_case_2_large_size
//------------------------------------------------------------------------
// Tests if size can return a large list size and each size up to that point
// By Alexander Scotte(ajs677)

void test_case_2_large_size()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  //adds a value to the list then checks to see if size has changed
  for(int i = 0; i < 10000; i++ ){
    ECE2400_CHECK_INT_EQ( list_int_size( &lst ), i);
    list_int_push_back( &lst, i );
  }

list_int_destruct( &lst );
}

// create a size test that returns undefind after destruct
//------------------------------------------------------------------------
// test_case_3_changing_index_at
//------------------------------------------------------------------------
/*  Tests to see if list_int_at can return the correct value as the list changes size
    and tests to see that items are only added to end of changing list
*/
// Author: Alexander Scotte(ajs677)
void test_case_3_changing_index_at()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  for( int i = 0; i < 1000; i++ ){
    list_int_push_back( &lst,                     i );
    ECE2400_CHECK_INT_EQ( list_int_at( &lst, i ), i );
    // checks to see that items are only added to back of list
    ECE2400_CHECK_INT_EQ( list_int_at( &lst, 0),  0 );
  }

  list_int_destruct( &lst );
}
//test_case_4_out_of_bounds_at
//------------------------------------------------------------------------
// tests to see if both negative and positive index values that out of bounds return 0
// Author: Alexander Scotte(ajs677)
void test_case_4_out_of_bounds_at()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  list_int_push_back( &lst, 1);

  //tests for out of bounds
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, 9 ),       0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, 1 ),       0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, 100 ),     0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, INT_MAX ), 0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, -2 ),      0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, -100 ),    0 );
  ECE2400_CHECK_INT_EQ( list_int_at( &lst, INT_MIN ), 0 );

list_int_destruct( &lst) ;
}

//------------------------------------------------------------------------
// test_case_5_simple_contains
//------------------------------------------------------------------------
// Push 2 elements and see if they can still be found.
void test_case_5_simple_contains()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  // Push back some elements
  for ( int i = 0; i < 2; i++ ){
    list_int_push_back( &lst, i );
  }
  // Try finding them
  for ( int i = 0; i < 2; i++ ){
    ECE2400_CHECK_TRUE( list_int_contains( &lst, i ) )
}
  // Check size
  ECE2400_CHECK_INT_EQ( list_int_size( &lst ), 2 );

  list_int_destruct( &lst );
}
//------------------------------------------------------------------------
// test_case_6_large_contains
//------------------------------------------------------------------------
// Tests to see if the contains function can handle a large list of values
// Author: Alexander Scotte(ajs667)
void test_case_6_large_contains()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  for( int i = 0; i < 1000; i++ )  {
    list_int_push_back( &lst, i);
  }
  for( int i = 0; i < 1000; i++ )  {
    //printf("contains: %d /n", i );
    ECE2400_CHECK_TRUE(list_int_contains( &lst, i));
  }
list_int_destruct( &lst);
  
}

void test_case_7_does_not_contain()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );
  
  //test empty list
  ECE2400_CHECK_FALSE( list_int_contains( &lst, 20));
  ECE2400_CHECK_FALSE( list_int_contains( &lst, INT_MAX));
  ECE2400_CHECK_FALSE( list_int_contains( &lst, -50));
  ECE2400_CHECK_FALSE( list_int_contains( &lst, INT_MIN));
  list_int_destruct(&lst);
}
//------------------------------------------------------------------------
// test_case_8_exact_closest
//------------------------------------------------------------------------
// A test case that tests for numbers in a list that are the exct value as the input
// Author: Alexander Scotte(ajs667)
void test_case_8_exact_closest()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  for( int i = 0; i < 100; i++ ){
    list_int_push_back( &lst, i );
  }
  for( int i = 0; i < 100; i++ ){
    ECE2400_CHECK_INT_EQ(list_int_find_closest( &lst, i ), i );
  }
  list_int_destruct(&lst);
}
//------------------------------------------------------------------------
// test_case_9_offset_simple_closest
//------------------------------------------------------------------------
// A test case that tests for numbers in a list that are the exct value as the input
// Author: Alexander Scotte(ajs667)
void test_case_9_offset_simple_closest()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  for( int i = 0; i < 1000; i = i + 3 ){
    list_int_push_back( &lst, i );
  }
  for( int i = 1; i < 1001; i = i + 3 ){
    ECE2400_CHECK_INT_EQ(list_int_find_closest( &lst, i ), i-1);
  }
  list_int_destruct(&lst);
}

//------------------------------------------------------------------------
// test_case_10_equidistant_closest
//------------------------------------------------------------------------
// Check if for list_int_find_closest of a value with two equidistant 
// solutions in the list, the oner closer to the header is selected.
// Author: Ved Kumar

void test_case_10_equidistant_closest()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );

  // Push back elements
  for (int i = 1; i < 4; i++) {
   list_int_push_back(&lst, -2*i);
   list_int_push_back(&lst, 2*i); 
   list_int_push_back(&lst, 8*i);
  }

  // Check output value is the one closer to the header
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 0 ), -2 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, -5 ), -4 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 1 ), 2 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 5 ), 4 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 7 ), 8 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 12 ), 8 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 20 ), 16 );

  list_int_destruct( &lst );
}
//------------------------------------------------------------------------
// test_case_11_closest_large
//------------------------------------------------------------------------
// A test case that tests searching for the closest with large numbers,
// Author: Scott Faber

void test_case_11_closest_large()
{
  printf( "\n%s\n", __func__ );

  list_int_t lst;
  list_int_construct( &lst );
  
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, 0 ), -1 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, INT_MAX ), -1 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, INT_MAX - 16 ), -1 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, -48 ), -1 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, INT_MIN ), -1 );
  ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, INT_MIN + 16 ), -1 );
  
  
  list_int_destruct( &lst );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) )  test_case_1_simple_push_back();
  if ( ( __n <= 0 ) || ( __n == 2 ) )  test_case_2_large_size();
  if ( ( __n <= 0 ) || ( __n == 3 ) )  test_case_3_changing_index_at();
  if ( ( __n <= 0 ) || ( __n == 4 ) )  test_case_4_out_of_bounds_at();
  if ( ( __n <= 0 ) || ( __n == 5 ) )  test_case_5_simple_contains();
  if ( ( __n <= 0 ) || ( __n == 6 ) )  test_case_6_large_contains();
  if ( ( __n <= 0 ) || ( __n == 7 ) )  test_case_7_does_not_contain();
  if ( ( __n <= 0 ) || ( __n == 8 ) )  test_case_8_exact_closest();
  if ( ( __n <= 0 ) || ( __n == 9 ) )  test_case_9_offset_simple_closest();
  if ( ( __n <= 0 ) || ( __n == 10 ) ) test_case_10_equidistant_closest();
  if ( ( __n <= 0 ) || ( __n == 11 ) ) test_case_11_closest_large();
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  printf( "\n" );
  return __failed;
}
