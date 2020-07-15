#include "doublewords.h"
#include "textprocess.h"
using std::string;
#include <sstream>      // std::stringstream
Doublewords::Doublewords (TextProcessor *component) : Decorator{component},
secondtime{false}, word_to_reap{""}{}

// VIRTUAL METHODS

Doublewords::~Doublewords(){
  delete source;
}

void Doublewords::setSource(std::istream *inp) { source = inp; }


std::string Doublewords::getWord(){
  // this is where you return the new one.
  if (secondtime) {
    secondtime = false;
  } else {
    (*source) >> word_to_reap;
    secondtime = true;
    //std::stringstream *ss =
  }
  component->setSource(  new std::stringstream{word_to_reap} );
  


  // wont survive unless its in heap
  return component->getWord();
}
