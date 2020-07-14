
#include "LibraryIterator.h"

/*
class Library; // forward declarations
class DigitalMedia;
*/


// or should it take an iterator
LibraryIterator::LibraryIterator(std::map <std::string, DigitalMedia *>::iterator it) 
: currit{it} {}  // Private constructor


DigitalMedia * LibraryIterator::operator*() {
        return currit->second;
}
LibraryIterator LibraryIterator::operator++() {
    ++currit;
    return *this;
}
bool LibraryIterator::operator==(const LibraryIterator &other) const {
        return currit == other.currit;
    }
bool LibraryIterator::operator!=(const LibraryIterator &other) const {
        return !(*this == other);
}    

