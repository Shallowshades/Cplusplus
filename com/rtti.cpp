#include <cxxabi.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

/**
 *@brief abi::__cxa_demangle这个方法获取类型的真实名称
 *
 * @param name
 * @return const char*
 */
const char* TypeToName(const char* name) {
    const char* __name = abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
    return __name;
}

class A {
public:
    void print() { std::cout << "A" << std::endl; }
};

class B : public A {
public:
    void print() { std::cout << "B" << std::endl; }
};

class C {
public:
    virtual void print() { std::cout << "C" << std::endl; }
};

class D : public C {
public:
    void print() final { std::cout << "D" << std::endl; }
};

class H {
public:
    virtual ~H() {}
    void print() { std::cout << "H" << std::endl; }

    int h;
};

class I : virtual public H {
public:
    void print() { std::cout << "I" << std::endl; }

    int i;
};

class J : virtual public H {
public:
    void print() { std::cout << "J" << std::endl; }

    int j;
};

class K : public I, public J {
public:
    void print() { std::cout << "K" << std::endl; }

    int k;
};

int main() {

    {
        cout << typeid(char).name() << endl;
        cout << typeid(int).name() << endl;
        cout << typeid(double).name() << endl;
        cout << typeid(unsigned char).name() << endl;
        cout << typeid(unsigned int).name() << endl;
        cout << typeid(string).name() << endl;
        cout << typeid(vector<float>).name() << endl;
    }

    {
        cout << "-----------------\n";
        cout << TypeToName(typeid(char).name()) << endl;
        cout << TypeToName(typeid(int).name()) << endl;
        cout << TypeToName(typeid(double).name()) << endl;
        cout << TypeToName(typeid(unsigned char).name()) << endl;
        cout << TypeToName(typeid(unsigned int).name()) << endl;
        cout << TypeToName(typeid(string).name()) << endl;
        cout << TypeToName(typeid(vector<float>).name()) << endl;
    }

    // typeid识别静态类型
    {
        cout << "---------- 一个任意的类型名 ----------" << endl;
        cout << "----- 基本内置类型名 -----" << endl;
        cout << TypeToName(typeid(char).name()) << endl;
        cout << TypeToName(typeid(int).name()) << endl;
        cout << "----- 无多态的类型名 -----" << endl;
        cout << TypeToName(typeid(string).name()) << endl;
        cout << TypeToName(typeid(vector<int>).name()) << endl;
        cout << "----- 有多态的类型名 -----" << endl;
        cout << TypeToName(typeid(iostream).name()) << endl;

        cout << "\n\n"
             << "---------- 一个基本内置类型的变量，或指向基本内置类型的指针或引用 ----------" << endl;
        cout << "----- 基本内置类型的变量 -----" << endl;
        long   type_long   = 1;
        double type_double = 1.23;
        cout << TypeToName(typeid(type_long).name()) << endl;
        cout << TypeToName(typeid(type_double).name()) << endl;
        cout << "----- 指向基本内置类型的指针或引用 -----" << endl;
        long*   type_long_ptr   = &type_long;
        double& type_double_ref = type_double;
        cout << TypeToName(typeid(type_long_ptr).name()) << endl;
        cout << TypeToName(typeid(type_double_ref).name()) << endl;

        cout << "\n\n"
             << "---------- 一个任意类型的指针 ----------" << endl;
        cout << "----- 一个指向没有多态类型的指针 -----" << endl;
        B  b;
        A* a_ptr = &b;
        cout << TypeToName(typeid(&b).name()) << endl;
        cout << TypeToName(typeid(a_ptr).name()) << endl;
        cout << "----- 一个指向具有多态类型的指针 -----" << endl;
        D  d;
        C* c_ptr = &d;
        cout << TypeToName(typeid(&d).name()) << endl;
        cout << TypeToName(typeid(c_ptr).name()) << endl;

        cout << "\n\n"
             << "---------- 一个具体的对象实例，无论对应的类有没有多态都可以直接在编译器确定 ----------" << endl;
        cout << "----- 无多态类的实例 -----" << endl;
        string      type_string;
        vector<int> type_vector;
        cout << TypeToName(typeid(type_string).name()) << endl;
        cout << TypeToName(typeid(type_vector).name()) << endl;
        cout << "----- 有多态类的实例 -----" << endl;
        iostream type_ios(nullptr);
        cout << TypeToName(typeid(type_ios).name()) << endl;

        cout << "\n\n"
             << "---------- 一个指向没有多态的类对象的指针的解引用 ----------" << endl;
        cout << "----- 一个指向没有多态的类对象的指针的解引用 -----" << endl;
        cout << TypeToName(typeid(*a_ptr).name()) << endl;  // 推算出来的依然是A

        cout << "\n\n"
             << "---------- 一个指向没有多态的类对象的引用 ----------" << endl;
        cout << "----- 一个指向没有多态的类对象的引用 -----" << endl;
        A& a_ref = b;
        cout << TypeToName(typeid(a_ref).name()) << endl;  // 推算出来的依然是A
    }

    // typeid识别动态类型
    // 单纯虚继承是无法体现出多态的，尽管它也会生成对应的虚表，要真正实现多态只能依靠虚函数来实现。
    // + virtual ~H() {}
    {
        cout << "---typeid识别动态类型---\n";
        K  k;
        H* h_ptr = &k;
        I* i_ptr = &k;
        J* j_ptr = &k;

        cout << TypeToName(typeid(k).name()) << endl;
        cout << TypeToName(typeid(*h_ptr).name()) << endl;
        cout << TypeToName(typeid(*i_ptr).name()) << endl;
        cout << TypeToName(typeid(*j_ptr).name()) << endl;
    }

    // 虚函数表指针指向的前一个位置（也就是索引的-1项）存放的就是当前实际类型的type_info信息
    // typeid关于多态类型的计算是通过基类指针或引用指向的对象（子对象）的虚函数表的-1项获得的。
    {
        cout << "---vptr---\n";
        K  k;
        H* h_ptr = &k;
        I* i_ptr = &k;
        J* j_ptr = &k;
        std::cout << typeid(*h_ptr).name() << std::endl;
        long* vtbl_H = (long*)*(long*)h_ptr;
        std::cout << ((std::type_info*)*(vtbl_H - 1))->name() << std::endl << std::endl;

        std::cout << typeid(*i_ptr).name() << std::endl;
        long* vtbl_I = (long*)*(long*)i_ptr;
        std::cout << ((std::type_info*)*(vtbl_I - 1))->name() << std::endl << std::endl;

        std::cout << typeid(*j_ptr).name() << std::endl;
        long* vtbl_J = (long*)*(long*)j_ptr;
        std::cout << ((std::type_info*)*(vtbl_J - 1))->name() << std::endl;
    }

    return 0;
}