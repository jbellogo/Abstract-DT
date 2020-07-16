#ifndef _DOUBLEWORDS_H_
#define _DOUBLEWORDS_H_
#include "decorator.h"
#include <vector>

class TextProcessor;
class Doublewords : public Decorator {
  std::istream *source;
  //std::iostream *source; /// TEST
  bool secondtime;
  std::string curr;
  std::vector <std::string> vec;
public:
  Doublewords (TextProcessor *component);
  ~Doublewords();
  // VIRTUAL METHODS
  virtual void setSource(std::istream *inp);
  virtual std::string getWord();
};


#endif
