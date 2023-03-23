/**
 * @file template.cpp
 * @author your name (you@domain.com)
 * @brief C++通过模板实现不同类型不同运算，特化
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>

using namespace std;

/*
    编译期就能确定的东西既可以做类型检查，编译器也能进行优化，砍掉任何不必要的代码执行路径。
*/
template<typename T> 
class AddFloatOrMulInt{
public:
    static T Do(T a, T b){
        return T(0);
    }
};

//特化 ：1
template<>
class AddFloatOrMulInt<int>{
public:
    static int Do(int a, int b){
        return a*b;
    }
};

//特化 ：2
template<>
class AddFloatOrMulInt<float>{
public:
    static float Do(float a, float b){
        return a + b;
    }
};