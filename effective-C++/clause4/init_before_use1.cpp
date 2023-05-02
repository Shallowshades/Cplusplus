#include <iostream>

#include "Foo.h"

extern Foo globalFoo;

class Bar {
public:
    explicit Bar(const Foo& foo) {
        std::cout << "Bar(const Foo&) foo.a=" << foo._a << std::endl;
    }
};

Bar bar(globalFoo);
