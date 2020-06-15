// Implementation file for queue-a module

// This version is implemented in a traditional array
// where the front of queue is always in index 0 (q->data[0])

#include "queue-a.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

///////////////////////////////////////
// STRUCTURE
///////////////////////////////////////
struct queue {
  int *data;
  int len;
  int maxlen;
};
///////////////////////////////////////

struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->len = 0;
  q->maxlen =1;
  q->data = malloc(q->maxlen * (sizeof(int)));
  return q;
}


void queue_add_back(int i, struct queue *q) {
  assert(q);
  if (q->len == q->maxlen) {
    q->maxlen *= 2;
    q->data = realloc(q->data, q->maxlen * sizeof(int));
  }
  q->data[q->len] = i;
  ++(q->len);
}

int queue_remove_front(struct queue *q) {
  assert(q); // this should cover empty/no front
  int first = q->data[0];
  for (int i = 0; i +1 < (q->len); i++) {
    q->data[i] = q->data[i+1];
  }
  (q->len)--;
  if ((q->len)*4 == q->maxlen) {
    q->maxlen /= 2;
  }
  return first;
}

int queue_front(const struct queue *q) {
  assert(q);
  return *(q->data);
}

bool queue_is_empty(const struct queue *q) {
  assert(q);
  return (q->len == 0);
}

void queue_destroy(struct queue *q) {
  free(q->data);
  free(q);
}

void queue_print(const struct queue *q) {
  assert(q);
  if (queue_is_empty(q)) {
    printf("[empty]\n");
  } else if (q->len == 1) {
    printf("[%d]\n", q->data[0]);
  } else {
    printf("[");
    for (int i = 0; i < q->len-1; i++) {
      printf("%d->", q->data[i]);
    }
    printf("%d]\n", q->data[q->len-1]);
  }
}
