// SEASHELL_READONLY   [do not copy/paste this line into a .c file]


// This .h file just provides the transparent wordmap structure


// requires: c must be one of: ' ', '\n' or '!'...'~'
//           word must be non-NULL, not empty, and cannot contain whitespace
struct wordmap {
  char c;
  char *word;
};
