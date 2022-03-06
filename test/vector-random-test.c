//========================================================================
// vector-random-test.c
//========================================================================
// This file contains contains random tests for vector-related functions.

#include "vector.h"
#include "ece2400-stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

//------------------------------------------------------------------------
// test_case_1_push_back_v2
//------------------------------------------------------------------------
// This test case tests teh functionality of push_back_v2 by testing random inputs

void test_case_1_push_back_v2()
{
  printf( "\n%s\n", __func__ );
  srand( 0xdeadbeef ); // random seed
  vector_int_t vec;
  vector_int_construct(&vec);
  int random;
  int container[100];
  //populates compare array and vector with same values
  for(int i = 0; i < 100; i++ ){
    random = ( rand() % 1000 ) + 1;
    container[i] = random;
    vector_int_push_back_v2(&vec, random);
  }
  //checks to see that they have the same values in the same order
  for( int i =0; i < 100; i++ ){
    ECE2400_CHECK_INT_EQ( vector_int_at( &vec, i ), container[i] );
  }
  vector_int_destruct(&vec);
}
//------------------------------------------------------------------------
// test_case_2_random_size_random_values
//------------------------------------------------------------------------
// A test case that pushes onto the vector a random value (-RAND_MAX/2 to RAND_MAX/2)
// N times (N is randomly chosen, 1 to 1000). It then picks 5 random locations
// in the vector and makes sure they have the correct value.
// Author: Daniel Buscaglia

void test_case_2_random_size_random_values()
{
  printf( "\n%s\n", __func__ );
  srand( 0xdeadbeef ); // random seed
  vector_int_t vec;

  for (size_t j = 0; j < 50; ++j ) {
    vector_int_construct( &vec );
    // Generate a random size (1 <= random_size <= 1000) and the random values
    size_t random_size = ( rand() % 1000 ) + 1;
    int* values = (int*) ece2400_malloc( random_size * sizeof( int ) );
    for ( size_t i = 0; i < random_size; ++i ) {
      values[i] = rand() - ( RAND_MAX / 2 ); // -RAND_MAX / 2 <= values[i] <= RAND_MAX / 2
    }

    // Push all values into vectir
    for ( size_t i = 0; i < random_size; ++i ) {
      vector_int_push_back_v1( &vec, values[i] );
    }

    ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), random_size ); 
    // Check 5 random values in vector
    for ( size_t i = 0; i < 5; ++i ) {
      size_t check_loc = rand() % random_size;
      ECE2400_CHECK_INT_EQ( vector_int_at( &vec, check_loc ), values[check_loc] );
    }

    ece2400_free( values );
    vector_int_destruct( &vec );
  }
}
//------------------------------------------------------------------------
// test_case_3_random_size_generator
//------------------------------------------------------------------------
// A test case that creates a vector with a random size 10 times
// Author: Alexander Scotte
void test_case_3_random_size_generator()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );

  vector_int_t vec;

  size_t random_size;
  // how many times random vector will be generated
  for( int i = 0; i < 10; i++ ){
    vector_int_construct( &vec );
    //generates size from 1 - 1000
    random_size = ( rand() % 1000 ) + 1;
    //generates random vector
    for(size_t c = 0; c < random_size; c++ ){
      vector_int_push_back_v1( &vec, c );
    }
    ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), random_size );
    vector_int_destruct( &vec );
  }
}

//------------------------------------------------------------------------
// test_case_4_random_test
//------------------------------------------------------------------------
// This test test push back, contain, size with random size(1-500) and value
// do 20 tests, check closest value with itself (tricky method)
//Author: Jingwen Ye
void test_case_4_random_test()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );
  vector_int_t vec;
  int iter = 20;

  for (int t = 0; t < iter; t++)
  {
    vector_int_construct( &vec );
    size_t sz = rand() % 500 + 1;
    int* array = (int*)malloc(sz * sizeof(int));

    // build an array, store value in range [-RAND_MAX, RAND_MAX]
    for (size_t i = 0; i < sz; i++)
      array[i] = rand() - RAND_MAX/2;

    // push back array values to vector
    for (size_t i = 0; i < sz; i++)
      vector_int_push_back_v1( &vec, array[i] );
    
    // check array
    for (size_t i = 0; i < sz; i++)
    {
      ECE2400_CHECK_TRUE( vector_int_contains( &vec, array[i]) );
      ECE2400_CHECK_INT_EQ( vector_int_at  ( &vec, i ), array[i] );
    }
      
    
    // Check size
    ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), sz );

    // Check closest value
    for (size_t i = 0; i < sz; i++)
      ECE2400_CHECK_INT_EQ( vector_int_find_closest( &vec, array[i]), array[i]);

    vector_int_destruct( &vec );
    free(array);
  }
  
}
//------------------------------------------------------------------------
// test_case_5_small_push_back
//------------------------------------------------------------------------
// A test which creates a vector and checks that the vector correctly pushes
// back random integers.
// Author: Christopher Bakhos (cmb524)

void test_case_5_small_push_back()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );
  
  int vector_size = 5;
  int x_lower_bound = -100;  // inclusive
  int x_upper_bound =  100;  // inclusive
  int x_range = x_upper_bound - x_lower_bound + 1;
  int x;
  
  vector_int_t vec;
  vector_int_construct( &vec );
  
  for( int i = 0; i < vector_size; i++ ) {
    x = ( rand() % x_range ) + x_lower_bound;
    vector_int_push_back_v1( &vec, x );
    ECE2400_CHECK_INT_EQ( vector_int_at( &vec, i ),      x );
  }
  ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), vector_size );

  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_6_random_contains_vector
//------------------------------------------------------------------------
// Simple random test case for vector contains
// Set variables for the number of tests as well as maximum random value to store
// Random elements will be generated, then tested with the contains function
// Author: Erik Ossner modified by Alexander Scotte

void test_case_6_random_contains_vector()
{
  printf( "\n%s\n", __func__ );
  srand( 0xDeadFa11 );

  vector_int_t vec;
  vector_int_construct( &vec );

  const int num_tests = 100;
  const int max_x = 100;
  int inputs[100];

  for ( int i = 0; i < num_tests; i++ ){
    inputs[i] = ( (float)rand() / (float)RAND_MAX ) * max_x;
    vector_int_push_back_v1( &vec, inputs[i] );
  }


  // Try finding them
  for ( int i = 0; i < num_tests; i++ )
    ECE2400_CHECK_TRUE( vector_int_contains( &vec, inputs[i] ) )

  // Check size
  ECE2400_CHECK_INT_EQ( vector_int_size( &vec ), num_tests );

  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// test_case_7_vector_closest_random
//------------------------------------------------------------------------
// Random case that tests find_closest by comparing it to ana array of the same random values
// Author: Alexander Scotte(ajs667)

void test_case_7_vector_closest_random()
{
  printf( "\n%s\n", __func__ );
  srand( 0xDeadFa11 );

  vector_int_t vec;
  vector_int_construct( &vec );

  int compare[100];
  int random_inputs; 

  // fills vector and compare array
  for( int i = 0; i < 100; i ++ )
  {
    random_inputs = ( rand() % 1000 ) + 1;
    compare[i] = random_inputs;
    vector_int_push_back_v1(&vec, random_inputs);
  }
  //does test 100 times
  for(int c = 0; c < 100; c++){
  // assigns random value to be used throughout test
    int random_value = ( rand() % 1000 ) + 1;
    int difference =  abs( compare[0] - random_value );
    int answer = compare[0];
    //finds the closest value 
    for( size_t i =0; i < 100; i++ ){
      int next_answer = abs(compare[i] - random_value);
      if( next_answer < difference){
        difference = next_answer;
        answer = compare[i]; 
      }
    }
    ECE2400_CHECK_INT_EQ(vector_int_find_closest( &vec , random_value ), answer );
  }
  vector_int_destruct( &vec );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) ) test_case_1_push_back_v2();
  if ( ( __n <= 0 ) || ( __n == 2 ) ) test_case_2_random_size_random_values();
  if ( ( __n <= 0 ) || ( __n == 3 ) ) test_case_3_random_size_generator();
  if ( ( __n <= 0 ) || ( __n == 4 ) ) test_case_4_random_test();
  if ( ( __n <= 0 ) || ( __n == 5 ) ) test_case_5_small_push_back();
  if ( ( __n <= 0 ) || ( __n == 6 ) ) test_case_6_random_contains_vector();
  if ( ( __n <= 0 ) || ( __n == 7 ) ) test_case_7_vector_closest_random();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  printf( "\n" );
  return __failed;
}
