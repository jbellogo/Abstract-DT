
#include "PlaylistIterator.h"
#include <vector>
#include <iostream>
/* 
class PlaylistIterator {
    friend class Playlist;
    int totalSeconds, secondsPlayedSoFar;
    std::vector < DigitalMedia * >::iterator currit;
    explicit PlaylistIterator( std::vector < DigitalMedia *>::iterator);
*/
PlaylistIterator::PlaylistIterator( std::vector <DigitalMedia*>::iterator it) : 
    totalSeconds{0},
    secondsPlayedSoFar{0},
    currit{it} {}

int PlaylistIterator::getElapsedTime() const {
    return secondsPlayedSoFar;
}


// Caller "plays" the item by printing its information to std::cout.
DigitalMedia * PlaylistIterator::operator*() {
    // std::cout << *currit;
    (*currit)->print(std::cout);
    std::cout << std::to_string(secondsPlayedSoFar) + '/';
    std::cout << std::to_string(totalSeconds)  << std::endl;
    return *currit;
}

    // Adds the duration of the item just played to the total time elapsed so far before moving
    // the iterator.
PlaylistIterator PlaylistIterator::operator++() {
    secondsPlayedSoFar += totalSeconds;
    ++currit;
    return *this;
}

bool PlaylistIterator::operator==(const PlaylistIterator &other) const {
    return currit == other.currit;
}
bool PlaylistIterator::operator!=(const PlaylistIterator &other) const {
    return !(*this == other);
}
