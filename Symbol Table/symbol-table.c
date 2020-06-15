/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#include "symbol-table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct symbol_table {
  char **data;   // a list of strings
  int len;
  int minlen;
};


bool is_valid_symbol(const char *s) {
  assert(s);
  int len = strlen(s);
  if (len <= 0) {
    return false;
  }
  if (!(((s[0] >= 'A')&&(s[0] <= 'Z'))||
        ((s[0] >= 'a')&&(s[0] <= 'z')))
     ) {
    return false;
  }
  for (int i = 1; i< len; i++) {
    if (!(
      ((s[i] >= '0')&&(s[i] <= '9'))||
      ((s[i] >= 'A')&&(s[i] <= 'Z'))||
      ((s[i] >= 'a')&&(s[i] <= 'z'))||
      (s[i] == '_'))) {
      return false;
    }
  }
  return true;
}



struct symbol_table *symbol_table_create(void) {
  struct symbol_table *st = malloc(sizeof(struct symbol_table));
  st->len = 0;
  st->minlen = 1;
  st->data = malloc((st->minlen) * sizeof(char *));
  return st;
}


void symbol_table_destroy(struct symbol_table *st) {
  assert(st);
  for (int i = 0; i < st->len; i++) {
    free(st->data[i]);
  }
  free(st->data);
  free(st);
}


const int INVALID_SYMBOL = -1;

int symbol_count(const struct symbol_table *st) {
  assert(st);
  return st->len;
}

int symbol_read(struct symbol_table *st) {
  assert(st);
  //char s[10000];
  char s[1000];
  if ((scanf("%s", s) != 1)||(!is_valid_symbol(s))) {
    return INVALID_SYMBOL;
  }

  for (int i= 0; i < st->len; i++) {
    if (strcmp(st->data[i], s) == 0) {
      return i+1;
    }
  }
  // O(n) realloc
  if (st->len == st->minlen) {
    st->minlen *=2;
    st->data = realloc(st->data, st->minlen * sizeof(char *));
  }
  char *yeet = malloc((strlen(s)+1)*sizeof(char));
  strcpy(yeet,s);
  st->data[st->len] = yeet;
  ++(st->len);    // add item and return old len
  return st->len;
}


// time: O(n+m)
int symbol_lookup(struct symbol_table *st,
                  const char *symbol_string) {
  assert(st);
  if (!is_valid_symbol(symbol_string)) return  INVALID_SYMBOL;

  for (int i= 0; i < st->len; i++) {
    if (strcmp(st->data[i], symbol_string) == 0) {
      return i+1;
    }
  }

  if (st->len == st->minlen) {
    st->minlen *=2;
    st->data = realloc(st->data, st->minlen*sizeof(char *));
  }
  char *yeet = malloc((strlen(symbol_string)+1)* sizeof(char));
  strcpy(yeet,symbol_string);
  st->data[st->len] = yeet;
  ++(st->len);    // add item and return old len
  return st->len;
}


void symbol_print(const struct symbol_table *st, int symbol_id) {
  assert(st);
  assert(0 < symbol_id);
  assert(symbol_id <= symbol_count(st));

  printf("%s", st->data[symbol_id-1]);
}
