/**
 *@file 03auto.cpp
 * @author your name (you@domain.com)
 * @brief auto推导规则
 * @version 0.1
 * @date 2024-10-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <functional>
#include <assert.h>
#include <map>

using namespace std;

class Base {
public:
    virtual void f() { std::cout << "Base::f()" << std::endl; };
};

class Derived : public Base {
public:
    virtual void f() override { std::cout << "Derived::f()" << std::endl; };
};

// 3.2.4
int sum(int a1, int a2) { return a1 + a2; };

// 3.4
// 使用auto作为返回值类型
// 如果有多重返回值，那么需要保证返回值类型是相同的
auto llsum(long a1, long a2) {
    if (a1 < 0) {
        return 0;          // 返回int类型 
    }
    else {
        // return a1 + a2;    // 返回long类型  多重返回值出错
        return static_cast<int>(a1 + a2);
    }
}

// 3.6 N为非类型模板参数
template <auto N>
void func() {
    std::cout << N << std::endl;
}

int main() {

    //3.1 使用规则
    {
        // 前提: 必须给值(变量)才可推导
        {
            auto num = 5;
            //auto val;
            //val = 5;
        }

        // 1.从左到右, 类型相同
        {
            int n = 5;
            auto* pn = &n, m = 10;  // 从左往右
            //auto* pn = &n, m = 10.0; // 类型不同
        }

        // 2.编译器优先使用表达能力更强的类型
        {
            auto i = true ? 5 : 8.0;    // i的数据类型为double
            std::cout << typeid(i).name() << std::endl;
        }

        // 3.成员变量初始化
        {
            // C++11 无法声明非静态成员变量
            // C++11 可以声明静态成员变量,但必须带const
            // C++17 静态成员变量可以在没const的情况下使用
            struct sometype {
                //auto i = 5;    // 错误，无法编译通过
                //static const auto i = 5;
                //static inline auto i = 5;
            };
        }

        // 4. C++20之前无法在形参列表中使用auto, C++14可以在lambda中使用auto

        // auto也可与new结合, 例如下面,但是破坏了代码的可读性,不建议使用
        {
            auto i = new auto(5);
            auto* j = new auto(7);

            delete i;
            delete j;
        }
    }

    //3.2 推到规则
    {
        //1 按值初始化, 忽略cv限定符; 指针和引用保留cv限定符
        {
            const int i = 5;
            auto j = i;         // auto推导类型为int，而非const int
            auto& m = i;        // auto推导类型为const int，m推导类型为const int&
            auto* k = &i;       // auto推导类型为const int，k推导类型为const int*
            const auto n = j;   // auto推导类型为int，n的类型为const int
        }

        //2 auto声明时,对象是引用,则引用属性忽略
        {
            int i = 5;
            int& j = i;
            auto m = j;     // 从某种角度来说, 这就是按值初始化
            auto& n = j;    // 引用
            auto* g = &j;   // 指针

            std::cout << "Address of i : " << hex << &i << std::endl;
            std::cout << "Address of j : " << hex << &j << std::endl;
            std::cout << "Address of m : " << hex << &m << std::endl;
            std::cout << "Address of n : " << hex << &n << std::endl;
            std::cout << "Address of g : " << hex << g << std::endl;
        }

        //3 auto和&&时, 对于左值, auto会推导为引用类型
        {
            int i = 5;
            auto&& m = i;    // auto推导类型为int& （这里涉及引用折叠的概念）
            auto&& j = 5;    // auto推导类型为int
            std::cout << typeid(m).name() << std::endl;
            std::cout << typeid(j).name() << std::endl;
        }

        //4 auto声明对于数组和函数时, auto会推导成对应指针类型
        {
            int i[5];
            auto m = i;         // auto推导类型为int*
            auto j = sum;       // auto推导类型为int (__cdecl *)(int,int)
        }

        //5 auto与初始化列表
        {
            auto x1 = { 1, 2 };      // x1类型为 std::initializer_list<int>
            //auto x2 = { 1, 2.0 };    // 编译失败，花括号中元素类型不同
            //auto x3{ 1, 2 };         // 编译失败，不是单个元素
            auto x4 = { 3 };         // x4类型为std::initializer_list<int>
            auto x5{ 3 };            // x5类型为int
        }

        // auto 和 class
        {
            Base* d = new Derived();
            auto b = *d;    // 按值赋值 Derived被切割成了Base
            b.f();
            std::cout << typeid(b).name() << std::endl;

            auto& b1 = *d;  // 引用*d Derived
            b1.f();
            std::cout << typeid(b1).name() << std::endl;

            auto* b2 = d;   // 使用指针的值, 为Base指针, 实质为Derived
            b2->f();
            std::cout << typeid(b2).name() << std::endl;
            std::cout << typeid(*b2).name() << std::endl;
        }
    }

    //3.3 使用时机
    //1．当一眼就能看出声明变量的初始化类型的时候可以使用auto。
    //2．对于复杂的类型，例如lambda表达式、bind等直接使用auto
    {
        std::map<std::string, int> str2int;
        // 下面两种遍历形式建议使用auto
        for (std::map<std::string, int>::const_iterator it = str2int.cbegin(); it != str2int.cend(); ++it) {}
        for (std::pair<const std::string, int>& it : str2int) {}

        // lambda表达式 
        auto iisum = [](int a1, int a2) { return a1 + a2; };
        auto iisum5x = bind(sum, 5, std::placeholders::_1);
        auto iisumx5 = bind(sum, std::placeholders::_1, 5);
        std::cout << iisum5x(6) << std::endl;
        std::cout << iisumx5(3) << std::endl;

    }

    //3.4 返回类型推导
    {

    }

    //3.5 lambda表达式使用auto类型推导 C++14
    {
        // 相当于泛型
        {
            auto l = [](auto a1, auto a2) { return a1 + a2; };
            auto retval = l(5, 5.0);
        }

        // 返回auto&
        {
            auto l = [](int& i)->auto& { return i; };
            auto x1 = 5;
            auto& x2 = l(x1);
            assert(&x1 == &x2);    // 有相同的内存地址
        }

    }

    //3.6 非类型模板形参占位符
    //模板参数的类型要求
    //‌类型模板参数‌：可以是任何类型，包括自定义类型、内置类型（如int、double）等。
    //非类型模板参数‌：必须是编译时常量，通常使用整数常量（如int），不能使用浮点数（如double）。
    {
        func<5>();      // int
        func<'c'>();    // char
        // f<5.0>();    // 不能为double
    }

    return 0;
}