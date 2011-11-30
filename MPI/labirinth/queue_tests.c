/*
 * Data structures
 * Testing of queue
 * File: queue_tests.c
 * Author: Vasily Tsybenko
 * Date: 2011-11-24
 */

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#define N 100

typedef unsigned int uint;

uint counter;

void test(BOOL cond)
{
  if (cond == TRUE)
    printf("TEST%d - OK\n", counter);
  else
    printf("TEST%d - ERROR\n", counter);
  ++counter;
}

int main(int argc, char *argv[])
{
  size_t s = sizeof(int);
  int foo;
  {
    /*#Test_0*/
    queue q; q_init(&q, s);
    test(q_size(&q) == 0 && q_is_empty(&q));
  }
  {
    /*#Test_1*/
    queue q; q_init(&q, s);
    foo = 1; q_push(&q, &foo);
    test(q_size(&q) == 1 && !q_is_empty(&q) && *(int *)q_front(&q) == 1);
  }
  {
    /*#Test_2*/
    queue q; q_init(&q, s);
    foo = 2; q_push(&q, &foo);
    foo = 1; q_push(&q, &foo);
    test(
        q_size(&q) == 2 && 
        *(int *)q_front(&q) == 1 && 
        *(int *)q_back(&q) == 2);
  }
  {
    /*#Test_3*/
    queue q; q_init(&q, s);

    foo = 3; q_push(&q, &foo);
    foo = 2; q_push(&q, &foo);
    foo = 1; q_push(&q, &foo);

    q_pop(&q);
    BOOL bar = *(int *)q_front(&q) == 1 && *(int *)q_back(&q) == 2;

    q_pop(&q);
    bar &= *(int *)q_front(&q) == 1 && *(int *)q_back(&q) == 1;

    q_pop(&q);
    test(
        bar &&
        q_is_empty(&q));
  }
  {
    /*#Test_4*/
    queue q; q_init(&q, s);
    BOOL bar = TRUE;

    for (uint i = 0; i < N; ++i)
    {
      foo = i; q_push(&q, &foo);
    }

    for (uint i = 0; i < N; ++i)
    {
      bar &= *(int *)q_back(&q) == i;
      if (!bar) break;
      q_pop(&q);
    }

    test(
        bar&
        q_is_empty(&q));
  }

  return EXIT_SUCCESS;
}

