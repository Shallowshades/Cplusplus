#include <iostream>

using namespace std;

void fun(const int& v) {
    int& type_int_ref = const_cast<int&>(v);
    type_int_ref      = 10;
}

int main() {

    // 错误示例，直接用于变量、不同类型转换
    {
        int type_int = 100;
        // float  type_float     = const_cast<float>(type_int);    // 错误，const_cast只能转换引用或者指针
        // float* type_float_ptr = const_cast<float*>(&type_int);  // 错误，从int* -> float* 无效
        // float& type_float_ref = const_cast<float&>(type_int);   // 错误，从int& -> float& 无效
    }

    // 不是很正确的用法
    // 本体并未改变
    {
        const int type_const_int     = 100;
        int*      type_const_int_ptr = const_cast<int*>(&type_const_int);  // 转换正确
        int&      type_const_int_ref = const_cast<int&>(type_const_int);   // 转换正确

        *type_const_int_ptr = 10;
        cout << *type_const_int_ptr << endl;  // 输出10
        cout << type_const_int << endl;       // 输出100，没有改变

        type_const_int_ref = 20;
        cout << type_const_int_ref << endl;  // 输出20
        cout << type_const_int << endl;      // 输出100，没有改变

        // 以下三个输出结果一致，说明const_cast确实只是去除了一些属性，并没有重新搞快内存把需要转换的变量给复制过去
        cout << "&type_const_int:\t" << &type_const_int << endl;
        cout << "type_const_int_ptr:\t" << type_const_int_ptr << endl;
        cout << "&type_const_int_ref:\t" << &type_const_int_ref << endl;
    }

    // 主要用法
    // 如果一个变量本来就不具备const属性，但是在传递过程中被附加了const属性，这时候使用const_cast就能完美清除掉后面附加的那个const属性了。
    {
        int type_int = 100;

        fun(type_int);
        cout << type_int << endl;  // 输出10，改变了
    }
    return 0;
}