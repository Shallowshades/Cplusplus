/**
 * @file test.cpp
 * @author your name (you@domain.com)
 * @brief const volatile mutable
 * @version 0.1
 * @date 2024-10-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
using namespace std;

/// @brief 实参不为const时, 形参为const, 此时实参可直接通过const_cast修改
/// @param val 
void test1(const int& val) {
    const_cast<int&>(val)++;
    //val++;
}

/// @brief 实参为const时, 形参也必须为const, 此时实参要带volatile才可通过const_cast修改
/// @param val
void test2(volatile const int& val) {
    const_cast<int&>(val)++;
}

class animal {
public:
    animal(int age = 1) : m_iAge(age) {}
    ~animal() = default;

    int age() const { ++counts; return m_iAge; }
    void age(int val) { m_iAge = val; }

    int count() const { return counts; }

private:
    int m_iAge = 18;
    mutable int counts = 0;
};

int main() {
    int a = 0;
    const int b = 0;

    auto f1 = [=]() {

        //a++;  // 错误，不提供说明符时复制捕获的对象在 lambda 体内是 const 的。
        //b++;  // 错误，同上，且按值传递const也会传递进来

        return a;
        };

    auto f2 = [=]() mutable {  // 提供mutable说明符
        a++;                     // 正确，mutable解除const限制。
        /*
        b++;  // 错误，mutable无法突破b本身的const限制
        */
        return a;
        };

    cout << a << ", " << b << endl;        // 输出0, 0
    cout << f1() << ", " << f2() << endl;  // 输出0, 1

    int c = 1;
    test1(c);
    std::cout << c << std::endl;

    volatile const int d = 1;
    test2(d);
    std::cout << d << std::endl;

    animal cat;
    std::cout << cat.age() << std::endl;
    std::cout << cat.count() << std::endl;

    return 0;
}