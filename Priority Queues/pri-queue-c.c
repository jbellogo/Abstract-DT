// Implementation file for pri-queue-c module using a MAXHEAP

#include "pri-queue-c.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include <string.h>
#include <stdbool.h>


struct pqnode {
  char *str;
  int priority;
  int id;  /// store in the node whe the len was wen added
};

struct pri_queue {
  struct pqnode *data;   // this is an array of nodes
  int len;
  int maxlen;
};

bool pq_node_empty(struct pqnode pqn) {
  return pqn.str == NULL;
}


struct pri_queue *pri_queue_create(int ignore) {
  struct pri_queue *pq = malloc(sizeof(struct pri_queue));
  pq->len = 0;
  pq->maxlen = 1; // can't initialize data with 0
  pq->data = malloc(pq->maxlen * sizeof(struct pqnode));
  return pq;
}



struct pqnode newnode(char *item, int pri, int id) {
  struct pqnode node = {item, pri, id};
  return node;
};

void swap(struct pqnode *px, struct pqnode *py) {
  struct pqnode temp = *px;
  *px = *py;
  *py = temp;
}


void pri_queue_add(const char *item, int priority, struct pri_queue *pq) {
  assert(item);
  assert(pq);
  if (pq->len == pq->maxlen) {
    (pq->maxlen) *= 2;
    (pq->maxlen)++;
    pq->data = realloc(pq->data, pq->maxlen*
                       sizeof(struct pqnode));
  }
  char *copy = malloc(sizeof(char)*(strlen(item) + 1));
  strcpy(copy, item);
  // place new node at first avaliable loc
  pq->data[pq->len]= newnode(copy, priority, pq->len);

  int inex = pq->len;
  while (pq->data[inex].priority > pq->data[(inex-1)/2].priority) {
    swap((pq->data + inex), (pq->data + (inex-1)/2));
    inex = (inex-1)/2;
  }
  (pq->len)++;
}



char *pri_queue_remove(struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));

  char *backup = pq->data[0].str;

  pq->data[0] = pq->data[pq->len -1]; // the rightmost
  --(pq->len);
  int inex = 0;

  while ((inex*2 + 1 < pq->len)&&
         ((pq->data[inex].priority <= pq->data[inex*2 +1].priority)||
          (pq->data[inex].priority <= pq->data[inex*2 +2].priority))) {
    if (pq->data[inex*2 +1].priority ==
        pq->data[inex*2 +2].priority) {
      if (pq->data[inex*2 +1].id <
          pq->data[inex*2 +2].id) {
        swap((pq->data + inex),
             (pq->data + inex*2 +1));
        inex = inex*2 +1;
      } else {
        swap((pq->data + inex),
             (pq->data + inex*2 +2));
        inex = inex*2+ 2;
      }

    } else {
      if (pq->data[inex*2 +1].priority >
          pq->data[inex*2 +2].priority) {
        swap((pq->data + inex),
             (pq->data + inex*2 +1));
        inex = inex*2 +1;
      } else {
        swap((pq->data + inex),
             (pq->data + inex*2 +2));
        inex = inex*2+ 2;
      }
    }
  }
  return backup;
}



int pri_queue_max(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  return pq->data[0].priority;
}


const char *pri_queue_front(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  const char *yeet = pq->data[0].str;
  return yeet;
}


bool pri_queue_is_empty(const struct pri_queue *pq) {
  assert(pq);
  return (pq->len == 0);
}


void pri_queue_destroy(struct pri_queue *pq) {
  char *a;
  assert(pq);
  for (int i = 0; i < pq->maxlen; i++) {
    if (!pri_queue_is_empty(pq)){
      a = pri_queue_remove(pq);
      free (a);
    }
  }
  free(pq->data);
  free(pq);
}
