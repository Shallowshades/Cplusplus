#include <iostream>
#include <memory>

using namespace std;

template <typename T, typename U> struct X;     // 0 原型有两个类型参数,所以下面的这些偏特化的实参列表也需要两个类型参数对应           
template <typename T>             struct X<T,  T  > {};    // 1
template <typename T>             struct X<T*, T  > {};    // 2
template <typename T>             struct X<T,  T* > {};    // 3
template <typename U>             struct X<U,  int> {};    // 4
template <typename U>             struct X<U*, int> {};    // 5
template <typename U, typename T> struct X<U*, T* > {};    // 6
template <typename U, typename T> struct X<U,  T* > {};    // 7
template <typename T>             struct X<unique_ptr<T>, shared_ptr<T>>; // 8


//原型中参数T1没有指定的地方，都由T1自己的默认参数void补齐了
template <typename T0, typename T1 = void>  struct DoWork;
template <typename T>                       struct DoWork<T> {};
template <>                                 struct DoWork<int> {};
template <>                                 struct DoWork<float> {};
template <>                                 struct DoWork<int, int> {};



int main(){

    // 以下特化，分别对应哪个偏特化的实例？
    // 此时偏特化中的T或U分别是什么类型？
    {
        X<float*,  int>  v0;                       
        X<double*, int>      v1;                       
        X<double,  double>   v2;                          
        X<float*,  double*>  v3;                           
        //X<float*,  float*>   v4;                          
        X<double,  float*>   v5;                          
        X<int,     double*>  v6;                           
        //X<int*,    int>      v7;                       
        X<double*, double>   v8;
    }

    //默认实参（Default Arguments）
    {
        DoWork<int> i;
        DoWork<float> f;
        DoWork<double> d;
        DoWork<int, int> ii;
    }
    return 0;
}