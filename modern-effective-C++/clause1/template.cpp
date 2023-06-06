/**
 *@file template.cpp
 * @author your name (you@domain.com)
 * @brief 模板推导
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

const char* TypeToName(const char* name) {
    const char* __name = abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
    return __name;
}

template <typename T>
void f(T& param) {
    std::cout << TypeToName(typeid(param).name()) << std::endl;
}

void func(int x, double y) {
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

template <typename T>
void f1(T param) {
    std::cout << TypeToName(typeid(param).name()) << std::endl;
    param(1, 1.1);
}

template <typename T>
void f2(T& param) {
    std::cout << TypeToName(typeid(param).name()) << std::endl;
    param(2, 2.2);
}

int main() {

    int x = 0;
    const int cx = x;
    const int& rx = x;

    f(x);
    f(cx);
    f(rx);

    auto func1 = [](int x, double y) {
        std::cout << "lambda" << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    };

    auto func2 = [](int x, float y) {
        std::cout << "lambda" << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    };

    f1(func1);
    f2(func2);

    auto list = { 1,2,3 };

    return 0;
}
