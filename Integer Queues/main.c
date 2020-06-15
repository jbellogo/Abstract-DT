// This is an I/O test client to test the queue-a queue-b and queue-c modules
//  Can choose which module to test below

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include "stack.h"

// IMPORTANT: UNCOMMENT ONE (AND ONLY ONE) of the following #includes
//            (the implementation you want to test)

// #include "queue-a.h"
 #include "queue-b.h"
// #include "queue-c.h"


int main(void) {
  const int ADD_BACK = lookup_symbol("add");
  const int REMOVE_FRONT = lookup_symbol("remove");
  const int FRONT = lookup_symbol("front");
  const int IS_EMPTY = lookup_symbol("is_empty");
  const int PRINT = lookup_symbol("print");

  struct queue *q = queue_create();
  int i = 0;

  while (1) {
    int cmd = read_symbol();
    if (cmd == ADD_BACK) {
      if (scanf("%d", &i) != 1) {
        break;
      }
      queue_add_back(i, q);
    } else if (cmd == REMOVE_FRONT) {
      printf("%d\n", queue_remove_front(q));
    } else if (cmd == FRONT) {
      printf("%d\n", queue_front(q));
    } else if (cmd == IS_EMPTY) {
      if (!queue_is_empty(q)) {
        printf("not ");
      }
      printf("empty\n");
    } else if (cmd == PRINT) {
      queue_print(q);
    } else {
      break;
    }
  }
  queue_destroy(q);
}
