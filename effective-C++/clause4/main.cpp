/**
 *@file clause4.cpp
 * @author your name (you@domain.com)
 * @brief 确定对象被使用前已经先被初始化
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <utility>
#include <string>

#include "Foo.h"

using namespace std;

class A {
public:
    explicit A(std::string name, int x = 0):_name(std::move(name)), _x(x) {
        printf("A(string):%s x:%d\n", _name.c_str(), _x);
    }

    ~A() {
        printf("~A():%s x:%d\n", _name.c_str(), _x);
    }
private:
    std::string _name;
    int _x;
};

class B {
public:
    explicit B(int v) {
        _v = v;
        printf("B(int):%d\n", v);
    }

    ~B() {
        printf("~B():%d\n", _v);
    }
public:
    int _v;
};

class C {
public:
    C(std::string aName, int bValue):_b(bValue), _a(aName, _b._v) {}
private:
    //初始化顺序和定义顺序相同，与初始化列表顺序无关
    B _b;
    A _a;
};

class Test1 {
public:
    explicit Test1(const Foo& foo) {
        _foo = foo;
    }
private:
    Foo _foo;
};

class Test2 {
public:
    explicit Test2(const Foo& foo):_foo(foo) {}
private:
    Foo _foo;
};

int main() {

    //A B C
    {
        C c("memberA", 6);
        /*
            A _a;
            B _b;

            A(string):memberA x:0
            B(int):6
            ~B():6
            ~A():memberA x:0
        */

        /*
          B _b;
          A _a;

          B(int):6
          A(string):memberA x:6
          ~A():memberA x:6
          ~B():6
        */
    }

    //Test1
    {
        Foo foo(1, "foo 1");
        Test1 test(foo);
        /*
            Foo(int, string) 0x7ffcb2934610 a:1 name:foo 1
            Foo(int, string) 0x7ffcb2934640 a:0 name:unknown
            operator=(const Foo &) SCR:0x7ffcb2934610 DST:0x7ffcb2934640 a:1 name:foo 1
            ~Foo() 0x7ffcb2934640
            ~Foo() 0x7ffcb2934610

            先构造一个对象，再拷贝
        */
    }
    //Test2
    {
        Foo foo(1, "foo 1");
        Test2 test(foo);
        /*
            Foo(int, string) 0x7ffda9793160 a:1 name:foo 1
            Foo(const Foo&) SCR:0x7ffda9793160 DST:0x7ffda9793190 a:1 name:foo 1
            ~Foo() 0x7ffda9793190
            ~Foo() 0x7ffda9793160
            调用拷贝构造函数，相比上一种，少了一步
        */
    }

    return 0;
}
