/**
 * @file init_before_use2.cpp
 * @author your name (you@domain.com)
 * @brief 非局部变量的初始化依赖替换为函数调用结合local static对象
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

#include "Foo.h"

using namespace std;

Foo& globalFoo() {

    std::cout << "globalFoo()" << std::endl;

    static Foo globalFoo(123, "globalFoo");
    return globalFoo;
}

int main() {

    std::cout << "===main===" << std::endl;

    return 0;
}

/*
    非局部变量的初始化依赖替换为函数调用结合local static对象

    g++ init_before_use2.cpp init_before_use3.cpp && ./a.out
    Foo(int, string) 0x563580faf160 a:123 name:globalFoo
    Bar(const Foo&) foo.a=123
    ===main===
    ~Foo() 0x563580faf160

    g++ init_before_use3.cpp init_before_use2.cpp && ./a.out
    Foo(int, string) 0x55cce4c6b160 a:123 name:globalFoo
    Bar(const Foo&) foo.a=123
    ===main===
    ~Foo() 0x55cce4c6b160
*/