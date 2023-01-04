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
int main() {

    // error case
    {
        float type_float = 10.1;
        // int type_int = reinterpret_cast<int>(type_float);//出错，type-id和expression中必须有一个是指针或者引用
        // char type_char = reinterpret_cast<char>(&type_float);// 出错，64位系统，这里type-id只能是long类型
        // double* type_double_ptr = reinterpret_cast<double*>(type_float); // 出错，这里expression只能是整型

        A a;
        B b;
        // long type_long = reinterpret_cast<long>(a);  // 出错，type-id和expression中必须有一个是指针或者引用
        // B    b1        = reinterpret_cast<B>(a);     // 出错，type-id和expression中必须有一个是指针或者引用
        // A    a1        = reinterpret_cast<A>(&b);    // 出错，B* -> A不允许，64位系统，type-id只能是long
        // A*   a_ptr     = reinterpret_cast<A*>(b);    // 出错，这里expression只能是整型
    }

    //
    {
        // cout << sizeof(long) << endl; //8
        float  type_float     = 10.1;
        long   type_long      = reinterpret_cast<long>(&type_float);     // 正确，float* -> long
        float* type_float_ptr = reinterpret_cast<float*>(type_long);     // 正确，long -> float*
        cout << *type_float_ptr << endl;                                 // 正确，仍然输出10.1
        long*   type_long_ptr   = reinterpret_cast<long*>(&type_float);  // 正确，float* -> long*
        char    type_char       = 'A';
        double& type_double_ptr = reinterpret_cast<double&>(type_char);  // 正确，char -> double&

        A    a;
        B    b;
        long a_long = reinterpret_cast<long>(&a);       // 正确，A* -> long
        A*   a_ptr1 = reinterpret_cast<A*>(type_long);  // 正确，long -> A*
        A*   a_ptr2 = reinterpret_cast<A*>(&b);         // 正确，B* -> A*
    }

    //
    {
        A a;
        cout << addressof(a) << endl;

        /*
            template<typename _Tp>
            inline _Tp* __addressof(_Tp& __r) _GLIBCXX_NOEXCEPT
            {
                return reinterpret_cast<_Tp*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
            }

            template<typename _Tp>
            inline _Tp* addressof(_Tp& __r) noexcept
            { return std::__addressof(__r); }
        */

        /*
            1.将__r由类型_Tp&强制转换为const volatile char&，这样做有两个作用：
                一是防止后面使用&操作符获取地址时触发原类型(即_Tp)的重载操作(operator&)，就像上面那个例子那样；
                二是reinterpret_cast操作符总是可以合法的在原类型的基础上加const或volatile,但是如果_Tp原来就带有const或volatile的话, 通过reinterpret_cast去掉是不允许的, 因此需要加上const
           volatile来避免编译器报错, 也就是此时不用再管_Tp是否本来就带有const或volatile属性了。
            2.将前面转换得到的结果强制转换为char&类型，此时如果转换成其它类型有可能会触发强制地址对齐的操作，这样的话真实地址就有可能会被改变了，最终造成程序错误。需要注意的是这个转换过程使用的是const_cast，可以顺便将前面留下的const和volatile属性给去掉了。
            3.使用&符号将前面的结果的地址给取出来（此时已经不会触发重载了）
            4.最后一步使用reinterpret_cast将前面获取到的地址转换回_Tp*类型，并且此时也会保留_Tp的const或volatile属性（如果有的话）
        */
    }
    return 0;
}