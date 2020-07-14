/*
   class DigitalMedia; // forward declaration
   class LibraryIterator;

   class Library {
   friend std::ostream & operator<<( std::ostream & out, const Library & lib );
   std::map <std::string, DigitalMedia *> lst;
 */
#include "Library.h"

Library::Library() {}
                 // Creates empty library.

Library::~Library() {
        //delete lst; default map destructors might take care of it 
}                          // Destroys all items in library.


LibraryIterator Library::begin() {
        LibraryIterator it{this->lst.begin()};
        return it;
}             // Iterator set to beginning of library contents.


LibraryIterator Library::end(){
        return LibraryIterator{this->lst.end()};
}               // Iterator set past end of library contents.

// Stores item, indexed by key. If key already exists, raises std::logic_error
// and specifies as the message that "key KKKK already exists in library".
void Library::add( DigitalMedia * m ) {
        if (lst.find(m->getKey()) == lst.end()){
                std::string mssg = "key " + m->getKey() + " already exists in library";
                throw std::logic_error(mssg);
        } else {
                lst.insert({m->getKey(), m});
        }
}

void Library::remove( std::string key ){
        if (lst.find(key) != lst.end()){
                // found it
                lst.erase(key);
        }
}     // Remove item if find key value else does nothing.

// Returns pointer to item, or nullptr if not there.
DigitalMedia * Library::find( std::string key ){
        if (lst.find(key) != lst.end()){
                return lst.find(key)->second;
        }
        return nullptr;
}


// Returns modified output stream. Stream contains the header "Library:\n" and the library
// contents, ordered by key. Each object is output using the appropriate output operator
// for the underlying object type, one per line and starting with a tab character.
std::ostream & operator<<( std::ostream & out, Library & library ) {
        out << "library:\n";
        /// NEED TO USE THE ITERATOR
        for (auto const& media : library.lst){
                out << '\t' << media.second << std::endl;   // already overloaded should be.
        }
        return out;
}


// Returns modified input stream. Contents of library modified with information read in,
// where the character 't' on a line specifies a TV show is to be read next, while 's'
// indicates that a Song is to be read in next. Reading continues until EOF is reached
// or an exception is raised. Raises std::runtime_error( "invalid media type" ) if doesn't
// get either 's' or 't'.
std::istream & operator>>( std::istream & in, Library & library ){
        char cha;
        while (! in.eof()){
                try {
                        in >> cha;
                      
                } catch (...) {
                        throw std::runtime_error("invalid media type");
                }
                
                if ( cha == 't' ){
                        TV tv{" ", " ", 1, 1, 1, " "};
                        in >> tv;
                        library.add(tv);
                } else if (cha == 's'){
                        Song sg{" ", " ", 1, " ", " ", " "};
                        in >> sg;
                        library.add(sg);
                } else {
                        throw std::runtime_error("invalid media type");
                }

        }
        return in;
}
