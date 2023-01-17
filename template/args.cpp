/**
 * @file args.cpp
 * @author your name (you@domain.com)
 * @brief 模板列表的参数
 * @version 0.1
 * @date 2023-01-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;

/*
    模板的匹配是在编译的时候完成的，所以实例化模板的时候所使用的参数，也必须要在编译期就能确定（编译期常量）

    只有整数类型可以作为模板参数


*/

//整数类型
template <int i>
class A{
public:
    void foo(int){

    }
};

//无符号整数，类(包括模板生成的类)，指针
template <uint8_t a, typename b, void* c>
class B{};

//bool常量，函数指针
template<bool, void (*a)()>
class C{};

//类的成员函数
template<void (A<3>::*a)(int)>
class D{};

//Error 浮点模板参数是非标准的C/C++
//template<float a>class E{};

//同样适用于函数
template<int i> int Add(int a){
    return a+i;
}

void foo(){

}

int main(){

    A<5> a;
    B<7,A<5>,nullptr> b;
    C<false,&foo> c;
    D<&A<3>::foo> d;
    int x = Add<3>(5);

    return 0;
}