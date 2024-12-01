/**
 *@file 02namespace.cpp
 * @author your name (you@domain.com)
 * @brief 命名空间
 * @version 0.1
 * @date 2024-11-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <limits>

using namespace std;

// 内联导入到父命名空间 唯一 否则会造成二义性
namespace Parent {
    namespace V1 { void foo() { std::cout << "foo v1.0" << std::endl; } }
    inline namespace V2 { void foo() { std::cout << "foo v2.0" << std::endl; } }
}

// 嵌套命名空间
namespace A::B::C {
    int foo() { return 5; }
}

int main() {

    Parent::foo();

    return 0;
}