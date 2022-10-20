/**
 * @file template.cpp
 * @author your name (you@domain.com)
 * @brief 模板的哲学在于将一切能够在编译期处理的问题丢到编译期进行处理，仅在运行时处理那些最核心的动态服务，进而大幅优化运行期的性能。
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>

// 1.外部模板
// 传统C++中，模板只有在使用时才会被编译器实例化
// 换句话说，只要在每个编译单元（文件）中编译的代码中遇到了被完整定义的模板，都会实例化。
//产生了重复实例化而导致的编译时间的增加,并且没有办法通知编译器不要触发模板的实例化

// C++11引入了外部模板，扩充了原来的强制编译器在特定位置实例化模板的语法，使能够显式的通知编译器何时进行模板的实例化

template class std::vector<bool>;           //强行实例化
extern template class std::vector<double>;  //不该在当前编译文件中实例化模板

// 2.尖括号 ">"
// 从C++11可以使用连续的尖括号，可以顺利通过编译，但是不建议

template <bool T>
class MagicType2 {
    bool magic = T;
};

// 3.类型别名模板
// 模板是用来产生类型的
// 在传统C++中，typedef可以为类型定义一个新的名称，但是却没有办法为模板定义一个新的名称。因为，模板不是类型。

template <typename T, typename U>
class MagicType3 {
public:
    T dark;
    U magic;
};

// 不合法
// template <typename T>
// typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;

// C++11使用using引入新形式的写法，同时支持对传统 typedef相同的功效
///通常使用typedef定义别名的语法是：typedef 原名称 新名称;
///但是对函数指针等别名的定义语法却不相同，这通常给直接阅读造成了一定程度的困难。

typedef int (*process)(void*);      // typedef 定义函数指针
using NewProcess = int (*)(void*);  // using 定义函数指针，更加清晰
template <typename T>
using TrueDarkMagic = MagicType3<std::vector<T>, std::string>;

// 4.变长参数模板
// C++11允许任意个数、任意类别的模板参数，同时也不需要在定义时将参数的个数固定。

template <typename... Ts>
class Magic4 {};

// 如果不希望产生的模板参数个数为0，可以手动的定义至少一个模板参数
template <typename Require, typename... Args>
class Magic41;

// 变长参数模板也能被直接调整到到模板函数上
// 传统C中的printf函数，虽然也能达成不定个数的形参的调用，但其并非类别安全
// C++11除了能定义类别安全的变长参数函数外，还可以使类似 printf 的函数能自然地处理"非自带类别"的对象
// 除了在模板参数中能使用 ... 表示不定长模板参数外， 函数参数也使用同样的 ... 表示法代表不定长参数

template <typename... Args>
void printf4(const std::string& str, Args... args);

// 解包 使用sizeof...计算数量
template <typename... Ts>
void magic4(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}

// 对参数进行解包，到目前为止还没有一种简单的方法能够处理参数包，但有两种经典的处理手法
// 4.1. 递归模板函数
template <typename T0>
void printf41(T0 value) {
    std::cout << value << std::endl;
}

template <typename T, typename... Ts>
void printf41(T value, Ts... args) {
    std::cout << value << " ";
    printf41(args...);
}

// 4.2. 变参模板展开
//在C++17中增加了变参模板展开的支持，于是可以在一个函数中完成printf的编写
///事实上，虽然使用了变参模板，却不一定需要对参数做逐个遍历，
///可以利用 std::bind 及完美转发等特性实现对函数和参数的绑定，从而达到成功调用的目的。
template <typename T0, typename... T>
void printf42(T0 t0, T... t) {
    if constexpr(sizeof...(t) > 0) {
        std::cout << t0 << " ";
        printf42(t...);
    }
    else {
        std::cout << t0 << std::endl;
    }
}

// 4.3. 初始化列表展开 ???
template <typename T, typename... Ts>
auto printf43(T value, Ts... args) {
    std::cout << value << std::endl;
    (void)std::initializer_list<T>{ ([&args] { std::cout << args << std::endl; }(), value)... };
}

// 5. 折叠表达式
// C++17中将变长参数这种特性进一步带给了表达式
template <typename... T>
auto sum(T... t) {
    return (t + ...);
}

// 6. 非类型模板参数推导
// 让不同字面量成为模板参数，即非类型模板参数
template <typename T, int BufSize>
class buffer_t {
public:
    T&   alloc(){};
    void free(T& item){};

private:
    T data[BufSize];
};

// C++17引入让编译进行类型推导
template <auto value>
void foo() {
    std::cout << value << std::endl;
    return;
}

/**
 * @brief
 *
 * @return int
 */
int main() {

    // 2
    {
        std::vector<MagicType2<(1 > 2)>> magic;  //合法，但不建议
        std::cout << typeid(&magic).name() << std::endl;
    }

    // 3
    {
        TrueDarkMagic<bool> you;  //使用using定义带模板类型的别名
        std::cout << typeid(&you).name() << std::endl;
    }

    // 4
    {
        class Magic4<int, std::vector<int>, std::map<std::string, std::vector<int>>> darkMagic;  //任意数量，任意类型
        std::cout << typeid(&darkMagic).name() << std::endl;

        class Magic4<> nothing;  //可以没有
        std::cout << typeid(&nothing).name() << std::endl;

        std::cout << "parameter counts: \n";
        magic4();       // 输出0
        magic4(1);      // 输出1
        magic4(1, "");  // 输出2
        magic4(1, 2.0f, 3.14, 'c', "string");

        // 递归参数模板
        std::cout << "recursion : ";
        printf41(1, 2, "123", 1.1);

        // 变参模板展开
        std::cout << "variable parameter template expansion: ";
        printf42(1, 2.0f, 3.14, 'c', "string");

        //初始化列表展开 ???
        std::cout << "initialier_list expension: ";
        printf43(1, 2.0f, 3.14, 'c', "string");
    }

    // 5
    {
        std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;  //？？？
    }

    // 6
    {
        buffer_t<int, 100>    buf1;  // 100 作为模板参数
        buffer_t<double, 200> buf2;  // 100 作为模板参数
        std::cout << typeid(&buf1).name() << std::endl;
        std::cout << typeid(&buf2).name() << std::endl;

        std::cout << "auto type deduction: ";
        foo<10>();  // value 被推导为 int 类型
    }

    {
        std::cout << std::hash<std::string>{}(std::string("hello")) << std::endl;  // hash

        if(std::is_same<decltype(std::hash<std::string>{}(std::string("hello"))), unsigned long long>::value)
            std::cout << "decltype  ==  unsigned long long" << std::endl;

        if(std::is_same<decltype(std::hash<std::string>{}(std::string("hello"))), long long>::value)
            std::cout << "decltype  ==  long long" << std::endl;

        if(std::is_same<decltype(std::hash<std::string>{}(std::string("hello"))), std::string>::value)
            std::cout << "decltype  ==  std::string" << std::endl;
    }

    return 0;
}