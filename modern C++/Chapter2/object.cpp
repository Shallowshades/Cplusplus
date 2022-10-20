/**
 * @file object.cpp
 * @author your name (you@domain.com)
 * @brief 面向对象
 * @version 0.1
 * @date 2022-09-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    int value1;
    int value2;
    Base() { value1 = 1; }
    Base(int value) : Base() { value2 = value; }  //委托构造函数， 简化代码
};

class Subclass : public Base {
public:
    using Base::Base;  //继承构造函数
};

//显式虚函数重载
// 函数SubClass::foo可能并不是程序员尝试重载虚函数，只是恰好加入了一个具有相同名字的函数。
//另一个可能的情形是，当基类的虚函数被删除后，子类拥有旧的函数就不再重载该虚拟函数并摇身一变成为了一个普通的类方法，这将造成灾难性的后果。
// C++11引入了 override 和 final 这两个关键字来防止上述情形的发生
namespace case1 {
    struct Base {
        virtual void foo();
    };
    struct SubClass : Base {
        void foo();
    };
}  // namespace case1

namespace case2 {
    struct Base {
        virtual void foo(int);
    };

    struct Subclass : Base {
        virtual void foo(int) override;  //合法
        // virtual void foo(float) override; //非法, 父类没有此虚函数
    };
}  // namespace case2

namespace case3 {
    struct Base {
        virtual void foo() final;
    };

    struct SubClass1 final : Base {};  // 合法

    // struct SubClass2 : SubClass1 {};  // 非法, SubClass1 已 final

    struct SubClass3 : Base {
        // void foo();  // 非法, foo 已 final
    };
}  // namespace case3

//显式禁用默认函数
//在传统 C++中，如果程序员没有提供，编译器会默认为对象生成默认构造函数、 复制构造、赋值算符以及析构函数。
//另外，C++ 也为所有类定义了诸如 new delete 这样的运算符。
//当程序员有需要时，可以重载这部分函数。

class Magic {
public:
    Magic()                        = default;  // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete;   // 显式声明拒绝编译器生成构造
    Magic(int magic_number);
};

//强类型枚举
//在传统C++中，枚举类型并非类型安全，枚举类型会被视作整数，则会让两种完全不同的枚举类型可以进行直接的比较（虽然编译器给出了检查，但并非所有），甚至同一个命名空间中的不同枚举类型的枚举值名字不能相同
//枚举类（enumeration class）
enum class new_enum : unsigned int { value1, value2, value3 = 100, value4 = 100 };
//未指定时将默认使用 int
//类型安全，首先不能够被隐式的转换为整数，同时也不能够将其与整数数字进行比较，更不可能对不同的枚举类型的枚举值进行比较。
//但相同枚举值之间如果指定的值相同，那么可以进行比较
template <typename T>
ostream& operator<<(typename enable_if<is_enum<T>::value, ostream>::type& stream, const T& e) {
    return stream << static_cast<typename underlying_type<T>::type>(e);
}

int main() {

    // 1
    {
        Base b(2);
        cout << b.value1 << endl;
        cout << b.value2 << endl;
    }

    // 2
    {
        Subclass s(3);
        cout << s.value1 << endl;
        cout << s.value2 << endl;
        cout << s.Base::value1 << endl;
        cout << s.Base::value2 << endl;
    }

    // 3
    {
        if(new_enum::value3 == new_enum::value4) cout << "new_enum::value3 == new_enum::value4" << endl;
        cout << "new_enum::value1 = " << new_enum::value1 << endl;
        cout << "new_enum::value2 = " << new_enum::value2 << endl;
        cout << "new_enum::value3 = " << new_enum::value3 << endl;
        cout << "new_enum::value4 = " << new_enum::value4 << endl;
    }
    return 0;
}