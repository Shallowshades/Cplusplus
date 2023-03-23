/**
 * @file error.cpp
 * @author your name (you@domain.com)
 * @brief 名称查找/名称解析
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;

template<typename T>
struct X{};

template <typename T>
struct Y{
    //X可以查找到原型；
    // X<T>是一个依赖性名称，模板定义阶段并不管X<T>是不是正确的。
    typedef X<T> ReboundType;

    // X可以查找到原型；
    // X<T>是一个依赖性名称，X<T>::MemberType也是一个依赖性名称；
    // 所以模板声明时也不会管X模板里面有没有MemberType这回事。
    typedef typename X<T>::MemberType MemberType;

    // UnknownType 不是一个依赖性名称
    // 而且这个名字在当前作用域中不存在，所以直接报错。
    //typedef UnknownType MemberType3;

    void foo(){
        X<T> instance0;
        typename X<T>::MemberType instance1;
        //WTF instance2;
    }
};

int a;
struct B{int v;};
template<typename T>
struct Z{
    B b;// B 是第三类名字，b 是第一类
    T t;// T 是第二类
    Z* anthor;// X 这里代指 X<T>，第一类
    typedef int Y;// int 是第三类
    Y y;// Y 是第一类
    //C c; // C 什么都不是，编译错误。

    void foo(){
        b.v += y;// b 是第一类，非依赖性名称
        b.v *= T::s_mem;// T::s_mem 是第二类
                        // s_mem的作用域由T决定
                        // 依赖性名称，类型依赖
    }
};



int main() {



    return 0;
}