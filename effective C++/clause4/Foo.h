#pragma once

#include <string>
#include <iostream>

class Foo {
public:
    Foo(int a = 0, std::string name = "unknown") {
        _a = a;
        _name = std::move(name);
        printf("Foo(int, string) %p a:%d name:%s\n", this, _a, _name.c_str());
    }

    Foo(const Foo& other) {
        _name = other._name;
        _a = other._a;
        printf("Foo(const Foo&) SCR:%p DST:%p a:%d name:%s\n", &other, this, _a, _name.c_str());
    }

    Foo(Foo&& other)noexcept {
        _name = std::move(other._name);
        _a = other._a;
        printf("Foo(Foo &) SCR:%p DST:%p a:%d name:%s\n", &other, this, _a, _name.c_str());
    }

    Foo& operator=(Foo&& other)noexcept {
        _name = std::move(other._name);
        _a = other._a;
        printf("operator=(Foo &&) SCR:%p DST:%p a:%d name:%s\n", &other, this, _a, _name.c_str());
    }

    Foo& operator=(const Foo& other)noexcept {
        _name = other._name;
        _a = other._a;
        printf("operator=(const Foo &) SCR:%p DST:%p a:%d name:%s\n", &other, this, _a, _name.c_str());
    }

    ~Foo() {
        printf("~Foo() %p\n", this);
    }
    int  _a;
    std::string _name;
};