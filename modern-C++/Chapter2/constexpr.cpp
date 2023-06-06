/**
 * @file constexpr.cpp
 * @author your name (you@domain.com)
 * @brief constexpr 关键字，它将表达式或函数编译为常量结果
 * 编译器能够在编译时就把这些常量表达式直接优化并植入到程序运行时，将能增加程序的性能
 * @version 0.1
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <ctime>
#include <iostream>
#include <string.h>
#include <unistd.h>

#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}

// C++11提供了
// 'constexpr'让用户显式的声明函数或对象构造函数在编译期会成为常量表达式
constexpr int len_foo_constexpr() {
    return 5;
}

// constexpr 修饰的函数可以使用递归
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    char arr_1[ 10 ];   // 合法
    char arr_2[ LEN ];  // 合法
    int  len = 10;
    // char arr_3[len]; // 非法

    const int                    len_2           = len + 1;
    constexpr int                len_2_constexpr = 1 + 2 + 3;
    constexpr unsigned long long len_2_ull       = 0x3f3f3f3f3f3f3f3f;

    // char arr_4[len_2];                // 非法
    // C++ 标准中数组的长度必须是一个常量表达式
    //对于 len_2 而言，这是一个 const 常数，而不是一个常量表达式
    //即便这种行为在大部分编译器中都支持，但是它是一个非法的行为
    char arr_4[ len_2_constexpr ];  // 合法

    char arr_5[ len_foo() + 5 ];  // 非法
    // 现在大部分编译器其实都带有自身编译优化，很多非法行为在编译器优化的加持下会变得合法，若需重现编译报错的现象需要使用老版本的编译器。
    char arr_6[ len_foo_constexpr() + 1 ];  // 合法

    std::cout << fibonacci(10) << std::endl;
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;
    return 0;
}