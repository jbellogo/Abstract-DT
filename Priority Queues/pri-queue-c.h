// times: n is the length of the queue (number of items)
//        m is the length of the string (parameter)


#include <stdbool.h>

struct pri_queue;

// pri_queue_create(ignore) creates a new priority queue
//   {{ignore is ignored}}
// effects: allocates memory (client must call pri_queue_destroy)
// time: O(1)
struct pri_queue *pri_queue_create(int ignore);

// pri_queue_add(item, priority, pq) adds item to pq with the given
//   priority
// note: makes a 'copy' of item (caller must free when removed)
// effects: modifies pq
//          allocates memory (caller must free when removed)
// time: {{O(log n + m) [amortized]}}
void pri_queue_add(const char *item, int priority, struct pri_queue *pq);

// pri_queue_remove(pq) removes and returns the item with the highest priority
// note: caller must free the returned string
// requires: pq is not empty
// effects: modifies pq
// time: {{O(log n) [amortized]}}
char *pri_queue_remove(struct pri_queue *pq);

// pri_queue_max(pq) returns the highest priority in pq
// requires: pq is not empty
// time: O(1)
int pri_queue_max(const struct pri_queue *pq);

// pri_queue_front(pq) returns a (const) pointer to the item in pq with the
//   highest priority
// requires: pq is not empty
// time: O(1)
const char *pri_queue_front(const struct pri_queue *pq);

// pri_queue_is_empty(pq) determines if pq is empty
// time: O(1)
bool pri_queue_is_empty(const struct pri_queue *pq);

// pri_queue_destroy(pq) frees all memory for pq (including any strings)
// effects: pq is no longer valid
// time: O(n)
void pri_queue_destroy(struct pri_queue *pq);
