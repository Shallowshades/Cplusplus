/**
 * @file tuple.cpp
 * @author your name (you@domain.com)
 * @brief 结构化绑定 结构化绑定提供了类似其他语言中提供的多返回值的功能
 * @version 0.1
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

int main() {
    auto [ x, y, z ] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return 0;
}