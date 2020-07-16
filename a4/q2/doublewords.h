#ifndef _DOUBLEWORDS_H_
#define _DOUBLEWORDS_H_
#include "decorator.h"
#include <vector>
#include <iostream>

class TextProcessor;
class Doublewords : public Decorator {
bool secondtime;
std::istream *source;
std::string curr;

public:
Doublewords (TextProcessor *component);
~Doublewords();
// VIRTUAL METHODS
virtual void setSource(std::istream *inp);
virtual std::string getWord();
};


#endif
