/**
 *@file deduced.cpp
 * @author your name (you@domain.com)
 * @brief IDE提示，编译错误提示，typeid&boost查看推导类型
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
using ull = unsigned long long;

template<typename T>
auto func1(T x, T y) -> decltype(x* y) {
    return x * y;
}

int main() {

    const int x = 2;
    //int& y = x; 
    //将 "int &" 类型的引用绑定到 "const int" 类型的初始值设定项时，限定符被丢弃
    auto y = x; //auto -> int 相当于值初始化
    auto& z = x; //auto -> const int,引用不能丢弃限定符
    auto t = &x; //auto -> const int*,指针指向的内容不能被修改

    func1(x, y);

    vector<int> v(10, 1);
    auto length = v.size();

    return 0;
}
