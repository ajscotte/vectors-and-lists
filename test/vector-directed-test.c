//========================================================================
// vector-directed-test.c
//========================================================================
// This file contains directed tests for vector-related functions.

#include "vector.h"
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

  vector_int_t vec;
  vector_int_construct( &vec );

  vector_int_push_back_v1( &vec, 0xbad22222 );
  ECE2400_CHECK_INT_EQ( vector_int_size( &vec    ), 1          );
  ECE2400_CHECK_INT_EQ( vector_int_at  ( &vec, 0 ), 0xbad22222 );

  vector_int_destruct( &vec );
}



//------------------------------------------------------------------------
// test_case_2_large_size
//------------------------------------------------------------------------
// Tests if size can return a large vector size and each size up to that point
// By Alexander Scotte(ajs677)

void test_case_2_large_size_vector()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  //adds a value to the vector then checks to see if size has changed also checks if has nothing in vector
  for(int i = 0; i < 10000; i++ ){
    ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), i);
    vector_int_push_back_v1( &vec, i );
  }

vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_3_changing_index_at_vector
//------------------------------------------------------------------------
/*  Tests to see if list_int_at can return the correct value as the list changes size
    and tests to see that items are only added to end of changing list
*/

void test_case_3_changing_index_at_vector()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );
  vector_int_push_back_v1(&vec, 10);
  for( int i = 1; i < 20; i++ ){
    vector_int_push_back_v1( &vec,                  i );
    ECE2400_CHECK_INT_EQ( vector_int_at( &vec, i ), i );
    // checks to see that items are only added to back of vector
    ECE2400_CHECK_INT_EQ( vector_int_at( &vec, 0),  10 );
  }

  vector_int_destruct( &vec );
}
//test_case_4_out_of_bounds_at_vector
//------------------------------------------------------------------------
// tests to see if both negative and positive index values that out of bounds return 0
// Author: Alexander Scotte(ajs677)
void test_case_4_out_of_bounds_at_vector()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  vector_int_push_back_v1( &vec, 1);

  //tests for out of bounds
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, 9 ),       0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, 1 ),       0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, 100 ),     0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, INT_MAX ), 0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, -2 ),      0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, -100 ),    0 );
  ECE2400_CHECK_INT_EQ( vector_int_at( &vec, INT_MIN ), 0 );

vector_int_destruct( &vec ) ;
}
//------------------------------------------------------------------------
// test_case_5_simple_contains
//------------------------------------------------------------------------
// Push 2 elements and see if they can still be found.

void test_case_5_simple_contains()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  // Push back some elements
  for ( int i = 0; i < 2; i++ )
    vector_int_push_back_v1( &vec, i );

  // Try finding them
  for ( int i = 0; i < 2; i++ )
    ECE2400_CHECK_TRUE( vector_int_contains( &vec, i ) )

  // Check size
  ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), 2 );

  vector_int_destruct( &vec );
}
//------------------------------------------------------------------------
// test_case_6_large_contains
//------------------------------------------------------------------------
// Tests to see if the contains function can handle a large vector of values
// also tests push_back_v1 to make sure it has added the values to the vector correctly
// Author: Alexander Scotte(ajs667)
void test_case_6_large_contains()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  for( int i = 0; i < 10000; i++ )  {
    vector_int_push_back_v1( &vec, i);
  }
  for( int i = 0; i < 10000; i++ )  {
    ECE2400_CHECK_TRUE(vector_int_contains( &vec, i));
  }
vector_int_destruct( &vec );
  
}

void test_case_7_does_not_contain()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );
  
  //test empty vector
  ECE2400_CHECK_FALSE(vector_int_contains( &vec, 20));
  ECE2400_CHECK_FALSE(vector_int_contains( &vec, INT_MAX));
  ECE2400_CHECK_FALSE(vector_int_contains( &vec, -50));
  ECE2400_CHECK_FALSE(vector_int_contains( &vec, INT_MIN));
  vector_int_destruct( &vec );
}
//------------------------------------------------------------------------
// test_case_8_exact_closest
//------------------------------------------------------------------------
// A test case that tests for numbers in a vector that are the exct value as the input
// Author: Alexander Scotte(ajs667)
void test_case_8_exact_closest()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  for( int i = 0; i < 100; i++ ){
    vector_int_push_back_v1( &vec, i );
  }
  for( int i = 0; i < 100; i++ ){
    ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, i ), i );
  }
  vector_int_destruct( &vec );
}
//------------------------------------------------------------------------
// test_case_9_offset_simple_closest
//------------------------------------------------------------------------
// A test case that tests for numbers in a vector that are the exct value as the input
// Author: Alexander Scotte(ajs667)
void test_case_9_offset_simple_closest()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  for( int i = 0; i < 100; i = i + 3 ){
    vector_int_push_back_v1( &vec, i );
  }
  for( int i = 1; i < 101; i = i + 3 ){
    ECE2400_CHECK_INT_EQ(vector_int_find_closest( &vec, i ), i-1);
  }
  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_10_equidistant_closest
//------------------------------------------------------------------------
// Check if for vector_int_find_closest of a value with two equidistant 
// solutions in the vector, the oner closer to the header is selected.
// Author: Ved Kumar modified by Alexander Scotte(ajs667)

void test_case_10_equidistant_closest()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );

  // Push back elements
  for (int i = 1; i < 4; i++) {
   vector_int_push_back_v1( &vec, -2*i );
   vector_int_push_back_v1( &vec, 2*i ); 
   vector_int_push_back_v1( &vec, 8*i );
  }

  // Check output value is the one closer to the header
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 0 ), -2 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, -5 ), -4 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 1 ), 2 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 5 ), 4 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 7 ), 8 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 12 ), 8 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 20 ), 16 );

  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_11_closest_large
//------------------------------------------------------------------------
// A test case that tests searching for the closest with large numbers,
// Author: Scott Faber modified by Alexander Scotte(ajs667)

void test_case_11_closest_large()
{
  printf( "\n%s\n", __func__ );

  vector_int_t vec;
  vector_int_construct( &vec );
  
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, 0 ), -1 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, INT_MAX ), -1 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, INT_MAX - 16 ), -1 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, -48 ), -1 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, INT_MIN ), -1 );
  ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, INT_MIN + 16 ), -1 );
  
  vector_int_push_back_v1( &vec, -1 );
  vector_int_push_back_v1( &vec, INT_MIN );
  vector_int_push_back_v1( &vec, -42 );
  
  
  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_12_check_push_back_v2_return_size
//------------------------------------------------------------------------
// A test case that tests if the size being occupied by a vector 
// that has used push_back_v2
// Author: Alexander Scotte(ajs667)
void test_case_12_check_push_back_v2_return_size(){
  printf( "\n%s\n", __func__ );


 // create vector
  vector_int_t vec;
  vector_int_construct( &vec );

  for ( int i = 0; i < 20; i++ ){
    vector_int_push_back_v1( &vec, i );
 }
 for(int i = 0; i < 20; i++){
  vector_int_push_back_v2( &vec, 20 );
  //vector_int_push_back_v2(&vec, 31);
 }
  ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), 40);
  
  vector_int_destruct(&vec);
}
//------------------------------------------------------------------------
// test_case_13_check_push_back_v2
//------------------------------------------------------------------------
// A test case that tests push_back_v2 
// Author: Alexander Scotte(ajs667)
void test_case_13_vector_push_back_v2()
{
  printf( "\n%s\n", __func__ );
  vector_int_t vec;
  vector_int_construct(&vec);
  //populates vector with values
  for(int i = 0; i < 1000; i++ ){
    vector_int_push_back_v2( &vec, i );
  }
  for( int i =0; i < 1; i++ ){
    ECE2400_CHECK_INT_EQ( vector_int_at( &vec, i ), i);
  }
  vector_int_push_back_v1( &vec, 100 );

  vector_int_destruct( &vec );
}
//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) )  test_case_1_simple_push_back();
  if ( ( __n <= 0 ) || ( __n == 2 ) )  test_case_2_large_size_vector();
  if ( ( __n <= 0 ) || ( __n == 3 ) )  test_case_3_changing_index_at_vector();
  if ( ( __n <= 0 ) || ( __n == 4 ) )  test_case_4_out_of_bounds_at_vector();
  if ( ( __n <= 0 ) || ( __n == 5 ) )  test_case_5_simple_contains();
  if ( ( __n <= 0 ) || ( __n == 6 ) )  test_case_6_large_contains();
  if ( ( __n <= 0 ) || ( __n == 7 ) )  test_case_7_does_not_contain();
  if ( ( __n <= 0 ) || ( __n == 8 ) )  test_case_8_exact_closest();
  if ( ( __n <= 0 ) || ( __n == 9 ) )  test_case_9_offset_simple_closest();
  if ( ( __n <= 0 ) || ( __n == 10 ) ) test_case_10_equidistant_closest();
  if ( ( __n <= 0 ) || ( __n == 11 ) ) test_case_11_closest_large();
  if ( ( __n <= 0 ) || ( __n == 12 ) ) test_case_12_check_push_back_v2_return_size();
  if ( ( __n <= 0 ) || ( __n == 13 ) ) test_case_13_vector_push_back_v2();

  printf( "\n" );
  return __failed;
}
