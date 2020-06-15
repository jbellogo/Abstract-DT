// Implementation file for pri-queue-b module

#include "pri-queue-b.h"

// Implemented as a single linked list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include <string.h>
#include <stdbool.h>


struct pqnode {
  char *item;
  int priority;
  struct pqnode *next;
};

struct pri_queue {
  struct pqnode *front;
};



struct pri_queue *pri_queue_create(int ignore) {
  struct pri_queue *pq = malloc(sizeof(struct pri_queue));
  pq->front = NULL;
  return pq;
}


struct pqnode *newnode(char *str, int pri,struct pqnode * nex) {
  assert(str);
  struct pqnode *node = malloc(sizeof(struct pqnode));
  node->item = str;
  node->priority = pri;
  node->next = nex;
  return node;
}



void pri_queue_add(const char *item, int priority, struct pri_queue *pq) {
  assert(pq);

  char *copy = malloc(sizeof(char)*(strlen(item) + 1));
  strcpy(copy, item);
  struct pqnode *node = newnode(copy, priority, NULL);

  if (pq->front == NULL || priority > pq->front->priority) {
    node->next = pq->front;
    pq->front = node;
    return;
  } else {
    struct pqnode *yeet = pq->front;
    while (yeet->next &&  priority <= yeet->next->priority) {
      yeet = yeet->next;
    }
    node->next = yeet->next;
    yeet->next = node;
  }
}



bool pri_queue_is_empty(const struct pri_queue *pq) {
  assert(pq);
  return ((pq->front) == NULL);
}


char *pri_queue_remove(struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  char *item = malloc((1+strlen(pq->front->item))*sizeof(char));
  strcpy(item, pq->front->item);
  struct pqnode *old = pq->front;
  pq->front = pq->front->next;
  free(old->item);
  free(old);
  return item;
}


void pri_queue_destroy(struct pri_queue *pq) {
  char *a;
  while (pq->front) {
    a = pri_queue_remove(pq);
    free(a);
  }
  free(pq->front);
  free(pq);
}



int pri_queue_max(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  return pq->front->priority;
}


const char *pri_queue_front(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  const char *yeet = pq->front->item;
  return yeet;
}
