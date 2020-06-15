// Implementation file for queue-b module

// This version is implemented in a circular array

#include "queue-b.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cs136-trace.h>

///////////////////////////////////////
// STRUCTURE
///////////////////////////////////////
struct queue {
  int *data;
  int front;     // the index of the front item
  int len;
  int maxlen;
};
///////////////////////////////////////


struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->front = 0;
  q->len = 0;
  q->maxlen = 1;
  q->data = malloc(q->maxlen * sizeof(int));
  return q;
}


void queue_add_back(int i, struct queue *q) {
  assert(q);
  if (q->len == q->maxlen) {  // resize => reorder
    //make copy of array
   int *m = malloc(q->len * sizeof(int));
  for (int i = 0; i < q->len; i++) {
      m[i] = q->data[i];  /// duplicate
    }
    for (int i = 0; i < q->len; i++) {
      int index= ((q->front +i)% q->maxlen);
      q->data[i] = m[index];
    }
    free(m);
    q->maxlen *= 2;
    q->data = realloc(q->data, q->maxlen*sizeof(int));
    q->data[q->len] = i;
    q->front = 0;//// COMEON!!!
  } else {
    int index = ((q->front + q->len)% q->maxlen);
    q->data[index] = i;
  }
  (q->len)++;
}


int queue_remove_front(struct queue *q) {
  assert(q);
  assert(q->data);
  const int first = q->data[q->front];
  q->front = (q->front +1) % q->maxlen;
  --(q->len);// has to go here
  if ((q->len)*4 == q->maxlen) { //resize => reorder
    //q->maxlen /= 2;
    // put them at the beginning first
    int *m = malloc(q->len * sizeof(int));
    trace_int(q->len);
    for (int i = 0; i < q->len; i++) {
      m[i] = q->data[(q->front + i) % q->maxlen];
      trace_int(m[i]);
    }
    for (int i = 0; i < q->len; i++) {
      q->data[i] = m[i];
      trace_int(q->data[i]);
    }
    free(m);
    q->front = 0; // update this shit
    // then cut it by half
    q->maxlen /= 2;
  }
  return first;
}


int queue_front(const struct queue *q) {
  assert(q);
  assert(q->data);
  return q->data[q->front];
}


bool queue_is_empty(const struct queue *q) {
  assert(q);
  return(q->len == 0);
}


void queue_destroy(struct queue *q) {
  free(q->data);
  free(q);
}

void queue_print(const struct queue *q) {
  if (queue_is_empty(q)) {
    printf("[empty]\n");
  } else if (q->len == 1) {
    printf("[%d]\n", q->data[q->front]);
  } else {
    printf("[");
    for (int i = 0; i < q->len-1; i++) {
      printf("%d->", q->data[(q->front + i) % q->maxlen]);
    }
    printf("%d]\n", q->data[(q->front + q->len -1)%q->maxlen]);
  }
}
