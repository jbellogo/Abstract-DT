#include "DigitalMedia.h"
/*
   class DigitalMedia {
   // *** fill in
   std::string key, title;
   int duration;
 */

// make these private
int check_lt_int(std::string idenfy, int len){
        if (len >= 1) return len;
        throw std::invalid_argument(idenfy + "< 1");
}

std::string check_lt_str(std::string idenfy, std::string str){
        if (str.length() >= 1) return str;
        throw std::length_error(idenfy + "has length < 1");
}

// Sets key, title and duration information.
// Raises: std::length_error if key.length() < 1 or title.length() < 1
//         std::invalid_argument if duration < 1 (checks are made in order listed)
DigitalMedia::DigitalMedia( const std::string & key, const std::string & title, int duration )
        : key{check_lt_str("key", key)}, 
        title{check_lt_str("title",title)}, 
        duration{check_lt_int("duration", duration)} {}

DigitalMedia::~DigitalMedia() {
}                          // this should do it?

// Concrete subclasses use this to invoke their output operator so that Library
// container can successfully print its contents using the iterator.
//////////////////
// virtual void print( std::ostream & out ) = 0;
///////////// THIS IS NOT IMPLEMENTED!

const std::string & DigitalMedia::getKey() const {
        return key;
}
const std::string & DigitalMedia::getTitle() const {
        return title;
}
int DigitalMedia::getDuration() const {
        return duration;
}
