/**
 * @file work.cpp
 * @author your name (you@domain.com)
 * @brief 用模板做一个对照表，让类型对应上一个数字
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

const char* TypeToName(const char* name) {
    return abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
}

template<typename T>
class TypeToID{
public:
    static const int ID = -1;
};

template<>
class TypeToID<uint8_t>{
public:
    static const int ID = 0;   
};

template<>
class TypeToID<uint16_t>{
public:
    static const int ID = 1;   
};

template<>
class TypeToID<uint32_t>{
public:
    static const int ID = 2;   
};

template<>
class TypeToID<uint64_t>{
public:
    static const int ID = 3;   
};

template<>
class TypeToID<float>{
public:
    static const int ID = 4;   
};

template<>
class TypeToID<double>{
public:
    static const int ID = 5;   
};

template<>
class TypeToID<string>{
public:
    static const int ID = 6;   
};

//模板是从最特殊到最一般形式进行匹配的

//偏特化 指针匹配
template<typename T>
class TypeToID<T*>{
public:
    typedef T SameAsT;
    static const int ID = 0x80000000;
};

template<>
class TypeToID<int*>{
public:
    static const int ID = 0x00000001;
};

template<typename T>
ostream& operator << (ostream& os, const TypeToID<T>& type){
    os << "ID of " << TypeToName(typeid(type).name());
    os << ": " << TypeToID<T>::ID;
    return os;
}

void method1(){
    TypeToID<uint8_t> u8;
    TypeToID<uint16_t> u16;
    TypeToID<uint32_t> u32;
    TypeToID<uint64_t> u64;
    TypeToID<float> f;
    TypeToID<double> d;
    TypeToID<string> s;

    cout << u8 << endl;
    cout << u16 << endl;
    cout << u32 << endl;
    cout << u64 << endl;
    cout << f << endl;
    cout << d << endl;
    cout << s << endl;
}

void method2(){
    cout << "ID of uint8_t: " << TypeToID<uint8_t>::ID << endl;
    cout << "ID of uint16_t: " << TypeToID<uint16_t>::ID << endl;
    cout << "ID of uint32_t: " << TypeToID<uint32_t>::ID << endl;
    cout << "ID of uint64_t: " << TypeToID<uint64_t>::ID << endl;
    cout << "ID of float: " << TypeToID<float>::ID << endl;
    cout << "ID of double: " << TypeToID<double>::ID << endl;
    cout << "ID of string: " << TypeToID<string>::ID << endl;
}

int main(){

    method1();
    method2();

    cout << "ID of double*: " << TypeToID<double*>::ID << endl;
    cout << "ID of int*: " << TypeToID<int*>::ID << endl;

    return 0;
}