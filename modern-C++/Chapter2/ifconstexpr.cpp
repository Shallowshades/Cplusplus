/**
 * @file ifconstexpr.cpp
 * @author your name (you@domain.com)
 * @brief
 * C++11 引入了 constexpr 关键字，它将表达式或函数编译为常量结果,
 * 把这一特性引入到条件判断中去，让代码在编译时就完成分支判断,
 * C++17 将 constexpr 这个关键字引入到 if 语句中
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

template <typename T> auto print_type_info(const T& t) {
    if constexpr(std::is_integral<T>::value)
        return t + 1;
    else
        return t + 0.001;
}

namespace temp {
    //在编译时，实际代码就会表现为如下：
    int print_type_info(const int& t) {
        return t + 1;
    }

    double print_type_info(const double& t) {
        return t + 0.001;
    }
}  // namespace temp

int main() {

    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
    return 0;
}
