/**
 * @file auto.cpp
 * @author your name (you@domain.com)
 * @brief 自动类型推导
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        // 从 C++11 起, 使用 auto 关键字进行类型推导
        for(auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};

//从 C++ 20 起，auto 甚至能用于函数传参
// warning: use of 'auto' in parameter declaration only available with -fconcepts

// template 修饰的T可以匹配所有类型
// concept 修饰的T只能匹配约束的类型
//比如mult函数传入一个string，可以匹配成功，但是string并不支持multiple
int add(auto x, auto y) {
    if(std::is_same<decltype(x), int>::value)
        std::cout << "type x == int" << std::endl;
    if(std::is_same<decltype(y), int>::value)
        std::cout << "type y == int" << std::endl;
    return x + y;
}

/// @brief
/// @return
int main() {
    // 在 C++11 之前
    // 由于 cbegin() 将返回 vector<int>::const_iterator
    // 所以 it 也应该是 vector<int>::const_iterator 类型
    vector<int> vec{ 0, 1, 2, 3, 4, 5, 6 };
    std::cout << "vec: ";
    for(vector<int>::const_iterator it = vec.cbegin(); it != vec.cend(); ++it)
        cout << *it << " ";
    cout << endl;

    // 从 C++11 起, 使用 auto 关键字进行类型推导
    MagicFoo magicFoo = { 1, 2, 3, 4, 5 };
    std::cout << "MagicFoo: ";
    for(auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    //一些其他的常见用法
    auto i   = 5;             // i 被推导为 int
    auto arr = new auto(10);  // arr 被推导为 int *

    auto x = 5;  // 被推导为 int
    auto y = 6;  // 被推导为 int
    std::cout << add(x, y) << std::endl;

    // auto auto_arr2[ 10 ] = { arr };  // 错误, 无法推导数组元素类型
    // error : 'auto_arr2' declared as array of 'auto' auto auto_arr2[ 10 ] = { arr };

    return 0;
}