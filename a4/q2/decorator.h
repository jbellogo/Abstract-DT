#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "textprocess.h"
#include <vector>

class Decorator : public TextProcessor {
protected:
TextProcessor *component;
std::vector <std::string> vecin;

public:
Decorator( TextProcessor *component );
bool stream_is_cin(std::istream *inp);

virtual ~Decorator();
};


#endif
