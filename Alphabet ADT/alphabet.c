/////////////////////////////////////////////////////////////////////////////
// Alphabet ADT
/////////////////////////////////////////////////////////////////////////////

#include "alphabet.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cs136-trace.h"
#include "readstr.h"

// For the efficiency analysis:
// m : message length (of array) calculated with strlen
// n : dictionary length



struct alphabet {
  const struct wordmap *wm;  // an array things
    int len;
  const char *ef_msg;
  char df_msg;
};

// alphabet_create(map, maplen, encode_fail, decode_fail) creates
//   a new alphabet ADT from the given word map and the string/char
//   to use when an encode/decode mismatch occurs
// requires: every char c and string word in map is unique [not asserted]
// effects: allocates memory (must call alphabet_destroy)
// time: O(1), No loops. array of maps passed as pointer
struct alphabet *alphabet_create(const struct wordmap map[], int maplen,
                                 const char *encode_fail, char decode_fail) {
  struct alphabet *al = malloc(sizeof(struct alphabet));
  al->wm = map;
  al->len = maplen;
  al->ef_msg = encode_fail;
  al->df_msg = decode_fail;
  return al;
}

// alphabet_destroy(st) destroys the alphabet a
// effects: a is no longer valid
// time: O(1)
void alphabet_destroy(struct alphabet *a) {
  assert(a);
  free(a);
}


bool member(char b, const struct alphabet *a) {
  assert(a);
  for (int j = 0; j< a->len; j++) {
    if (b == a->wm[j].c) {
      return true;
    }
  }
  return false;
}


// alphabet_encode(a, msg) returns a 'new' string (caller must free)
//   that is the result of msg being encoded via the alphabet
// notes: adds a single space in-between the codes
//        unknown codes are shown as encode_fail (see alphabet_create)
// example: for a typical nato alphabet,
//          alphabet_encode(a, "cs") => "charlie sierra"
// effects: allocates memory (caller must free)
// time: O(m^2 * n) worst case
char *alphabet_encode(const struct alphabet *a, const char *msg) {
  assert(a);
  assert(msg);
  int msglen = strlen(msg);

    // make a copy of message;
  char *cpy = malloc((1+ msglen)*(sizeof(char)));
  strcpy(cpy, msg);
  // NO!


  int enc_len = strlen(a->ef_msg);
  int outputlen = 0;
  char *output = malloc((2+ msglen)*(sizeof(char)));
  strcpy(output, ""); // initialize to nothing;

  for (int i = 0; i <msglen; i++) {
    // for each charachter in msg
    if (!member(cpy[i], a)) {
      outputlen += 2 + enc_len;
      output = realloc(output,
                       (5+ outputlen*sizeof(char)));
      strcat(output, a->ef_msg);

    } else {
      for (int j = 0; j< a->len; j++) {
        // compare agains each char in dic
        if (cpy[i] == a->wm[j].c) {
          outputlen += strlen(a->wm[j].word);
          output = realloc(output,
                           ((5 + outputlen)
                            *sizeof(char)));
          strcat(output, a->wm[j].word);
          break;
        }
      }
    }
    if (i == msglen-1) break;
    outputlen++;
    strcat(output, " ");
  }
  free(cpy);
  return output;
}


// determines if a word is a member of a dictionary
// O(n)
bool wordmmbr(char *b, const struct alphabet *a) {
  assert(a);
  assert(b);
  for (int j = 0; j< a->len; j++) {
    if (strcmp(b, a->wm[j].word) == 0) {
      return true;
    }
  }
  return false;
}


// alphabet_decode(a, msg) returns a 'new' string (caller must free)
//   that is the result of msg being decoded via the alphabet
// notes: whitespace separates codes in msg (extra whitespace ignored)
//        unknown codes are shown as decode_fail (see alphabet_create)
// example: for a typical nato alphabet,
//          alphabet_decode(a, "charlie    sierra") => "cs"
// effects: allocates memory (caller must free)
// time: O(n*m^2) worst case because of use of realloc
char *alphabet_decode(const struct alphabet *a, const char *msg) {
  assert(a);
  assert(msg);
  int outputlen = 0;
  char *output = malloc((2)*(sizeof(char)));
  strcpy(output, ""); // initialize to nth;
  int i = 0;
  int mslen = strlen(msg);
  while (i <= mslen) {
    // find the dam curr_word
    char *cur_word = malloc(1000*sizeof(char));

    int worlen =0;
    int k = 0;
    while ((i <= mslen)&&(msg[i] != ' ')) {
      cur_word[k] = msg[i];
      i++;
      worlen++;
      k++;
    }
    cur_word = realloc(cur_word, (1+ worlen)*sizeof(char));
    cur_word[worlen] = 0;

    while ((i <= mslen)&&(msg[i] == ' ')){
      ++i;
    }
    if (!wordmmbr(cur_word, a)) {
      outputlen += 2;
      output = realloc(output,
                       (5+ outputlen*sizeof(char)));
      char str[2] = {a->df_msg, '\0'};
      strcat(output, str);
    } else {
      for (int j = 0; j< a->len; j++) {
        if (strcmp(cur_word, a->wm[j].word)==0) {
          outputlen ++;
          output = realloc(output,(outputlen+5)*sizeof(char));
          char str[2] = {a->wm[j].c, '\0'};
          strcat(output, str);
          break;
        }
      }
    }
    free(cur_word);
  }
  return output;
}
