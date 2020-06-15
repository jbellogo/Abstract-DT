// This modulde provides an Alphabet ADT
// that can encode or decode a message using a phonetic alphabet

// NOTE: * all alphabet parameters must be valid (not NULL)
//       * all strings must be valid (non-null) strings
//       * an empty message string (or all whitespace msg for decode)
//         should return a 'new' empty string

#include "wordmap.h"

struct alphabet;

// alphabet_create(map, maplen, encode_fail, decode_fail) creates
//   a new alphabet ADT from the given word map and the string/char
//   to use when an encode/decode mismatch occurs
// requires: every char c and string word in map is unique [not asserted]
// effects: allocates memory (must call alphabet_destroy)
// time: ??? comment in implementation
struct alphabet *alphabet_create(const struct wordmap map[], int maplen,
                                 const char *encode_fail, char decode_fail);

// alphabet_destroy(st) destroys the alphabet a
// effects: a is no longer valid
// time: ??? comment in implementation
void alphabet_destroy(struct alphabet *a);

// alphabet_encode(a, msg) returns a 'new' string (caller must free)
//   that is the result of msg being encoded via the alphabet
// notes: adds a single space in-between the codes
//        unknown codes are shown as encode_fail (see alphabet_create)
// example: for a typical nato alphabet,
//          alphabet_encode(a, "cs") => "charlie sierra"
// effects: allocates memory (caller must free)
// time: ??? comment in implmentation
char *alphabet_encode(const struct alphabet *a, const char *msg);

// alphabet_decode(a, msg) returns a 'new' string (caller must free)
//   that is the result of msg being decoded via the alphabet
// notes: whitespace separates codes in msg (extra whitespace ignored)
//        unknown codes are shown as decode_fail (see alphabet_create)
// example: for a typical nato alphabet,
//          alphabet_decode(a, "charlie    sierra") => "cs"
// effects: allocates memory (caller must free)
// time: ??? comment in implmentation
char *alphabet_decode(const struct alphabet *a, const char *msg);
