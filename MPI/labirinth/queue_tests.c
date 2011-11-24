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
  {
    /*#Test_0*/
    queue q; q_init(&q, s);
    test(q_size(&q) == 0 && q_is_empty(&q));
  }
  {
    /*#Test_1*/
    queue q; q_init(&q, s);
    q_push(&q, (void *)1);
    test(q_size(&q) == 1 && !q_is_empty(&q));
  }
  {
    /*#Test_2*/
    queue q; q_init(&q, s);
    q_push(&q, (void *)2);
    q_push(&q, (void *)1);
    test(
        q_size(&q) == 2 && 
        q_front(&q) == (void *)1 && 
        q_back(&q) == (void *)2);
  }
  {
    /*#Test_3*/
    queue q; q_init(&q, s);
    q_push(&q, (void *)3);
    q_push(&q, (void *)2);
    q_push(&q, (void *)1);

    q_pop(&q);
    BOOL foo = q_front(&q) == (void *)1 && q_back(&q) == (void *)2;

    q_pop(&q);
    BOOL bar = q_front(&q) == (void *)1 && q_back(&q) == (void *)1;

    q_pop(&q);
    test(
        foo &&
        bar &&
        q_is_empty(&q));
  }
  {
    /*#Test_4*/
    queue q; q_init(&q, s);
    BOOL foo = TRUE;

    for (uint i = 0; i < N; ++i)
      q_push(&q, (void *)i);

    for (uint i = 0; i < N; ++i)
    {
      foo &= q_back(&q) == (void *)i;
      if (!foo) break;
      q_pop(&q);
    }

    test(
        foo &
        q_is_empty(&q));
  }

  return EXIT_SUCCESS;
}

