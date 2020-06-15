// times: n is the number of symbols [symbol_count()]
//        m is the length of the string (parameter)

#include <stdbool.h>

struct symbol_table;

// is_valid_symbol_string(s) determines if the string in s is a valid
//   symbol according to the following naming rules:
//   * length is at least one
//   * only contain letters, underscores and numbers
//   * starts with a letter
// time: O(m)
bool is_valid_symbol(const char *s);

// symbol_table_create() creates an empty symbol table
// effects: allocates memory (must call symbol_table_destroy)
// time: O(1)
struct symbol_table *symbol_table_create(void);

// symbol_table_destroy(st) destroys the symbol table st
// effects: st is no longer valid
// time: O(n)
void symbol_table_destroy(struct symbol_table *st);

// the constant INVALID_SYMBOL is returned by symbol_lookup & symbol_read when:
// * the string (parameter or from input) is not a valid symbol
// * the end of the input (e.g., EOF) is encountered in symbol_read
extern const int INVALID_SYMBOL;

// symbol_count(st) returns the number of symbol IDs that have been
//   generated
// time: O(1)
int symbol_count(const struct symbol_table *st);

// symbol_read(st) returns the ID for the next symbol from input
//   (which may be a new or existing ID) or INVALID_SYMBOL
// effects: reads from input
//          may modifies st
// time: ??? comment in implementation -- at worst: O(n * m)
int symbol_read(struct symbol_table *st);

// symbol_lookup(st, symbol_string) returns the ID for symbol_string
//   (which may be a new or existing ID) or INVALID_SYMBOL
// effects: may modify st
// time: ??? comment in implementation -- at worst: O(n * m)
int symbol_lookup(struct symbol_table *st, const char *symbol_string);

// symbol_print(st, symbol_id) prints the symbol corresponding to symbol_id
//   using "%s" (no newline)
// requires: symbol_id is a valid ID: 0 < symbol_id <= symbol_count()
// effects: displays a message
// time: O(m)
void symbol_print(const struct symbol_table *st, int symbol_id);
