/**
 * @file lambda.cpp
 * @author your name (you@domain.com)
 * @brief lambda
 * @version 0.1
 * @date 2022-10-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

/* 语法
[捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
// 函数体
}
*/

int main() {

    /*
    获列表的最常用的四种形式可以是：
    [] 空捕获列表
    [name1, name2, ...] 捕获一系列变量
    [&] 引用捕获, 让编译器自行推导引用列表
    [=] 值捕获, 让编译器自行推导值捕获列表
    */

    //值捕获、引用捕获都是已经在外层作用域声明的变量，因此这些捕获方式捕获的均为左值，而不能捕获右值。
    // 1.值捕获
    {
        int  value        = 1;
        auto copy_value   = [value] { return value; };
        value             = 100;
        auto stored_value = copy_value();
        cout << "store_value = " << stored_value << endl;
        // 这时, stored_value == 1, 而 value == 100.
        // 因为 copy_value 在创建时就保存了一份 value 的拷贝
    }

    // 2.引用捕获
    {
        int  value        = 1;
        auto copy_value   = [&value] { return value; };
        value             = 100;
        auto stored_value = copy_value();
        cout << "store_value = " << stored_value << endl;
        // 这时, stored_value == 100, value == 100.
        // 因为 copy_value 保存的是引用
    }

    // 3.隐式捕获
    {
        int  value        = 1;
        auto copy_value   = [=] { return value; };
        value             = 100;
        auto stored_value = copy_value();
        cout << "store_value = " << stored_value << endl;
    }

    {
        int  value        = 1;
        auto copy_value   = [&] { return value; };
        value             = 100;
        auto stored_value = copy_value();
        cout << "store_value = " << stored_value << endl;
    }

    // C++14允许捕获的成员用任意的表达式进行初始化，这就允许了右值的捕获， 被声明的捕获变量类型会根据表达式进行判断，判断方式与使用 auto 本质上是相同的
    // 4.表达式捕获
    {
        auto important = std::make_unique<int>(1);
        auto add       = [v1 = 1, v2 = std::move(important)](int x, int y) -> int { return x + y + v1 + (*v2); };
        cout << "add(3,4) = " << add(3, 4) << endl;
        // cout << "important = " << *important << endl;//error

        // important 是一个独占指针，是不能够被 "=" 值捕获到，这时候可以将其转移为右值，在表达式中初始化
    }

    //泛型 Lambda
    {
        // auto 关键字不能够用在参数表里，这是因为这样的写法会与模板的功能产生冲突
        //但是 Lambda 表达式并不是普通函数，所以在没有明确指明参数表类型的情况下，Lambda 表达式并不能够模板化
        //从C++14开始，Lambda 函数的形式参数可以使用 auto 关键字来产生意义上的泛型
        auto add  = [](auto x, auto y) -> auto{ return x + y; };
        auto add1 = [](auto x, auto y) -> decltype(x + y) { return x + y; };
        cout << add(1, 2) << endl;
        cout << add(1.1, 2.2) << endl;
        cout << add(1, 1.444) << endl;
        cout << add1(1, 1.444) << endl;
    }

    //函数对象包装器（增强了 C++ 语言运行时的能力）
    // Lambda 表达式的本质是一个和函数对象类型相似的类类型（称为闭包类型）的对象（称为闭包对象），
    //当 Lambda 表达式的捕获列表为空时，闭包对象还能够转换为函数指针值进行传递
    {
        using foo = void(int);  // 定义函数类型, using 的使用,别名语法

        // 参数列表中定义的函数类型 foo 被视为退化后的函数指针类型 foo*
        auto function = [](foo f) -> void {
            f(1);  // 通过函数指针调用函数
        };
        auto f = [](int value) -> void { cout << value << endl; };
        function(f);  // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
        f(1);         // lambda 表达式调用

        //一种是将Lambda作为函数类型传递进行调用，
        // 而另一种则是直接调用Lambda表达式
        //在C++11中，统一了这些概念，将能够被调用的对象的类型，统一称之为可调用类型。而这种类型，便是通过"std::function"引入的。
    }

    {
        // C++11 std::function 是一种通用、多态的函数封装， 它的实例可以对任何可以调用的目标实体进行存储、复制和调用操作， 它也是对 C++
        // 中现有的可调用实体的一种类型安全的包裹（相对来说，函数指针的调用不是类型安全的）， 换句话说，就是函数的容器。当有了函数的容器之后便能够更加方便的将函数、函数指针作为对象进行处理。
        int                                   out   = 100;
        int                                   out1  = 20;
        int                                   out2  = 30;
        auto                                  foo   = [](int para) -> int { return para; };
        auto                                  add   = [](auto x, auto y) -> decltype(x + y) { return x + y; };
        std::function<int(int)>               func  = foo;
        std::function<int(int)>               func2 = [&](int value) -> int { return 1 + value + out; };
        std::function<int(int, int)>          add1  = add;
        std::function<double(double, double)> add2  = add;

        cout << func(10) << endl;
        cout << func2(10) << endl;
        cout << add1(out1, out2) << endl;
        cout << add2(1.23, 2.34) << endl;
    }

    // std::bind 和 std::placeholder
    // std::bind 则是用来绑定函数调用的参数的，
    // 它解决的需求是有时候可能并不一定能够一次性获得调用某个函数的全部参数，通过这个函数，可以将部分调用参数提前绑定到函数身上成为一个新的对象，然后在参数齐全后，完成调用。
    {
        auto foo = [](int a, int b, int c) { return a + b + c; };
        // 将参数1,2绑定到函数 foo 上，
        // 但使用 std::placeholders::_1 来对第一个参数进行占位
        auto bindFoo = std::bind(foo, std::placeholders::_1, 1, 2);
        // 这时调用 bindFoo 时，只需要提供第一个参数即可
        cout << bindFoo(1) << endl;
    }

    //使用auto规避不太熟悉的函数的返回值类型

    return 0;
}