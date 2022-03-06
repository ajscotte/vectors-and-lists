//========================================================================
// list-random-test.c
//========================================================================
// This file contains the tests with randomly generated inputs

#include "list.h"
#include "ece2400-stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

//------------------------------------------------------------------------
// test_case_1_random_size_random_values
//------------------------------------------------------------------------
// A test case that pushes onto the list a random value (-RAND_MAX/2 to RAND_MAX/2)
// N times (N is randomly chosen, 1 to 1000). It then picks 5 random locations
// in the list and makes sure they have the correct value.
// Author: Daniel Buscaglia

void test_case_1_random_size_random_values()
{
  printf( "\n%s\n", __func__ );
  srand( 0xdeadbeef ); // random seed
  list_int_t lst;

  for (size_t j = 0; j < 50; ++j ) {
    list_int_construct( &lst );
    // Generate a random size (1 <= random_size <= 1000) and the random values
    size_t random_size = ( rand() % 1000 ) + 1;
    int* values = (int*) ece2400_malloc( random_size * sizeof( int ) );
    for ( size_t i = 0; i < random_size; ++i ) {
      values[i] = rand() - ( RAND_MAX / 2 ); // -RAND_MAX / 2 <= values[i] <= RAND_MAX / 2
    }

    // Push all values into list
    for ( size_t i = 0; i < random_size; ++i ) {
      list_int_push_back( &lst, values[i] );
    }

    ECE2400_CHECK_INT_EQ( list_int_size( &lst ), random_size ); 
    // Check 5 random values in list
    for ( size_t i = 0; i < 5; ++i ) {
      size_t check_loc = rand() % random_size;
      ECE2400_CHECK_INT_EQ( list_int_at( &lst, check_loc ), values[check_loc] );
    }

    ece2400_free( values );
    list_int_destruct( &lst );
  }
}
//------------------------------------------------------------------------
// test_case_2_random_size_generator
//------------------------------------------------------------------------
// A test case that creates a list with a random size 10 times
// Author: Alexander Scotte
void test_case_2_random_size_generator()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );

  list_int_t lst;

  size_t random_size;
  // how many times random list will be generated
  for( int i = 0; i < 10; i++ ){
    list_int_construct( &lst );
    //generates size from 1 - 1000
    random_size = ( rand() % 1000 ) + 1;
    //generates random list
    for(size_t c = 0; c < random_size; c++ ){
      list_int_push_back( &lst, c );
    }
    ECE2400_CHECK_INT_EQ( list_int_size( &lst ), random_size );
    list_int_destruct( &lst );
  }
}

//------------------------------------------------------------------------
// test_case_3_random_test
//------------------------------------------------------------------------
// This test test push back, contain, size with random size(1-500) and value
// do 20 tests, check closest value with itself (tricky method)
//Author: Jingwen Ye
void test_case_3_random_test()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );
  list_int_t lst;
  int iter = 20;

  for (int t = 0; t < iter; t++)
  {
    list_int_construct( &lst );
    size_t sz = rand() % 500 + 1;
    int* array = (int*)malloc(sz * sizeof(int));

    // build an array, store value in range [-RAND_MAX, RAND_MAX]
    for (size_t i = 0; i < sz; i++)
      array[i] = rand() - RAND_MAX/2;

    // push back array values to list
    for (size_t i = 0; i < sz; i++)
      list_int_push_back( &lst, array[i] );
    
    // check array
    for (size_t i = 0; i < sz; i++)
    {
      ECE2400_CHECK_TRUE( list_int_contains( &lst, array[i]) );
      ECE2400_CHECK_INT_EQ( list_int_at  ( &lst, i ), array[i] );
    }
      
    
    // Check size
    ECE2400_CHECK_INT_EQ( list_int_size( &lst ), sz );

    // Check closest value
    for (size_t i = 0; i < sz; i++)
      ECE2400_CHECK_INT_EQ( list_int_find_closest( &lst, array[i]), array[i]);

    list_int_destruct( &lst );
    free(array);
  }
  
}
//------------------------------------------------------------------------
// test_case_4_small_push_back
//------------------------------------------------------------------------
// A test which creates a list and checks that the list correctly pushes
// back random integers.
// Author: Christopher Bakhos (cmb524)

void test_case_4_small_push_back()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8badF00D );
  
  int list_size = 5;
  int x_lower_bound = -100;  // inclusive
  int x_upper_bound =  100;  // inclusive
  int x_range = x_upper_bound - x_lower_bound + 1;
  int x;
  
  list_int_t list;
  list_int_construct( &list );
  
  for( int i = 0; i < list_size; i++ ) {
    x = ( rand() % x_range ) + x_lower_bound;
    list_int_push_back( &list, x );
    ECE2400_CHECK_INT_EQ( list_int_at( &list, i ),      x );
  }
  ECE2400_CHECK_INT_EQ( list_int_size( &list ), list_size );

  list_int_destruct( &list );
}

//------------------------------------------------------------------------
// test_case_5_random_contains_list
//------------------------------------------------------------------------
// Simple random test case for vector contains
// Set variables for the number of tests as well as maximum random value to store
// Random elements will be generated, then tested with the contains function
// Author: Erik Ossner modified by Alexander Scotte

void test_case_5_random_contains_list()
{
  printf( "\n%s\n", __func__ );
  srand( 0xDeadFa11 );

  list_int_t lst;
  list_int_construct( &lst );

  const int num_tests = 100;
  const int max_x = 100;
  int inputs[100];

  for ( int i = 0; i < num_tests; i++ ){
    inputs[i] = ( (float)rand() / (float)RAND_MAX ) * max_x;
    list_int_push_back( &lst, inputs[i] );
  }


  // Try finding them
  for ( int i = 0; i < num_tests; i++ )
    ECE2400_CHECK_TRUE( list_int_contains( &lst, inputs[i] ) )

  // Check size
  ECE2400_CHECK_INT_EQ( list_int_size( &lst ), num_tests );

  list_int_destruct( &lst );
}

//------------------------------------------------------------------------
// test_case_6_list_closest_random
//------------------------------------------------------------------------
// Random case that tests find_closest by comparing it to ana array of the same random values
// Author: Alexander Scotte(ajs667)

void test_case_6_list_closest_random()
{
  printf( "\n%s\n", __func__ );
  srand( 0xDeadFa11 );

  list_int_t lst;
  list_int_construct( &lst );

  int compare[100];
  int random_inputs; 

  // fills list and compare array
  for( int i = 0; i < 100; i ++ )
  {
    random_inputs = ( rand() % 1000 ) + 1;
    compare[i] = random_inputs;
    list_int_push_back(&lst, random_inputs);
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
    ECE2400_CHECK_INT_EQ(list_int_find_closest( &lst , random_value ), answer );
  }
  list_int_destruct(&lst);
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) ) test_case_1_random_size_random_values();
  if ( ( __n <= 0 ) || ( __n == 2 ) ) test_case_2_random_size_generator();
  if ( ( __n <= 0 ) || ( __n == 3 ) ) test_case_3_random_test();
  if ( ( __n <= 0 ) || ( __n == 4 ) ) test_case_4_small_push_back();
  if ( ( __n <= 0 ) || ( __n == 5 ) ) test_case_5_random_contains_list();
  if ( ( __n <= 0 ) || ( __n == 6 ) ) test_case_6_list_closest_random();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  printf( "\n" );
  return __failed;
}
