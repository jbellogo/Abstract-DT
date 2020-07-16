#include "doublewords.h"
#include "textprocess.h"
using std::string;
#include <sstream>      // std::stringstream
#include <vector>
using std::vector;

Doublewords::Doublewords (TextProcessor *component) : Decorator{component},
secondtime{false}, curr{""}{}

// VIRTUAL METHODS

Doublewords::~Doublewords(){
  //delete source;
}

void Doublewords::setSource(std::istream *inp) { source = inp; }


std::string Doublewords::getWord(){
  // get every single input.
 if (! secondtime) {
    string input;
    (*source) >> input;
    vec.push_back(input);
  }

  // SKIP the current
  /*if (curr == "") {
    curr = vec.front();
  }*/
  std::stringstream *ss = new std::stringstream{curr};
  component->setSource( ss );

  if (secondtime || curr == "") {
    secondtime = false;
    vec.erase(vec.begin()); // erase
    curr = vec.front(); // set new curr
  } else {
    secondtime = true;
  }

  return component->getWord();
}


/*
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
*/
