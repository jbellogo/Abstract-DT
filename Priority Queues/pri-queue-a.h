// times: n is the length of the queue (number of items)
//        m is the length of the string (parameter)
//        {{k is the number of levels}}

// NOTE: features of this interface that are _different_
//       for PRI-QUEUE-A are surrounded by {{double curly brackets}}

#include <stdbool.h>

struct pri_queue;

// pri_queue_create(levels) creates a new priority queue
//   {{with a fixed number of priority levels from [0...levels - 1]}}
// requires: {{levels > 0}}
// effects: allocates memory (client must call pri_queue_destroy)
// time: {{O(k)}}
struct pri_queue *pri_queue_create(int levels);

// pri_queue_add(item, priority, pq) adds item to pq with the given
//   priority
// note: makes a 'copy' of item (caller must free when removed)
// requires: {{0 <= priority < levels}}
// effects: modifies pq
//          allocates memory (caller must free when removed)
// time: O(m)
void pri_queue_add(const char *item, int priority, struct pri_queue *pq);

// pri_queue_remove(pq) removes and returns the item with the highest priority
// note: caller must free the returned string
// requires: pq is not empty
// effects: modifies pq
// time: {{O(k)}}
char *pri_queue_remove(struct pri_queue *pq);

// pri_queue_max(pq) returns the highest priority in pq
// requires: pq is not empty
// time: {{O(k)}}
int pri_queue_max(const struct pri_queue *pq);

// pri_queue_front(pq) returns a (const) pointer to the item in pq with the
//   highest priority
// requires: pq is not empty
// time: {{O(k)}}
const char *pri_queue_front(const struct pri_queue *pq);

// pri_queue_is_empty(pq) determines if pq is empty
// time: {{O(k)}}
bool pri_queue_is_empty(const struct pri_queue *pq);

// pri_queue_destroy(pq) frees all memory for pq (including any strings)
// effects: pq is no longer valid
// time: {{O(n + k)}}
void pri_queue_destroy(struct pri_queue *pq);
