// This is a very simple test for queue module

#include <assert.h>
#include "queue.h"

int main(void) {
  struct queue *q = queue_create();
  queue_add_back(42, q);
  assert(queue_front(q) == 42);
  assert(queue_remove_front(q) == 42);
  assert(queue_is_empty(q));
  queue_add_back(42, q);
  queue_add_back(0, q);
  queue_add_back(-3, q);
  assert(!queue_is_empty(q));
  assert(queue_remove_front(q) == 42);
  assert(queue_front(q) == 0);
  assert(queue_remove_front(q) == 0);
  assert(queue_remove_front(q) == -3);

  queue_destroy(q);
}
