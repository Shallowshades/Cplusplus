/**
 * @file match.cpp
 * @author your name (you@domain.com)
 * @brief 只使用一个条件量分派
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <complex>
#include <type_traits>
#include <vector>

template <typename T>
T CustomDiv(T lhs, T rhs){
    return lhs/rhs;
}

//原型
template <typename T, typename Enabled = std::true_type>
class SafeDivide{
public:
    static T Do(T lhs, T rhs){
        return CustomDiv(lhs, rhs);
    }
};

//偏特化A
template<typename T> 
class SafeDivide<T, typename std::is_floating_point<T>::type>{
public:
    static T Do(T lhs, T rhs){
        return CustomDiv(lhs, rhs);
    }
};

//偏特化B
template <typename T>
class SafeDivide<T, typename std::is_integral<T>::type>{
public:
    static T Do(T lhs, T rhs){
        return rhs == 0 ? 0 : lhs/rhs;
    }
};

void foo(){
    std::cout << SafeDivide<float>::Do(1.0f,2.0f) << std::endl;
    std::cout << SafeDivide<int>::Do(1,2) << std::endl;
    std::cout << SafeDivide<std::complex<float>>::Do({1.f,2.f},{1.f,-2.f}) << std::endl;
}

struct X {
    typedef float type;
};

struct Y {
    typedef float type2;
};

//传入类型
template <typename T, typename U>
void foo(T t, typename U::type u) {
    // ...
    std::cout <<"t = "<<t<<std::endl;
    std::cout <<"u = "<<u<<std::endl;
}

//+++ foo<int,Y>可以匹配成功
template <typename T, typename U>
void foo(T t, typename U::type2 u) {
    // ...
    std::cout <<"t = "<<t<<std::endl;
    std::cout <<"u = "<<u<<std::endl;
}

//这种只要有正确的候选，就无视替换失败的做法为SFINAE。
//替换失败并非错误(Substitution Failure Is Not An Error)
void callFoo() {
    foo<int, X>(5, 5.0); // T == int, typename U::type == X::type == float
    foo<int,Y>(5,5.0); //no type named ‘type’ in ‘struct Y’，
}

template<typename T, typename U = typename std::vector<T>::iterator>
typename std::vector<T>::value_type //需要替换的部分
foo(
    T*,//需要替换的部分
    T&,//需要替换的部分
    typename T::internal_type,//需要替换的部分
    //typename add_reference<T>::type, //需要替换的部分
    int
){
    // 根据定义，substitution只发生在函数签名上。
    // 故而整个函数实现部分都不会存在 substitution。
    // 这是一个重点需要记住。
}

namespace test{
    struct X{ 
        typedef int type;
    };

    struct Y{
        typedef int type2;
    };

    template<typename T> void foo(typename T::type) {};//0
    template<typename T> void foo(typename T::type2) {};//1
    template<typename T> void foo(T) {};//2

    void callFoo(){
                        //0     1       2
        foo<X>(5);      //√     ×       ×    
        foo<Y>(10);     //×     √       ×
        foo<int>(15);   //×     ×       √
    }
} 


int main(){

    foo();
    callFoo();
    test::callFoo();

    return 0;
}