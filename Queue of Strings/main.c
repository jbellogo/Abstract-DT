// This is an I/O test client to test the squeue module

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include "readstr.h"

#include "squeue.h"

int main(void) {
  const int ADD_BACK = lookup_symbol("add");
  const int REMOVE_FRONT = lookup_symbol("remove");
  const int FRONT = lookup_symbol("front");
  const int IS_EMPTY = lookup_symbol("is_empty");
  const int PRINT = lookup_symbol("print");
  
  struct squeue *sq = squeue_create();
  
  while (1) {
    int cmd = read_symbol();
    if (cmd == ADD_BACK) {
      char *to_add = readstr();
      if (to_add == NULL) {
        break;
      }      
      squeue_add_back(to_add, sq);
      free(to_add);
    } else if (cmd == REMOVE_FRONT) {
      char *removed = squeue_remove_front(sq);
      printf("%s\n", removed);
      free(removed);
    } else if (cmd == FRONT) {
      printf("%s\n", squeue_front(sq));
    } else if (cmd == IS_EMPTY) {
      if (!squeue_is_empty(sq)) {
        printf("not ");
      }
      printf("empty\n");
    } else if (cmd == PRINT) {
      squeue_print(sq);
    } else {
      break;
    }
  }
  squeue_destroy(sq);
}
