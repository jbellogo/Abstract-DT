#include <iostream>
#include <sstream>
using namespace std;
const int MAX_INT_SETS = 5;

struct IntSet {
  int *data;
  int size;
  int capacity;
};
///////////////////////////////////////////////////////////////////////////////

void init( IntSet & i ) {    // Initialize to be "empty" with following field values: {nullptr,0,0}
  i.data = nullptr;
  i.size = 0;
  i.capacity = 0;
}
///////////////////////////////////////////////////////////////////////////////

void destroy( IntSet & i ){
  delete [] i.data;
} // Clean up the IntSet and free dynamically allocated memory.

///////////////////////////////////////////////////////////////////////////////

bool contains( const IntSet & i, int e ) {
  for (int j = 0; j < i.size; j++) {
    if (e == i.data[j]) return true;
  }
  return false;
}     // True if set i contains element e.

///////////////////////////////////////////////////////////////////////////////

void add( IntSet & i, int e ) {
  if (contains(i, e)) return;
  if (i.size == 0) {
    i.capacity == 5;
    i.size++;
    i.data = new int [5]; /// hmm
    i.data[0] = e;
    return;
  }
  if (i.size == i.capacity) {
    i.capacity  *= 2;
  }
  i.size++;
  for (int j = i.size-1; j > 0; j--) {
    if (i.data[j-1] < e) {
      i.data[j] = e;
      return;
    } else {
      i.data[j] = i.data[j-1];
    }
  }
  i.data[0] = e;
} // Add element e to the set i.

///////////////////////////////////////////////////////////////////////////////
// UNION
IntSet operator| ( const IntSet & i1, const IntSet & i2 ) {
  IntSet un;
  init( un );

  for (int i = 0; i < i1.size ; i++) {
    add(un, i1.data[i]);
  }
  for (int i = 0; i < i2.size ; i++) {
    add(un, i2.data[i]);
  }
  return un;
} // Set union.

///////////////////////////////////////////////////////////////////////////////
IntSet operator& ( const IntSet & i1, const IntSet & i2 ){
  IntSet in;
  init( in );
  for (int i = 0; i < i1.size ; i++) {
    if (contains(i2, i1.data[i])) {
      add(in, i1.data[i]);
    }
  }
  return in;
} // Set intersection.
///////////////////////////////////////////////////////////////////////////////

bool operator==( const IntSet & i1, const IntSet & i2 ){
  if (i1.size != i2.size) { return false; }
  for (int i = 0; i < i1.size ; i++) {
    if (i1.data[i] != i2.data[i]) { return false; }
  }
  return true;
} // Set equality.


///////////////////////////////////////////////////////////////////////////////

bool isSubset( const IntSet & i1, const IntSet & i2 ) {
  for (int i = 0; i < i2.size ; i++) {
    if (! contains(i1, i2.data[i])) return false;
  }
  return true;
}   // True if i2 is a subset of i1.

///////////////////////////////////////////////////////////////////////////////

int find_index(IntSet & i, int e){
  for (int j = 0; j < i.size; j++) {
    if (e == i.data[j]) {
      return j;
    }
  }
  return -1;
}

void remove( IntSet & i, int e ){
  int index = find_index(i, e);
  if (index = -1) return; // not in set
  for (int j = index; j < i.size -1; j++) {
    i.data[j] = i.data[j+1];
  }
  --i.size;
} // Remove element e from the set i.

///////////////////////////////////////////////////////////////////////////////

// Output operator for IntSet.
std::ostream& operator<<( std::ostream & out, const IntSet & is ){
  out << "(";
  for (int j = 0; j < is.size; j++) {
    out << is.data[j];
    if (j != is.size-1) {
      out << ",";
    }
  }
  out << ")";
  return out;
}

// Input operator for IntSet. Continuously read int values from in and add to the passed IntSet.
// Function stops when input contains a non-int value. Discards the first non-int character.
std::istream& operator>>( std::istream & in, IntSet & is ) {
  int num;
  while (true) {
    if (! (in >> num)) {
      if (in.eof()) return in;
      in.clear();
      in.ignore();
      break;
    } else{
      add(is, num);
    }
  }
  return in;
}


// Test harness for IntSet functions. You may assume that all commands entered are valid.
// Valid commands: n <ind>,  p <ind>, & <ind1> <ind2>,
//                 | <ind1> <ind2>, = <ind1> <ind2>,
//                 s <ind1> <ind2>, c <ind1> <elem>,
//                 a <ind1> <elem>, r <ind1> <elem>,
//                 q/EOF
// Silently ignores invalid commands. Doesn't check that 0 <= index < MAX_INT_SETS.
// Do not test invalid commands!

int main() {
  bool done = false;
  IntSet sets[MAX_INT_SETS], tmpSet;
  for ( int i = 0; i < MAX_INT_SETS; i++ ) init( sets[i] );
  init( tmpSet );

  while ( ! done ) {
    char c;
    int lhs, rhs;
    cerr << "command?" << endl;
    cin >> c; // Reads command.

    if (cin.eof()) break;

    switch(c) {
      case 'n':
        // Create new IntSet at index lhs after destroying the old.
        // Read in integers to add to it until hitting non int using operator>>.
        cin >> lhs;
        destroy( sets[lhs] );
        init( sets[lhs] );
        cerr << "enter integer values for sets[" << lhs << "], terminated by non-int: " << endl;
        cin >> sets[lhs];
        break;

      case 'p':
        // Print IntSet at lhs.
        cin >> lhs;
        cout << sets[lhs] << endl;
        break;

      case '&':
        // Print intersection of lhs and rhs.
        cin >> lhs >> rhs; // reads in two indices
        destroy( tmpSet );
        init( tmpSet );
        tmpSet = (sets[lhs] & sets[rhs]);
        cout << tmpSet << endl;
        break;

      case '|':
        // Print union of lhs and rhs.
        cin >> lhs >> rhs;
        destroy( tmpSet );
        init( tmpSet );
        tmpSet = (sets[lhs] | sets[rhs]);
        cout << tmpSet << endl;
        break;

      case '=':
        // Print true if lhs == rhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << (sets[lhs] == sets[rhs]) << endl;
        break;

      case 's':
        // Print true if rhs is subset of lhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << isSubset( sets[lhs], sets[rhs] ) << endl;
        break;

      case 'c':
        // Print true if lhs contains element rhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << contains( sets[lhs], rhs ) << endl;
        break;

      case 'a':
        // Add elem rhs to set lhs
        cin >> lhs >> rhs;
        add( sets[lhs], rhs );
        break;

      case 'r':
        // Remove elem rhs from set lhs
        cin >> lhs >> rhs;
        remove( sets[lhs], rhs );
        break;

      case 'q':
        // Quit
        done = true;
        break;

    } // switch
  } // while

  for ( int i = 0; i < MAX_INT_SETS; i++ ) destroy( sets[i] );
  destroy( tmpSet );
} // main
