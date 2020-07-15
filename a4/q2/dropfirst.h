#ifndef _DROPFIRST_H_
#define _DROPFIRST_H_
#include "decorator.h"

class TextProcessor;

class Dropfirst : public Decorator {
  std::istream *source;
  int upto;
  std::string word;
  
public:
  Dropfirst (TextProcessor *component, int n);
  // VIRTUAL METHODS
  virtual void setSource(std::istream *inp);
  virtual std::string getWord();
};


#endif
