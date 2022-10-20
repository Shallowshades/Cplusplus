/**
 * @file range.cpp
 * @author your name (you@domain.com)
 * @brief 区间for迭代
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

int main() {

    std::vector<int> vec = { 1, 2, 3, 4, 5 };

    if(auto it = std::find(vec.begin(), vec.end(), 3); it != vec.end())
        *it = 4;

    // read only
    for(auto element : vec)
        std::cout << element << " ";
    std::cout << std::endl;

    // writeable
    for(auto& element : vec)
        element += 1;

    // read only
    for(auto element : vec)
        std::cout << element << " ";
    std::cout << std::endl;

    return 0;
}