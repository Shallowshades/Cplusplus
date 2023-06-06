/**
 * @file variable.cpp
 * @author your name (you@domain.com)
 * @brief 变量声明强化
 * @version 0.1
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = { 1, 2, 3, 4 };

    // 在 c++17 之前
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if(itr != vec.end()) {
        *itr = 3;
    }

    // 需要重新定义一个新的变量
    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if(itr2 != vec.end()) {
        *itr2 = 4;
    }

    // 将输出 1, 4, 3, 4
    for(std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
        std::cout << *element << std::endl;

    // C++ 17 允许在if、switch的括号内，像for一样定义局部变量
    // 将临时变量放到 if 语句内
    if(const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
        *itr = 4;
    }

    return 0;
}