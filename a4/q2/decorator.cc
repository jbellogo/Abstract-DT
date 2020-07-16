#include "decorator.h"

Decorator::Decorator( TextProcessor *component )
        : component{component} {
}

Decorator::~Decorator() {
        delete component;
}

bool Decorator::stream_is_cin(std::istream *inp) {
        return (inp == &std::cin);
}

