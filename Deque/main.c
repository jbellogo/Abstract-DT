// Test client


#include <assert.h>
#include "deque.h"
#include "cs136-trace.h"


int deque_len(const struct deque *deq);

int main(void) {
  struct deque *deq = deque_create();
  deque_print_reverse(deq); /* [empty] */
  deque_print(deq);
  deque_insert_front(1, deq);
  assert(deque_front(deq) == 1);
  assert(deque_back(deq) == 1);

  deque_insert_front(9, deq);
  deque_insert_back(9, deq);
  deque_insert_back(3, deq);
  deque_print(deq);
  deque_print_reverse(deq);

  assert(deque_front(deq) == 9);
  assert(deque_back(deq) == 3);

  assert(deque_remove_front(deq) == 9);
  deque_print(deq);
  deque_print_reverse(deq);

  assert(deque_remove_back(deq) == 3);
  deque_print(deq);
  deque_print_reverse(deq);
  assert(deque_remove_back(deq) == 9);
  deque_print(deq);
  deque_print_reverse(deq);
  assert(deque_back(deq) == deque_front(deq));

  deque_remove_back(deq);




  deque_destroy(deq);
}
