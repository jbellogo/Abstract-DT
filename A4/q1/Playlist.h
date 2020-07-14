#ifndef _PLAYLIST_
#define _PLAYLIST_

#include <string>
#include "PlaylistIterator.h"
#include <vector>

class DigitalMedia; // forward declaration

class Playlist {
    friend std::ostream & operator<<( std::ostream & out, Playlist & p );   
    std::vector <DigitalMedia *> vec;
    int totalSeconds, secondsPlayedSoFar;
    // *** fill in
public:
    Playlist();
    virtual ~Playlist();
    void reset(); // resets the elapsed time back to 0
    void add( DigitalMedia * m );
    void remove( DigitalMedia * m );
    PlaylistIterator begin();
    PlaylistIterator end();
    int getTotalSeconds() const;
};

std::ostream & operator<<( std::ostream & out, Playlist & p );

#endif
