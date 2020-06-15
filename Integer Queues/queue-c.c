// Implementation file for queue-c module

// This version is implemented with two stacks

#include "stack.h"
#include "queue-c.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cs136-trace.h"


///////////////////////////////////////
// STRUCTURE
///////////////////////////////////////
struct queue {
  struct stack *a;
  struct stack *b;
};
///////////////////////////////////////


struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->a = stack_create();
  q->b = stack_create();
  return q;
}


bool queue_is_empty(const struct queue *q) {
  assert(q);
  return (stack_is_empty(q->a) && stack_is_empty(q->b));
}


void queue_add_back(int i, struct queue *q) {
  assert(q);
  if (stack_is_empty(q->a)) {
    while (!stack_is_empty(q->b)) {
      stack_push(stack_pop(q->b), q->a);
    }
  }
  stack_push(i, q->a);
}


int queue_remove_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  if (stack_is_empty(q->b)) {
    while (!stack_is_empty(q->a)) {
      stack_push(stack_pop(q->a), q->b);
    }
  }
  return stack_pop(q->b);
}


int queue_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  if (stack_is_empty(q->b)) {
    while (!stack_is_empty(q->a)) {
      stack_push(stack_pop(q->a), q->b);
    }
  }
  return stack_top(q->b);;
}


void queue_destroy(struct queue *q) {
  assert(q);
  stack_destroy(q->a);
  stack_destroy(q->b);
  free(q);
}


int queue_len(struct queue *q) {
  assert(q);
  int len = 0;
  if (stack_is_empty(q->a)) {
    while(!stack_is_empty(q->b)) {
      stack_push(stack_pop(q->b), q->a);
      len++;
    }
  } else if (stack_is_empty(q->b)) {
    while (!stack_is_empty(q->a)) {
      stack_push(stack_pop(q->a), q->b);
      len++;
    }
  }
  return len;
}


void queue_print(struct queue *q) {
  assert(q);
  if (queue_is_empty(q)) {
    printf("[empty]\n");
  } else {
    printf("[");
    int len = queue_len(q);

    if (stack_is_empty(q->b)) {
      // reorder if needed
      while (!stack_is_empty(q->a)) {
        stack_push(stack_pop(q->a), q->b);
      }
    }

    for (int i = 0; i+1 < len; i++){
      int yeet = stack_pop(q->b);
      printf("%d->", yeet);
      stack_push(yeet, q->a);
    }
    int yeet = stack_pop(q->b);
    printf("%d]\n", yeet);
    stack_push(yeet, q->a);
  }
}
