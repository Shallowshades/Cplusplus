/**
 * @file work2.cpp
 * @author your name (you@domain.com)
 * @brief 用折叠表达式实现用计算均值的函数
 * @version 0.1
 * @date 2022-09-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

template <typename... T>
auto average(T... t) {
    return (t + ...) / sizeof...(t);
}

template <typename... T>
auto sum(T... t) {
    return (t + ...);
}

int main() {

    std::cout << average(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    return 0;
}