#include <iostream>

using namespace std;

class A {
public:
    int a;
};

class B {
public:
    int b;
};

class C : public A, public B {
public:
    int c;
};

class H {
public:
    virtual void print() { std::cout << "H" << std::endl; }
};

class I {
public:
    virtual void print() { std::cout << "I" << std::endl; }
};

class J : public H, public I {
public:
    virtual void print() override { std::cout << "J" << std::endl; }
};

int main() {

    // 用于基本内置数据类型之间的转换
    // 转换结果可能存在截断性，这种转换的安全性要由开发人员来保证
    {
        char  type_char       = 'A';
        float type_float      = type_char;                      // 隐式转换也可以
        float type_float_cast = static_cast<float>(type_char);  // 显式地使用static_cast进行强制类型转换
        cout << type_char << endl;
        cout << type_float << endl;

        double type_double    = 1.23;
        long   type_long      = type_double;                     // 隐式转换也可以
        long   type_long_cast = static_cast<long>(type_double);  // 显式地使用static_cast进行强制类型转换
        cout << type_double << endl;
        cout << type_long << endl;
    }

    // 用于指针之间的转换
    // 指针转换类型检查非常严格，不同类型的指针是禁止转换，除非使用void*作为中间参
    // 隐式转换下void*类型是无法直接转换为其它类型指针的，这时候就需要借助static_cast来转换了。
    // static_cast是直接不允许不同类型的引用进行转换的，因为没有void类型引用可以作为中间介质，这点和指针是有相当大区别的
    {
        int type_int = 100;
        // float* float_ptr1 = &type_int;                       // int* -> float* 隐式转换无效
        // float* float_ptr2 = static_cast<float*>(&type_int);  // int* -> float* 使用static_cast转换无效
        // char*  char_ptr1  = &type_int;                       // int* -> char* 隐式转换无效
        // char*  char_ptr2  = static_cast<char*>(&type_int);   // int* -> char* 使用static_cast转换无效
        cout << "type_int = " << type_int << endl;

        void* void_ptr = &type_int;  // 任何指针都可以隐式转换为void*
        // float* float_ptr3 = void_ptr;                       // void* -> float* 隐式转换无效
        float* float_ptr4 = static_cast<float*>(void_ptr);  // void* -> float* 使用static_cast转换成功
        // char*  char_ptr3  = void_ptr;                       // void* -> char* 隐式转换无效
        char* char_ptr4 = static_cast<char*>(void_ptr);  // void* -> char* 使用static_cast转换成功
        cout << "void_ptr = " << void_ptr << endl;
        cout << "*float_ptr = " << *float_ptr4 << endl;
        cout << "*char_ptr = " << (int)*char_ptr4 << endl;
    }

    // static_cast不能转换掉expression的const或volitile属性
    {
        int temp = 10;

        const int* a_const_ptr = &temp;
        // int*       b_const_ptr = static_cast<int*>(a_const_ptr);  // const int* -> int* 无效
        const int a_const_ref = 10;
        // int&      b_const_ref = static_cast<int&>(a_const_ref);  // const int& -> int& 无效
        volatile int* a_vol_ptr = &temp;
        // int*          b_vol_ptr = static_cast<int*>(a_vol_ptr);  // volatile int* -> int* 无效
        volatile int a_vol_ref = 10;
        // int&         b_vol_ref = static_cast<int&>(a_vol_ref);  // volatile int& -> int& 无效
    }

    // 用于类实例的之间转换
    // 任何合法的上行转换都可以直接由隐式转换来完成，而不需要手工去强制类型转换，但是下行转换则不行
    {
        C c;
        A a = static_cast<A>(c);  // 上行转换正常
        B b = static_cast<B>(c);  // 上行转换正常
        // C c_a = static_cast<C>(a);  // 下行转换无效 error: no matching function for call to ‘C::C(A&)’
        //  C c_b = static_cast<C>(b);  // 下行转换无效 error: no matching function for call to ‘C::C(B&)’
        //  可以看出通过添加参数为A、B的构造函数来将下行转换变得合法
    }

    // 用于没有多态的类实例指针或引用之间的转换
    // 进行上行转换（派生类指针->基类指针、派生类引用->基类引用）是完全安全的，这个过程由隐式转换来完成也是合法的
    // 进行下行转换（基类指针->派生类指针、基类引用->派生类引用）由于缺乏安全检查，所以是有问题的，要尽量避免这种用法
    // 如果两个类无继承关系，则使用static_cast进行转换时会失败，但是这种情况下static_cast会显性地展示出错误信息，是安全的
    {
        C c;

        A* a_ptr = static_cast<A*>(&c);  // 上行指针转换正常
        B* b_ptr = static_cast<B*>(&c);  // 上行指针转换正常
        A& a_ref = static_cast<A&>(c);   // 上行引用转换正常
        B& b_ref = static_cast<B&>(c);   // 上行引用转换正常

        C* c_ptra = static_cast<C*>(a_ptr);  // 下行指针转换正常
        C* c_ptrb = static_cast<C*>(b_ptr);  // 下行指针转换正常
        C& c_refa = static_cast<C&>(a_ref);  // 下行引用转换正常
        C& c_refb = static_cast<C&>(b_ref);  // 下行引用转换正常

        // A* a_ptr_fail = static_cast<A*>(b_ptr);  // B* -> A*，无关联的两个类型，无效

        A a;
        B b;

        // 以下都能转换成功，说明static_cast根本就没有安全检查，只看到有继承关系就给转换了
        C* c_ptra1 = static_cast<C*>(&a);
        C* c_ptrb1 = static_cast<C*>(&b);
        C& c_refa1 = static_cast<C&>(a);
        C& c_refb1 = static_cast<C&>(b);
    }

    // 用于具有多态的类实例指针或引用之间的转换
    // 进行上行转换（派生类指针->基类指针、派生类引用->基类引用）是完全安全的，没有任何问题，当然这个过程由隐式转换来完成也是合法的
    // 进行下行转换（基类指针->派生类指针、基类引用->派生类引用）由于缺乏安全检查，所以是有问题的，并且因为具有多态的类往往具有特殊的用法，所以在这种情况下产生的后果比前面没有多态情况下的要更严重，要尽量避免这种用法
    {
        J j;

        H* h_ptr = static_cast<H*>(&j);  // 上行指针转换正常
        I* i_ptr = static_cast<I*>(&j);  // 上行指针转换正常
        h_ptr->print();                  // 输出J，符合多态的要求
        i_ptr->print();                  // 输出J，符合多态的要求

        H& h_ref = static_cast<H&>(j);  // 上行引用转换正常
        I& i_ref = static_cast<I&>(j);  // 上行引用转换正常
        h_ref.print();                  // 输出J，符合多态的要求
        i_ref.print();                  // 输出J，符合多态的要求

        // TODO: 此处为何正常？ 本来就是由J转换而来？
        J* j_ptrh = static_cast<J*>(h_ptr);  // 下行指针转换正常
        J* j_ptri = static_cast<J*>(i_ptr);  // 下行指针转换正常
        j_ptrh->print();                     // 输出J，符合多态的要求
        j_ptrh->print();                     // 输出J，符合多态的要求

        J& j_refh = static_cast<J&>(h_ref);  // 下行引用转换正常
        J& j_refi = static_cast<J&>(i_ref);  // 下行引用转换正常
        j_refh.print();                      // 输出J，符合多态的要求
        j_refi.print();                      // 输出J，符合多态的要求

        // 下行转换不正常示例
        H h;
        I i;

        J* j_ptrh1 = static_cast<J*>(&h);
        J* j_ptri1 = static_cast<J*>(&i);
        j_ptrh1->print();  // 正常输出H
        j_ptri1->print();  // 段错误, 输出H
        // J由于先后继承H、I, 有两个虚指针，第一个是H的，第二个是I的

        J& j_refh1 = static_cast<J&>(h);
        J& j_refi1 = static_cast<J&>(i);
        j_refh1.print();  // 正常输出H
        j_refi1.print();  // 段错误, 输出H

        cout << sizeof(H) << endl;
        cout << sizeof(I) << endl;
        cout << sizeof(J) << endl;
    }
    return 0;
}