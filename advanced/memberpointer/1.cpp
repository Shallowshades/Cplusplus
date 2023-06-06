#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
    operator .* 不可以重载
    operator ->* 可以重载
*/

struct X {
    void f() {
        std::cout << "void" << std::endl;
    }

    void f(int) {
        std::cout << "int" << std::endl;
    }

    template<typename Ty>
    auto operator ->* (Ty v) {
        return (this->*v)();
    }

    int x = 1;
};

void f1(void(X::* p)(), X* x) {
    (x->*p)();
}

void f2(void(X::* p)(int), X* x, int n) {
    (x->*p)(n);
}

void f3(int X::* v, X* x) {
    (x->*v) = 66;
}

struct Test_bind {
    void t(int n) {
        for (;n;n--) {
            std::cout << "func t" << std::endl;
        }
    }
    void t() {
        std::cout << "overload func t()\n";
    }
};

int main() {

    //基础语法
    void(X:: * p)() = &X::f;
    X x;
    (x.*p)();

    f1(&X::f, &x);
    f2(&X::f, &x, 5);
    //x->*& X::f; 没有与这些操作数匹配的 "->*" 运算符

    int X::* y = &X::x;
    std::cout << x.x << "\n";
    int& v = (x.*y);
    v = 100;
    std::cout << x.x << std::endl;

    f3(&X::x, &x);
    std::cout << x.x << std::endl;


    Test_bind t_b;
    auto n = std::bind(static_cast<void(Test_bind::*)(int)>(&Test_bind::t), &t_b, 3);
    n();
    return 0;
}
