/**
 *@file init_before_use.cpp
 * @author your name (you@domain.com)
 * @brief 非局部变量的初始化顺序问题
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

#include "Foo.h"

using namespace std;

//全局变量初始化早于main函数
Foo globalFoo(123, "globalFoo");

int main() {

    std::cout << "===main===" << std::endl;

    return 0;
}

/*
    1.不同的编译器得到的结果不同
    2.不同的编译顺序，得到的结果不同

    g++ init_before_use.cpp  init_before_use1.cpp && ./a.out
    Foo(int, string) 0x563e4edbf140 a:123 name:globalFoo
    Bar(const Foo&) foo.a=123
    ===main===
    ~Foo() 0x563e4edbf140

    g++ init_before_use1.cpp  init_before_use.cpp && ./a.out
    Bar(const Foo&) foo.a=0
    Foo(int, string) 0x55631d907140 a:123 name:globalFoo
    ===main===
    ~Foo() 0x55631d907140
*/