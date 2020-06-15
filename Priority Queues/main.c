// This is an I/O test client to test the modules:
//   pri-queue-a pri-queue-b and pri-queue-c
// You can choose which module to test below

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include "readstr.h"
#include "squeue.h"

// IMPORTANT: UNCOMMENT THE MODULE YOU WANT TO TEST

#include "pri-queue-a.h"
//#include "pri-queue-b.h"
//#include "pri-queue-c.h"

int main(void) {
  const int ADD = lookup_symbol("add");
  const int REMOVE = lookup_symbol("remove");
  const int FRONT = lookup_symbol("front");
  const int IS_EMPTY = lookup_symbol("is_empty");
  
  // for pri-queue-a, there are 100 levels (0...99)
  // for pri-queue-b and pri-queue-c this is ignored
  struct pri_queue *pq = pri_queue_create(100);
  int priority = 0;
  
  while (1) {
    int cmd = read_symbol();
    if (cmd == ADD) {
      char *to_add = readstr();
      if (to_add == NULL) {
        break;
      }
      if (scanf("%d", &priority) != 1) {
        free(to_add);
        break;
      }
      pri_queue_add(to_add, priority, pq);
      free(to_add);
    } else if (cmd == REMOVE) {
      char *removed = pri_queue_remove(pq);
      printf("%s\n", removed);
      free(removed);
    } else if (cmd == FRONT) {
      printf("%s (%d)\n", pri_queue_front(pq), pri_queue_max(pq));
    } else if (cmd == IS_EMPTY) {
      if (!pri_queue_is_empty(pq)) {
        printf("not ");
      }
      printf("empty\n");
    } else {
      break;
    }
  }
  pri_queue_destroy(pq);
}
