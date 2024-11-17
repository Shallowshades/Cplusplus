/**
 *@file 04decltype.cpp
 * @author your name (you@domain.com)
 * @brief 类型推导
 * @version 0.1
 * @date 2024-11-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <initializer_list>

int main() {

    //typeid
    {
        int x1 = 0;
        double x2 = 5.5;
        std::cout << typeid(x1).name() << std::endl;
        std::cout << typeid(x1 + x2).name() << std::endl;
        std::cout << typeid(int).name() << std::endl;
    }

}