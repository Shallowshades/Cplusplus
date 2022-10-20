/**
 * @file forward.cpp
 * @author your name (you@domain.com)
 * @brief 完美转发
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <utility>

// std::forward 的具体实现机制
// std::forward 包含两个重载
// template <typename _Tp>
// constexpr _Tp&& forward(typename std::remove_reference(_Tp)::type& __t) noexcept {
//     return static_cast<_Tp&&>(__t);
// }
// template <typename _Tp>
// constexpr _Tp&& forward(typename std::remove_reference(_Tp)::type&& __t) noexcept {
//     static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument substituting _Tp is an lvalue reference type");
//     return static_cast<_Tp&&>(__t);
// }
// std::remove_reference 的功能是消除类型中的引用
// std::is_lvalue_reference 则用于检查类型推导是否正确

void reference(int& v) { std::cout << "left value" << std::endl; }
void reference(int&& v) { std::cout << "right value" << std::endl; }

template <typename T>
void pass1(T&& v) {
    std::cout << "common parameter\n";  //引用是一个左值
    reference(v);
}

template <typename T>
void pass2(T&& v) {
    std::cout << "common parameter: ";
    reference(v);
    //无论传递参数为左值还是右值，普通传参都会将参数作为左值进行转发

    std::cout << "std::move parameter: ";
    reference(std::move(v));
    // std::move 总会接受到一个左值，从而转发调用了reference(int&&) 输出右值引用。

    std::cout << "std::forward parameter: ";
    reference(std::forward<T>(v));
    //唯独 std::forward 即没有造成任何多余的拷贝，同时完美转发(传递)了函数的实参给了内部调用的其他函数。

    std::cout << "static_cast<T&&> parameter: ";
    reference(static_cast<T&&>(v));
}

int main() {

    //引用坍缩规则
    /*
    函数形参类型 实参参数类型 推导后函数形参类型
    T&              左引用          T&
    T&              右引用          T&
    T&&             左引用          T&
    T&&             右引用          T&&     ※
    */
    //无论模板参数是什么类型的引用，当且仅当实参类型为右引用时，模板参数才能被推导为右引用类型
    {
        std::cout << "delivery right value" << std::endl;
        pass1(1);
        std::cout << "delivery left value" << std::endl;
        int value = 1;
        pass1(value);
    }

    //所谓完美转发，就是为了让在传递参数的时候， 保持原来的参数类型（左引用保持左引用，右引用保持右引用）
    {
        std::cout << "-----------------\n";
        std::cout << "delivery right value" << std::endl;
        pass2(1);
        std::cout << "delivery left value" << std::endl;
        int value = 1;
        pass2(value);
    }

    //为什么在使用循环语句的过程中，auto&& 是最安全的方式？ 因为当 auto 被推导为不同的左右引用时，与 && 的坍缩组合是完美转发。

    return 0;
}