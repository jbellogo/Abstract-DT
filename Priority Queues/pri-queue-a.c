// Implementation file for pri-queue-a module
// USING AN array of queues

#include "pri-queue-a.h"
#include "squeue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include <string.h>


struct pri_queue {
  struct squeue **aosq;
  int num_levels;
};

// pri_queue_create(levels) creates a new priority queue
//   {{with a fixed number of priority levels from [0...levels - 1]}}
// requires: {{levels > 0}}
// effects: allocates memory (client must call pri_queue_destroy)
// time: {{O(k)}}
struct pri_queue *pri_queue_create(int levels) {
  assert(levels > 0);
  struct pri_queue *pq = malloc(sizeof(struct pri_queue));
  pq->num_levels = levels;
  pq->aosq = malloc(levels* sizeof(struct squeue *));
  for (int i= 0; i < levels; i++) {
    struct squeue *sq = squeue_create();
    pq->aosq[i] = sq;
  }
  return pq;
}

// pri_queue_add(item, priority, pq) adds item to pq with the given
//   priority
// note: makes a 'copy' of item (caller must free when removed)
// requires: {{0 <= priority < levels}}
// effects: modifies pq
//          allocates memory (caller must free when removed)
// time: O(m)
void pri_queue_add(const char *item, int priority, struct pri_queue *pq) {
  assert(pq);
  assert(item);
  assert(0 <= priority);
  assert(priority< pq->num_levels);
  const char *yeet = item;  // caller must free
  squeue_add_back(yeet, pq->aosq[priority]);
}


// pri_queue_is_empty(pq) determines if pq is empty
// time: {{O(k)}}
bool pri_queue_is_empty(const struct pri_queue *pq) {
  assert(pq);
  for (int i= 0; i < pq->num_levels; i++) {
    if (!squeue_is_empty(pq->aosq[i])) {
      return false;
    }
  }
  return true;
}

// pri_queue_remove(pq) removes and returns the item with the highest priority
// note: caller must free the returned string
// requires: pq is not empty
// effects: modifies pq
// time: {{O(k)}}
char *pri_queue_remove(struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  char *yeet = NULL;
  for (int i = pq->num_levels -1; i>=0; i--) {
    if (!squeue_is_empty(pq->aosq[i])) {
      yeet = (squeue_remove_front(pq->aosq[i]));
      return yeet;
    }
  }
  return 0;
}

// pri_queue_max(pq) returns the highest priority in pq
// requires: pq is not empty
// time: {{O(k)}}
int pri_queue_max(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  for (int i = pq->num_levels -1; i>=0; i--) {
    if (!squeue_is_empty(pq->aosq[i])) {
      return i;
    }
  }
  return 0;
}


// pri_queue_front(pq) returns a (const) pointer to the item in pq with the
//   highest priority
// requires: pq is not empty
// time: {{O(k)}}
const char *pri_queue_front(const struct pri_queue *pq) {
  assert(pq);
  assert(!pri_queue_is_empty(pq));
  for (int i = pq->num_levels -1; i>=0; i--) {
    if (!squeue_is_empty(pq->aosq[i])) {
      return (squeue_front(pq->aosq[i]));
    }
  }
  return 0;
}


// pri_queue_destroy(pq) frees all memory for pq (including any strings)
// effects: pq is no longer valid
// time: {{O(n + k)}}
void pri_queue_destroy(struct pri_queue *pq){
  char *a = NULL;
  while(!pri_queue_is_empty(pq)) {
    a = pri_queue_remove(pq);
    free(a);
  }
  for (int i= 0; i < pq->num_levels; i++) {   //O(k)
    free(pq->aosq[i]);
  }
  free(pq->aosq);
  free(pq);

}
