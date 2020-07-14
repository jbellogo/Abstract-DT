
#include "Song.h"


// Sets key, title, duration, artist, album, and genre information.
// Raises: std::length_error if key.length() < 1 or title.length() < 1
//         std::invalid_argument if duration < 1
//         std::length_error if artist.length() < 1
// (checks are made in order listed)

////////////////////////////////////////////
/// APPARENTLY ALBUM AND GENRE CAN BE EMPTY STR
/////////////////////////////////////////
Song::Song( const std::string & key, const std::string & title, int duration,
            const std::string & artist, const std::string & album, const std::string & genre )
        : DigitalMedia{key, title, duration},
        artist{check_lt_str("artist",artist)},
        album{album},
        genre{genre} {
}

Song::~Song() {
        delete this;
}

void Song::print( std::ostream & out ) {

}

const std::string & Song::getArtist() const {
        return artist;
}
const std::string & Song::getAlbum() const {
        return album;
}
const std::string & Song::getGenre() const {
        return genre;
}

// Returns modified output stream. Outputs (key, "title", "album", "artist", duration, "genre").
// (Explicitly surrounds strings that might have whitespace within with double-quotation marks.)
std::ostream & operator<<( std::ostream & out, const Song & s ) {
        out << "(" << s.getKey() <<  " \""<< s.getTitle() << "\", ";
        out << '\"'<< s.getAlbum() << "\", ";
        out << '\"'<< s.getArtist() << "\", ";
        out << s.getDuration() << ", ";
        out << '\"'<< s.getGenre() << "\")";
        return out;
}

// Returns modified input stream. Contents of s over-written with information read in, where
// format is "key\ntitle\nduration\nartist\nalbum\ngenre\n".
// Raises std::runtime_error if fails to obtain any of the elements, if any of the strings
// except for genre are empty, or if duration cannot be successfully converted to an int.
std::istream & operator>>( std::istream & in, Song & s ) {
        int duration;
        std::string key, title, artist, album, genre;

        getString(in, key, "failed to read in key");
        getString(in, title, "failed to read in title");
        getInteger(in, duration, "failed to read in duration");

        getString(in, artist, "failed to read in artist");
        getString(in, album, "failed to read in album");
        getString(in, genre, "failed to read in genre");

        // lets see if them move assignemtn constructors work
        s = Song{key, title, duration, artist, album, genre}; // or should be new? or declare as freind class
        return in;
}
