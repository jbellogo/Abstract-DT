
#include "Playlist.h"
#include <iostream>

/*
class Playlist {
    friend std::ostream & operator<<( std::ostream & out, Playlist & p );   
    std::vector <DigitalMedia *> vec;
    int totalSeconds, secondsPlayedSoFar; 

    //////////////////////////////////////
    //SHOULD ANY OF THESE BE STATIC?????//
    //////////////////////////////////////

*/
Playlist::Playlist(){} 
Playlist::~Playlist(){}

void Playlist::reset() {
    secondsPlayedSoFar = 0;
} // resets the elapsed time back to 0

void Playlist::add( DigitalMedia * m ) {
    if ( m ) {
        vec.push_back(m);
    }
}
/// I THINK ERASE TAKES IN An iterator
void Playlist::remove( DigitalMedia * m ) {
    for (PlaylistIterator it = this->begin(); it != this->end(); ++it){
        if (*it == m) {
                // found it
                vec.erase(it.currit);
        }
    }
}

PlaylistIterator Playlist::begin() {
    return PlaylistIterator{this->vec.begin()};
}
PlaylistIterator Playlist::end() {
    return PlaylistIterator{this->vec.end()};
}

int Playlist::getTotalSeconds() const {
    return totalSeconds;
}

std::ostream & operator<<( std::ostream & out, Playlist & p ) {
        // check executable for out specifics
        for (PlaylistIterator it = p.begin(); it != p.end(); ++it){
            out << '\t';
            (*it);// ->print(out);
        }
        out << "Total: ";
        return out;
}
