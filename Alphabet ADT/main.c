// This is a test client for the alphabet ADT
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabet.h"
#include "nato.h"
#include "slurp.h"

int main(void) {
  char buffer[1024] = {0};
  assert(scanf("%s", buffer) == 1);
  assert(!strcmp(buffer, "[encode]") || !strcmp(buffer, "[decode]"));

  struct alphabet *a = alphabet_create(nato_alphabet, nato_len, "?!?", '?');

  char *msg = slurp();
  char *result = "";
  if (!strcmp(buffer, "[encode]")) {
    result = alphabet_encode(a, msg);
  } else {
    result = alphabet_decode(a, msg);
  }
  printf("%s\n", result);
  free(msg);
  free(result);
  alphabet_destroy(a);
}
