/////////////////////////////////////////////////////////////////////////////
// Deque ADT
/////////////////////////////////////////////////////////////////////////////

#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"

///////////////////////////////////////
// STRUCTURE
///////////////////////////////////////
struct llnode {
  int item;
  struct llnode *prev;
  struct llnode *next;
};

struct deque {
  struct llnode *front;
  struct llnode *back;
};
///////////////////////////////////////


struct deque *deque_create(void) {
  struct deque *deq = malloc(sizeof(struct deque));
  deq->front = NULL;
  deq->back = NULL;
  return deq;
}


// time: O(1)
bool deque_is_empty(const struct deque *deq) {
  assert(deq);
  return (deq->front == NULL) ||(deq->back == NULL);
}



// must be freed
struct llnode *new_node(int i, struct llnode *prev,
                        struct llnode *next) {
  struct llnode *node = malloc(sizeof(struct llnode));
  node->item = i;
  node->prev = prev;
  node->next = next;
  return node;  /// this must be freed
}


void deque_insert_front(int item, struct deque *deq){
  assert(deq);
  struct llnode *old_front = deq->front;
  struct llnode *node = new_node(item, NULL, old_front);

  if (deq->front != NULL) {
    old_front->prev = node;
  }
  if (deque_is_empty(deq)) {
    deq->back = node;
  }
  deq->front = node;
}


int deque_front(const struct deque *deq) {
  assert(deq);
  assert(!deque_is_empty(deq));
  return deq->front->item;
}


int deque_len(const struct deque *deq) {
  assert(deq);
  if (deque_is_empty(deq)) return 0;
  int count = 0;
  struct llnode *yeet = deq->front;
  while (yeet) {
    count++;
    yeet = yeet->next;
  }
  return count;
}


int deque_remove_front(struct deque *deq) {
  assert(deq);
  assert(!deque_is_empty(deq));
  int ret = deq->front->item;

  struct llnode *old_front = deq->front;

  deq->front = deq->front->next;
  free(old_front);
  if (deq->front == NULL) {  //remove from deq len =1
    deq->back = NULL;
  } else {
    deq->front->prev = NULL;
  }
  return ret;
}


void deque_destroy(struct deque *deq) {
  assert(deq);
  if (deque_is_empty(deq)) {
    free(deq->front);
    free(deq->back);
    free(deq);
  } else {
    struct llnode *yeet = deq->front;
    while (yeet) {
      free(yeet->prev);
      yeet = yeet->next;
    }
    free(deq->back);
    free(deq);
  }
}



void deque_insert_back(int item, struct deque *deq) {
  assert(deq);
  struct llnode *node = new_node(item, deq->back, NULL);
  if (deque_is_empty(deq)) {
    deq->front = node;
    deq->back = node;
  } else {
    deq->back->next = node;
    deq->back = node;
  }
}


int deque_back(const struct deque *deq) {
  assert(deq);
  assert(!deque_is_empty(deq));
  return deq->back->item;
}


int deque_remove_back(struct deque *deq) {
  assert(deq);
  assert(!deque_is_empty(deq));
  int ret = deq->back->item;
  struct llnode *old_back = deq->back;
  deq->back = deq->back->prev;
  free(old_back);
  if (deq->back == NULL) {
    deq->front = NULL;
  } else {
    deq->back->next = NULL;
  }
  if (deq->front == NULL) {  //remove from deq len =1
    deq->back = NULL;
  }
  return ret;
}



void deque_print(const struct deque *deq) {
  assert(deq);
  if (deque_is_empty(deq)) {
    printf("[empty]\n");
  } else if (!(deq->front->next)) {
    printf("[%d]\n", deq->front->item);
  } else {
    struct llnode *trav = deq->front;
    printf("[");
    while (trav->next) {   /// hmm pls work
      printf("%d,", trav->item);
      trav = trav->next;
    }
    printf("%d]\n", trav->item);
  }
}


void deque_print_reverse(const struct deque *deq) {
  assert(deq);
  if (deque_is_empty(deq)) {
    printf("[empty]\n");
  } else if (!deq->front->next) {
    printf("[%d]\n", deq->front->item);
  } else {

    struct llnode *trav = deq->back; // no need to free
    printf("[");
    while (trav->prev) {   /// hmm pls work
      printf("%d,", trav->item);
      trav = trav->prev;
    }
    printf("%d]\n", trav->item);
  }
}
