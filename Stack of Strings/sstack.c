/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cs136-trace.h"
#include <assert.h>

struct sstack {
  int len;
  int maxlen;
  char **data;
};

struct sstack *sstack_create(void) {
  struct sstack *s = malloc(sizeof(struct sstack));
  s->len = 0;
  s->maxlen = 1;
  s->data = malloc((s->maxlen) * sizeof(char *)); // it must be freed when used
  return s;
}

bool sstack_is_empty(const struct sstack *ss) {
  assert(ss);
  return (ss->len == 0);
}

const char *sstack_top(const struct sstack *ss) {
  assert(ss);
  assert(ss->len); // non-empty
  return *(ss->data + ss->len -1);
}


char *sstack_pop(struct sstack *ss) {
  assert(ss);
  assert(ss->len); // non-empty
  ss->len -=1;
  if (4*(ss->len) == ss->maxlen) {
    ss->maxlen /= 2;
  }
  return *(ss->data + ss->len);
}


void sstack_push(const char *str, struct sstack *ss) {
  assert(str);
  assert(ss);
  char *yeet = malloc(sizeof(char)*(1+ strlen(str)));
  strcpy(yeet, str);
  if (ss->len == ss->maxlen) {
    ss->maxlen *= 2;
    ss->data = realloc(ss->data, ss->maxlen *(sizeof(char *)));
  }
  assert(ss->data);
  *(ss->data + ss->len) = yeet;
  // now this points at a malloc in the heap (yeet)
  // will be freed when destroyed
  ss->len +=1;
}

void sstack_destroy(struct sstack *ss) {
  for (int i = 0; i < ss->len; i++) {
    free(ss->data[i]);
  }
  free(ss->data);
  free(ss);
}

void sstack_status(const struct sstack *ss) {
  assert(ss);
  int length = ss->len;
  int maximum_capacity = ss->maxlen;
  printf("status: %d/%d\n", length, maximum_capacity);
}
