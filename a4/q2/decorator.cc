#include "decorator.h"

Decorator::Decorator( TextProcessor *component )
  : component{component} {}

Decorator::~Decorator() { delete component; }
