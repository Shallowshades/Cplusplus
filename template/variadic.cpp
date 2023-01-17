/**
 * @file variadic.cpp
 * @author your name (you@domain.com)
 * @brief 默认参数，不定参数
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <type_traits>
#include <complex>

using namespace std;

//同C语言的不定长参数一样，它通常只能放在参数列表的最后
//C++的模板是自左向右匹配的，所以不定长参数只能结尾。

//template <typename... Ts, typename U> class X {};                 // (1) error! 模板参数包不在参数列表结尾
template <typename... Ts>             class Y {};                   // (2)
//偏特化时，模板参数列表并不代表匹配顺序，它们只是为偏特化的模式提供的声明
//也就是说，它们的匹配顺序，只是按照<U, Ts...>来，而之前的参数只是告诉你Ts是一个类型列表，而U是一个类型，排名不分先后
template <typename... Ts, typename U> class Y<U, Ts...> {};         // (3)
//template <typename... Ts, typename U> class Y<Ts..., U> {};       // (4) error! 参数包必须是部分专用化中的最终模板参数

template<typename T>
T CustomDiv(T lhs, T rhs){
    //TODO: Custom Div implement
    return lhs/rhs;
}

template<typename T, 
bool IsFloat = std::is_floating_point<T>::value,
bool IsIntegral = std::is_integral<T>::value>
struct SafeDivide{
    static T Do(T lhs, T rhs){
        return CustomDiv(lhs, rhs);
    }
};

//偏特化A
template<typename T>
struct SafeDivide<T, true, false>{
    static T Do(T lhs, T rhs){
        return lhs/rhs;
    }
};

//偏特化B
template<typename T>
struct SafeDivide<T,false, true>{
    static T Do(T lhs, T rhs){
        if(rhs == 0){
            cout << "x/0" << endl;
            exit(-1);
        }
        return lhs/rhs;
    }
};

void foo(){
    cout << SafeDivide<float>::Do(1.0f,2.0f) << endl;//A
    cout << SafeDivide<int>::Do(1,2) << endl;//B
    cout << SafeDivide<std::complex<float>>::Do({1.f,2.f},{1.f,-2.f}) << endl; //一般形式
}

int main(){

    foo();

    return 0;
}