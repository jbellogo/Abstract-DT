#include "dropfirst.h"
#include "textprocess.h"
using std::string;
#include <sstream>
using std::cin;
/*
   std::istream *source;
   int upto;
   std::string word;
 */
Dropfirst::Dropfirst (TextProcessor *component, int n) :
        Decorator{component},
        upto{n}{
}

// VIRTUAL METHODS
void Dropfirst::setSource(std::istream *inp) {
        source = inp;
}


std::string Dropfirst::getWord() {
        while (true) {
                component->setSource(source);
                word = component->getWord();
                if (upto < word.size()) {
                        break;
                }
        }
        word = word.substr(upto);
        return word;
}
