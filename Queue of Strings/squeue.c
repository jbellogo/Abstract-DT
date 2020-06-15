/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// This is a module that provides a queue of strings [squeue] ADT
// where each string is dynamically allocated (copied) when pushed

// times: n is the length of the queue (number of items)
//        m is the length of the string (parameter)
//        k is the combined length of all strings in the queue


#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cs136-trace.h"
#include <assert.h>

struct llnode {
  char *string;
  struct llnode *next;
};

struct squeue {
  struct llnode *front;
  struct llnode *back;
};


// helper: creates a new node.
// effects: allocates memory (caller must free)
struct llnode *new_node(char *str, struct llnode *pnext) {
  assert(str);
  struct llnode *node = malloc(sizeof(struct llnode));
  node->string = str;
  node->next = pnext;
  return node;
}


struct squeue *squeue_create(void) {
  struct squeue *q = malloc(sizeof(struct squeue));
  q->front = NULL;
  q->back = NULL;
  return q;
}

void squeue_add_back(const char *str, struct squeue *sq) {
  assert(str);
  char *yeet = malloc(sizeof(char)*(1+ strlen(str)));
  strcpy(yeet, str);
  struct llnode *node = new_node(yeet, NULL);
  if (!sq->front) {
    sq->front = node;
  } else {
    sq->back->next = node;
  }
  sq->back = node;
}

// squeue_remove_front(sq) removes and returns the item at the front of sq
// note: caller must free the returned string
// requires: sq is not empty
// effects: modifies sq
// time: O(1)
char *squeue_remove_front(struct squeue *sq) {
  assert(sq);
  assert(sq->front);
  char *yeet = malloc((strlen(sq->front->string)+1)* sizeof(char));
  strcpy(yeet, sq->front->string);
  struct llnode *old_front = sq->front;
  sq->front = sq->front->next;
  free(old_front->string); // this does it
  free(old_front);
  return yeet;
}

// squeue_front(sq) returns a (const) pointer the front item in sq
// requires: sq is not empty
// time: O(1)
const char *squeue_front(const struct squeue *sq) {
  assert(sq);
  assert(sq->front);
  return sq->front->string;
}

// squeue_is_empty(sq) determines if sq is empty
// time: O(1)
bool squeue_is_empty(const struct squeue *sq) {
  return (sq->front == NULL);
}

// squeue_destroy(sq) frees all memory for sq (including any strings)
// effects: sq is no longer valid
// time: O(n)
void squeue_destroy(struct squeue *sq) {
  char *a;
  while (!squeue_is_empty(sq)) {
    a = squeue_remove_front(sq);
    free(a);
  }
  free(sq);
}

// squeue_print(sq) prints the current queue
// notes: prints "[empty]\n" if sq is empty
//        prints "[%s]\n" if sq has a single item
//        prints "[%s->%s->...->%s]\n" otherwise
//               so if the queue from front->back is "dog", "cat", "", "rat"
//               prints "[dog->cat->->rat]\n"
// effects: displays output
// time: O(n + k)
void squeue_print(const struct squeue *sq) {
  if (squeue_is_empty(sq)) {
    printf("[empty]\n");
  } else if (!(sq->front->next)) {
    printf("[%s]\n", sq->front->string);
  } else {
    printf("[");
    struct llnode *node = sq->front;
    while (node->next) {
      printf("%s->", node->string);
      node = node->next;
    }
    printf("%s]\n", node->string);
  }
}
