/**
 * @file refer.cpp
 * @author your name (you@domain.com)
 * @brief 左值，右值，纯右值、将亡值
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

/**
 * @brief
 * static_assert
 * 在编译时求值该常量表达式并将它与零比较。
 * 若它比较等于零，则发生编译错误，
 * 而若提供消息 ，则编译器必须将它作为错误消息的一部分显示
 * （除了不要求显示基本源码字符集以外的字符）。
 * 否则，若表达式 不等于零，则什么都不发生；不生成代码
 */

void func_assert() {

    // 测试数学是否正常工作
    static_assert(2 + 2 == 4, "Whoa dude!");  // 或 _Static_assert(...

    // 这会在编译时产生错误。
    static_assert(sizeof(int) > sizeof(char), "this program requires that int is less than char");
}

vector<int> foo() {
    vector<int> tmp = { 1, 2, 3, 4 };
    return tmp;
}

void reference(std::string& str) { std::cout << "left value" << std::endl; }
void reference(std::string&& str) { std::cout << "right value" << std::endl; }

void increase(int& v) { v++; }

int main() {

    // 左值，右值，纯右值、将亡值
    {
        // 正确，"01234" 类型为 const char [6]，因此是左值
        const char(&left)[6] = "01234";

        // 断言正确，确实是 const char [6] 类型，注意 decltype(expr) 在 expr 是左值
        // 且非无括号包裹的 id 表达式与类成员表达式时，会返回左值引用
        static_assert(is_same<decltype("01234"), const char(&)[6]>::value, "");

        // 错误，"01234" 是左值，不可被右值引用
        // const char (&&right)[6] = "01234";

        //数组可以被隐式转换成相对应的指针类型，而转换表达式的结果（如果不是左值引用）则一定是个右值（右值引用为将亡值，否则为纯右值）
        const char*   p  = "01234";  // 正确，"01234" 被隐式转换为 const char*
        const char*&& pr = "01234";  // 正确，"01234" 被隐式转换为 const char*，该转换的结果是纯右值
        // const char*& pl = "01234"; // 错误，此处不存在 const char* 类型的左值
    }

    //将亡值
    //将亡值(xvalue, expiring value)，是 C++11 为了引入右值引用而提出的概念（因此在传统 C++中， 纯右值和右值是同一个概念），也就是即将被销毁、却能够被移动的值。
    //将亡值就定义了这样一种行为：临时的值能够被识别、同时又能够被移动。
    //在 C++11之后，编译器为我们做了一些工作，此处的左值 temp 会被进行此隐式右值转换，
    //等价于 static_cast<vector<int>&&>(temp)，进而此处的 v 会将 foo 局部返回的值进行移动。 也就是移动语义。
    { vector<int> v = foo(); }

    //右值引用的声明让这个临时值的生命周期得以延长、只要变量还活着，那么将亡值将继续存活。
    {
        //不可同名
        // auto reference = [](string& str) { cout << "左值" << endl; };
        // auto reference = [](string&& str) { cout << "右值" << endl; };

        string lv1 = "string,";  // lv1 是一个左值
        // string&& r1 = lv1;      // 非法, 右值引用不能引用左值
        string&& rv1 = move(lv1);  // 合法, move可以将左值转移为右值
        cout << rv1 << endl;       // string,
        reference(lv1);

        const string& lv2 = lv1 + lv1;  // 合法, 常量左值引用能够延长临时变量的生命周期
        // lv2 += "Test"; // 非法, 常量引用无法被修改
        cout << lv2 << endl;  // string,string,

        string&& rv2 = lv1 + lv2;  // 合法, 右值引用延长临时对象生命周期
        rv2 += "Test";             // 合法, 非常量引用能够修改临时变量
        cout << rv2 << endl;       // string,string,string,Test

        reference(rv2);  // 输出左值

        // rv2 虽然引用了一个右值，但由于它是一个引用，所以 rv2 依然是一个左值。
    }

    //一个遗留问题
    {
        // int &a = std::move(1);    // 不合法，非常量左引用无法引用右值
        const int& b = std::move(1);  // 合法, 常量左引用允许引用右值

        // 1.
        double s = 1;
        // increase(s);
        // error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
        cout << "s = " << s << endl;

        //不允许非常量引用绑定到非左值
        //逻辑错误：由于 int& 不能引用 double 类型的参数，因此必须产生一个临时值来保存s的值，
        //从而当 increase() 修改这个临时值时，调用完成后s本身并没有被修改。

        //为什么常量引用允许绑定到非左值？原因很简单，因为 Fortran需要   ???
    }

    return 0;
}