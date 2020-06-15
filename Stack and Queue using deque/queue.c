/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////


#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"


struct queue {
  struct deque *deq;
};


struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->deq = deque_create();
  return q;
}


void queue_destroy(struct queue *q) {
  assert(q);
  deque_destroy(q->deq);
  free(q);
}


bool queue_is_empty(const struct queue *q) {
  assert(q);
  return (deque_is_empty(q->deq));
}

void queue_add_back(int item, struct queue *q) {
  assert(q);
  deque_insert_back(item, q->deq);
}

int queue_front(const struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  return deque_front(q->deq);
}

int queue_remove_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  return deque_remove_front(q->deq);
}
