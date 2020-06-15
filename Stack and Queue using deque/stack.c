/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"



struct stack {
  struct deque *deq;
};


struct stack *stack_create(void) {
  struct stack *s = malloc(sizeof(struct stack));
  s->deq = deque_create();
  return s;
}


void stack_destroy(struct stack *s) {
  assert(s);
  deque_destroy(s->deq);
  free(s);
}

bool stack_is_empty(const struct stack *s) {
  assert(s);
  return (deque_is_empty(s->deq));
}

void stack_push(int item, struct stack *s) {
  assert(s);
  deque_insert_back(item, s->deq);
}

int stack_top(const struct stack *s) {
  assert(s);
  assert(!stack_is_empty(s));
  return deque_back(s->deq);
}

int stack_pop(struct stack *s) {
  assert(s);
  assert(!stack_is_empty(s));
  return deque_remove_back(s->deq);
}
