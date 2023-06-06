/**
 * @file initializer_list.cpp
 * @author your name (you@domain.com)
 * @brief 初始化列表
 * @version 0.1
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <initializer_list>
#include <iostream>
#include <vector>

class MagicFoo {
public:
    std::vector<int> vec;
    //用在构造函数上
    //这种构造函数被叫做初始化列表构造函数，具有这种构造函数的类型将在初始化时被特殊关照。
    MagicFoo(std::initializer_list<int> list) {
        vec.clear();
        for(std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
            vec.push_back(*it);
    }
    //除了用在对象构造上，还能将其作为普通函数的形参
    void foo(std::initializer_list<int> list) {
        vec.clear();
        for(std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
            vec.push_back(*it);
    }
};

class Foo {
public:
    int value_a;
    int value_b;
    Foo(int a, int b) : value_a(a), value_b(b) {}
};

int main() {
    // before C++11
    int              arr[ 3 ] = { 1, 2, 3 };
    Foo              foo(1, 2);
    std::vector<int> vec = { 1, 2, 3, 4, 5 };

    std::cout << "arr[0]: " << arr[ 0 ] << std::endl;
    std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // after C++11
    // constructor function
    MagicFoo magicFoo = { 1, 2, 3, 4, 5 };
    std::cout << "magicFoo: ";
    for(std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    // conmon function
    magicFoo.foo({ 6, 7, 8, 9 });
    std::cout << "magicFoo: ";
    for(std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    // C++ 11 还提供了统一的语法来初始化任意的对象
    Foo foo2{ 3, 4 };
    std::cout << foo2.value_a << " " << foo2.value_b << std::endl;

    return 0;
}