#include "dropfirst.h"
#include "textprocess.h"
using std::string;
#include <sstream>      // std::stringstream

/*
std::istream *source;
int upto;
std::string word;
*/
Dropfirst::Dropfirst (TextProcessor *component, int n) :
Decorator{component},
upto{n}{}

// VIRTUAL METHODS
void Dropfirst::setSource(std::istream *inp) { source = inp; }


// EL MERO MERO
std::string Dropfirst::getWord() {
//  while (true) {
    (*source) >> word; // here is the issue

    if (upto < word.size()){
    //  break;

  //}
    word = word.substr(upto);
    std::stringstream *ss = new std::stringstream{word};
    component->setSource(ss);
  }
  return component->getWord();
}
