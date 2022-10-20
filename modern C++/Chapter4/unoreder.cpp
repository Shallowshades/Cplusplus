/**
 * @file unoreder.cpp
 * @author your name (you@domain.com)
 * @brief 无序容器
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main() {

    {
        // 两组结构按同样的顺序初始化
        std::unordered_map<int, std::string> u = { { 1, "1" }, { 3, "3" }, { 2, "2" } };
        std::map<int, std::string>           v = { { 1, "1" }, { 3, "3" }, { 2, "2" } };

        // 分别对两组结构进行遍历
        std::cout << "std::unordered_map" << std::endl;
        for(const auto& n : u) std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

        std::cout << std::endl;
        std::cout << "std::map" << std::endl;
        for(const auto& n : v) std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    {
        // 两组结构按同样的顺序初始化
        std::unordered_map<int, std::string> u = { { 1, "1" }, { 3, "3" }, { 2, "2" } };
        std::map<int, std::string>           v = { { 1, "1" }, { 3, "3" }, { 2, "2" } };

        // 分别对两组结构进行遍历
        std::cout << "std::unordered_map" << std::endl;
        for(auto&& n : u) std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

        std::cout << std::endl;
        std::cout << "std::map" << std::endl;
        for(auto&& n : v) std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    return 0;
}