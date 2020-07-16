#include "doublewords.h"
#include "textprocess.h"
using std::string;
#include <sstream>      // std::stringstream
#include <vector>
#include <iostream>
using std::vector;

Doublewords::Doublewords (TextProcessor *component) : Decorator{component},
        secondtime{false}{
}

// VIRTUAL METHODS

Doublewords::~Doublewords(){
        //delete source;
}

void Doublewords::setSource(std::istream *inp) {
        source = inp;
}

//////////////////////////////////////////////////////////

std::string Doublewords::getWord(){
        if (secondtime) {
                secondtime = false;
        } else {
                component->setSource(source);
                curr = component->getWord();
                secondtime = true;
        }
        //(ss) << curr;
        //component->setSource( ss );
        return curr;
}

//std::stringstream *ss =  new std::stringstream{curr};
//std::iostream *ss = new std::iostream{};

/*
   std::stringstream *ss = nullptr;
   if (curr == "") {
        (*source) >> stored;
        curr = stored;
        secondtime = true;
   }

   if (!secondtime) {
        //FIRST
        (*source) >> stored;
        ss = new std::stringstream{curr};
        secondtime = true;
   } else {
        // SECOND
        ss = new std::stringstream{curr};
        curr = stored;
        secondtime = false;
   }
 */
