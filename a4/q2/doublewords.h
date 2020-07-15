#ifndef _DOUBLEWORDS_H_
#define _DOUBLEWORDS_H_
#include "decorator.h"

class TextProcessor;
class Doublewords : public Decorator {
  /* This?? */
  std::istream *source;
  bool secondtime;
  std::string word_to_reap;
public:
  Doublewords (TextProcessor *component);
  ~Doublewords();
  // VIRTUAL METHODS
  virtual void setSource(std::istream *inp);
  virtual std::string getWord();
};


#endif
