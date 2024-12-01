/**
 *@file 05post.cpp
 * @author your name (you@domain.com)
 * @brief 函数返回类型后置
 * @version 0.1
 * @date 2024-11-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>

using namespace std;

int func(int x) { return x; }

// 使用时机 返回值为函数指针
auto foo() -> int(*)(int) {
    return func;
}

// 推导
template<typename T1, typename T2>
auto sum1(T1 t1, T2 t2) -> decltype(t1 + t2) {
    return t1 + t2;
}

// decltype 放在前面时,变量必须定义或者使用类型默认构造的变量(相当于临时定义)
// 编译器要求T1和T2的默认构造函数必须存在，否则会编译失败
template<typename T1, typename T2>
decltype(T1() + T2()) sum2(T1 t1, T2 t2) {
    return t1 + t2;
}

template<class T1, class T2>
decltype(*static_cast<T1*>(nullptr) + *static_cast<T2*>(nullptr)) sum3(T1 t1, T2 t2) {
    return t1 + t2;
}

// template<class T>
// T&& declval();

// 在标准库中提供了一个std::declval函数模板声明（没有具体实现），
// 它将类型T转换成引用类型，这样在使用decltype推导表达式类型时不必经过构造函数检查
template<class T1, class T2>
decltype(declval<T1>() + declval<T2>()) sum4(T1 t1, T2 t2) {
    return t1 + t2;
}

template<typename T>
void print(T t) {
    std::cout << typeid(t).name() << "\t" << t << std::endl;
}

int main() {

    print(foo()(10));
    print(sum1(10, 20.1));
    print(sum2(10L, 2));
    print(sum3(10L, 2.1));
    print(sum4(10L, 2.f));

    return 0;
}