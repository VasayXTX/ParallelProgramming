/*
 * Data structures
 * Implementation of queue
 * File: queue.h
 * Author: Vasily Tsybenko
 * Date: 2011-11-24
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "bool.h"

typedef struct _node {
  struct _node *next, *prev;
  void *data;
} node;

typedef struct {
  size_t size, size_el;
  node *head, *tail;
} queue;

void q_init(queue *, size_t);

size_t q_size(queue *);
size_t q_size_elem(queue *);

BOOL q_is_empty(queue *);

void q_push(queue *, void *);
void q_pop(queue *);

void *q_front(queue *);
void *q_back(queue *);

#endif
