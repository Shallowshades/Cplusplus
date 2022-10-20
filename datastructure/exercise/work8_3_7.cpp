/**
 * @file 8.3.7.cpp
 * @author your name (you@domain.com)
 * @brief 荷兰国旗问题
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

// 强类型枚举 枚举类（enumeration class）类型安全
// 不能够被隐式的转换为整数, 也不能够将其与整数数字进行比较, 更不可能对不同的枚举类型的枚举值进行比较。
// 但相同枚举值之间如果指定的值相同，那么可以进行比较
enum class color : unsigned int { red = 0, wirte = 1, blue = 2 };

template <typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& os, const T& elem) {
    return os << static_cast<typename std::underlying_type<T>::type>(elem);
}

bool cmp(color a, color b) { return a < b; }

int main() {

    std::cout << color::red << std::endl;
    std::cout << color::wirte << std::endl;
    std::cout << color::blue << std::endl;
    if(color::red < color::wirte) std::cout << "true" << std::endl;
    if(color::red > color::blue) std::cout << "true" << std::endl;

    srand((unsigned int)time(0));
    std::vector<color> v;
    for(int i = 0; i < 30; i++) {
        int x = rand() % 3;
        switch(x) {

            case 0:
                v.push_back(color::red);
                break;
            case 1:
                v.push_back(color::wirte);
                break;
            case 2:
                v.push_back(color::blue);
                break;
            default:
                break;
        }
    }

    auto print = [&v]() {
        for(auto elem : v) std::cout << elem << " ";
        std::cout << std::endl;
    };

    std::cout << "before sort: ";
    print();

    // std::sort(v.begin(), v.end(), cmp);

    // 整理
    auto arrange = [&v]() {
        int i = 0, j = 0, k = v.size() - 1;
        while(j <= k) {
            switch(v[j]) {
                case color::red:
                    std::swap(v[i++], v[j++]);
                    break;
                case color::blue:
                    std::swap(v[j], v[k--]);
                    break;
                case color::wirte:
                    ++j;
                    break;
                default:
                    break;
            }
        }
    };

    arrange();

    std::cout << "after sort: ";
    print();

    return 0;
}