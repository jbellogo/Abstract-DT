#include "TV.h"
/*
   class TV : public DigitalMedia {
   int episode, season;
   std::string series;
 

int check_lt_int(std::string idenfy, int len){
        if (len >= 1) return len;
        throw std::invalid_argument(idenfy + "< 1");
}

std::string check_lt_str(std::string idenfy, std::string str){
        if (str.length() >= 1) return str;
        throw std::length_error(idenfy + "has length < 1");
}
*/
// Sets key, title, duration, episode, season, and series information.
// Raises: std::length_error if key.length() < 1 or title.length() < 1
//         std::invalid_argument if duration < 1
//         std::length_error if series.length() < 1
//         std::invalid_argument if episode < 1 or season < 1
// (checks are made in order listed)
TV::TV( const std::string & key, const std::string & title, int duration,
    int episode, int season, const std::string & series ) :
        DigitalMedia{key, title, duration},
episode{check_lt_int("episode",episode)},
season{check_lt_int("season", season)},
series{check_lt_str("series",series)} {}

TV::~TV() {
}
/// hmm
void TV::print( std::ostream & out ) {
        operator<<(out, *this);   // Now calling what its supposed to 
}

int TV::getEpisode() const {
        return episode;
}
int TV::getSeason() const {
        return season;
}

const std::string & TV::getSeries() const {
        return series;
}

std::string check_len(int se_ep_num){
        // no exceptions?
        std::string s = std::to_string(se_ep_num);
        if (se_ep_num < 10) {
                return "0" + s;
        }
        return s;    // or should we use casting
}

// Returns modified output stream. Outputs (key, "series" S<season>E<episode> "title", duration).
// (Explicitly surrounds strings that might have whitespace within with double-quotation marks.
// Season number and episode number have a default width of 2, and must start with '0' if < 10.)
std::ostream & operator<<( std::ostream & out, const TV & t ){
        out << "(" << t.getKey() << ", \""<< t.getSeries() << "\" ";
        out << "S"+ check_len(t.getSeason()) << "E" + check_len(t.getEpisode()) << " ";
        out << '\"'<< t.getTitle() << "\", ";
        out << t.getDuration() << ")";
        return out;
}



// Returns modified input stream. Contents of t over-written with information read in, where
// format is "key\ntitle\nduration\nseason\nepisode\nseries\n".
// Raises std::runtime_error if fails to obtain any of the elements with the message
// "failed to read in XXXX", where XXXX is replaced by one of: key, title, duration, season, episode,
// or series or if duration, season, or episode cannot be successfully converted to an int.
// Also follows the exception raise rules for the constructor.

std::istream & operator>>( std::istream & in, TV & t ) {
        int duration, season, episode;
        std::string key, title, series;
        getString(in, key, "failed to read in key");
        getString(in, title, "failed to read in title");
        getInteger(in, duration, "failed to read in duration");
        getInteger(in, season, "failed to read in season");
        getInteger(in, episode, "failed to read in episode");
        getString(in, series, "failed to read in series");
        // lets see if them move assignemtn constructors work
        t = TV{key, title, duration, episode, season, series}; // or should be new? or declare as freind class
        return in;
}
