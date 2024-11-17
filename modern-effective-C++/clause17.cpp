/**
 * @file clause17.cpp
 * @author your name (you@domain.com)
 * @brief 特种成员函数的生成机制
 * @version 0.1
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <algorithm>

using namespace std;

/*
    三五法则
    三 : 析构函数, 拷贝构造, 拷贝赋值构造
    五 : 移动构造, 移动赋值构造

    当书写析构函数时, 则不提供拷贝操作
    当书写任一析构, 拷贝操作, 移动操作时, 则不提供移动操作

    书写任一构造, 则不提供默认构造
 */


class Top {
public:
    Top() { std::cout << "Top Ctor" << std::endl; };
    virtual ~Top() { std::cout << "Top Dtor" << std::endl; };

    virtual void func() = 0;
};

class Base : public Top {
public:
    Base() { std::cout << "Base Ctor" << std::endl; }
    virtual ~Base() { std::cout << "Base Dtor" << std::endl; }

    virtual void func() override { std::cout << "Base func" << std::endl; }
};

class Drived : public Base {
public:
    Drived() { std::cout << "Drived Ctor" << std::endl; }
    virtual ~Drived() { std::cout << "Drived Dtor" << std::endl; }

    virtual void func() override { std::cout << "Drived func" << std::endl; }
};

int main() {

    {
        Base* b = new Drived();
        b->func();
        delete b;
    }

    return 0;
}