#include "util.h"

void getString( std::istream & in, std::string & s, const char * fieldType ) {
        try {
                getline( in, s );
                if (in.eof()) {
                        throw std::runtime_error{fieldType};
                }
        } catch (...) {   // or just eof inclusive /// TEST EMPTY STRINGs
                throw std::runtime_error{fieldType};
        }
        // *** If getline fails to obtain the necessary argument, raise
        // *** std::runtime_error initialized with the fiedlType parameter passed in.
} // getString

void getInteger( std::istream & in, int & i, const char * fieldType ) {
        std::string s;
        try{
                getline( in, s );
                i = std::stoi(s);
                if (in.eof()) {
                        throw std::runtime_error{fieldType};
                }
        } catch (...) {   // should be inclusive
                throw std::runtime_error{fieldType};
        }


        // *** If std::stoi fails, or getline fails to obtain the necessary argument, raise
        // *** std::runtime_error initialized with the fiedlType parameter passed in.
} // getInteger
