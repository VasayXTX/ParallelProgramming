/*
 * Data structures
 * Implementation of queue
 * File: queue.h
 * Author: Vasily Tsybenko
 * Date: 2011-11-24
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

void q_init(queue *q, size_t size_el)
{
  q->size = 0;
  q->size_el = size_el;
  q->head = q->tail = NULL;
}

size_t q_size(queue *q)
{
  return q->size;
}

size_t q_size_el(queue *q)
{
  return q->size_el;
}

BOOL q_is_empty(queue *q)
{
  if (!q->size) return TRUE;
  else return FALSE;
}

void q_push(queue *q, void *data)
{
  node *foo = (node *)malloc(sizeof(q->size_el));
  if (q->head == NULL)
  {
    q->head = q->tail = foo;
    foo->next = foo->prev = NULL;
  }
  else
  {
    foo->next = q->head;
    foo->prev = NULL;
    q->head = q->head->prev = foo;
  }
  foo->data = (void *)malloc(sizeof(q->size_el));
  memcpy(foo->data, data, q->size_el);
  ++q->size;
}

void q_pop(queue *q)
{
  if (q->head == NULL)
  {
    fprintf(stderr, "Queue is empty!");
    return;
  }
  if (q->head == q->tail) q->head = NULL;
  else q->tail->prev->next = NULL;
  node *foo = q->tail;
  q->tail = q->tail->prev;
  free(foo->data);
  free(foo);
  --q->size;
}

void *q_front(queue *q)
{
  return q->head->data;
}

void *q_back(queue *q)
{
  return q->tail->data;
}

