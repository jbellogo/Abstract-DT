// This is a module that provides a queue of strings [squeue] ADT
// where each string is dynamically allocated (copied) when pushed

// times: n is the length of the queue (number of items)
//        m is the length of the string (parameter)
//        k is the combined length of all strings in the queue

#include <stdbool.h>

struct squeue;

// squeue_create() crates a new empty squeue
// effects: allocates memory (client must call squeue_destroy)
// time: O(1)
struct squeue *squeue_create(void);

// squeue_add_back(str, sq) adds str to the back of sq
// note: makes a 'copy' of str (caller must free when removed)
// requires: str is a valid (non-null) string
// effects: modifies sq
// time: O(m)
void squeue_add_back(const char *str, struct squeue *sq);

// squeue_remove_front(sq) removes and returns the item at the front of sq
// note: caller must free the returned string
// requires: sq is not empty
// effects: modifies sq
// time: O(1)
char *squeue_remove_front(struct squeue *sq);

// squeue_front(sq) returns a (const) pointer the front item in sq
// requires: sq is not empty
// time: O(1)
const char *squeue_front(const struct squeue *sq);

// squeue_is_empty(sq) determines if sq is empty
// time: O(1)
bool squeue_is_empty(const struct squeue *sq);

// squeue_destroy(sq) frees all memory for sq (including any strings)
// effects: sq is no longer valid
// time: O(n)
void squeue_destroy(struct squeue *sq);

// squeue_print(sq) prints the current queue
// notes: prints "[empty]\n" if sq is empty
//        prints "[%s]\n" if sq has a single item
//        prints "[%s->%s->...->%s]\n" otherwise
//               so if the queue from front->back is "dog", "cat", "", "rat"
//               prints "[dog->cat->->rat]\n"
// effects: displays output
// time: O(n + k)
void squeue_print(const struct squeue *sq);
