/**
 * @file decltype.cpp
 * @author your name (you@domain.com)
 * @brief 为了解决 auto 关键字只能对变量进行类型推导的缺陷（以及尾返回类型推导）, 用法和 typeof 很相似
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

// auto 不能用于函数形参进行类型推导
// typename 和 class 在模板参数列表中没有区别，在 typename 这个关键字出现之前，都是使用 class 来定义模板参数的。
// 但在模板中定义有嵌套依赖类型的变量时，需要用 typename 消除歧义

// 代码丑陋,在使用这个模板函数的时候，必须明确指出返回类型
// 事实上在使用时并不知道 add() 这个函数会做什么样的操作，以及获得一个什么样的返回类型。
template <typename R, typename T, typename U> R add(T x, U y) {
    return x + y;
}

//不能通过编译
//在编译器读到 decltype(x+y) 时，x 和 y 尚未被定义。
// template <typename T, typename U> decltype(x + y) add1(T x, U y) {
//     return x + y;
// }

//为了解决这个问题，C++11引入了一个叫做尾返回类型（trailing return type），利用 auto 关键字将返回类型后置
template <typename T, typename U> auto add2(T x, U y) -> decltype(x + y) {
    return x + y;
}

//从 C++14 开始是可以直接让普通函数具备返回值推导
template <typename T, typename U> auto add3(T x, U y) {
    return x + y;
}

struct Point {
    float x;
    float y;

    auto size() const -> int {
        return 2;
    }

    // wonderful
    auto operator[](int i) const -> float {
        return i == 0 ? x : y;
    }
};

int main() {

    {
        auto            x = 1;
        auto            y = 2;
        decltype(x + y) z = 3.14;

        std::cout << "Z = " << z << std::endl;

        if(std::is_same<decltype(x), int>::value)
            std::cout << "type x == int" << std::endl;
        if(std::is_same<decltype(y), double>::value)
            std::cout << "type y == double" << std::endl;
        if(std::is_same<decltype(z), int>::value)
            std::cout << "type z == int" << std::endl;
    }

    {
        //所有位置的参数类型都要指定
        double t = add<double, int, float>(1, 1.0f);
        std::cout << "t: " << t << std::endl;

        // after c++11
        std::cout << "C++11" << std::endl;
        auto w = add2<int, double>(1, 2.0);
        if(std::is_same<decltype(w), double>::value) {
            std::cout << "w is double: ";
        }
        std::cout << "w: " << w << std::endl;

        // after c++14
        std::cout << "C++14" << std::endl;
        auto q = add3<double, int>(1.0, 2);
        std::cout << "q: " << q << std::endl;
    }

    return 0;
}