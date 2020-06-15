// This is a very simple test for the stack module

#include <assert.h>
#include "stack.h"

int main(void) {
  struct stack *s = stack_create();
  assert(stack_is_empty(s));
  stack_push(42, s);
  assert(stack_top(s) == 42);
  assert(stack_pop(s) == 42);
  assert(stack_is_empty(s));
  stack_push(4, s);
  stack_push(2, s);
  stack_push(7, s);
  stack_push(-9, s);
  assert(stack_top(s) == -9);
  assert(stack_pop(s) == -9);
  assert(stack_pop(s) == 7);
  assert(stack_pop(s) == 2);
  assert(stack_pop(s) == 4);
  assert(stack_is_empty(s));

  stack_destroy(s);
}
