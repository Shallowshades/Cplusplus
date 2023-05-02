/**
 * @file smart.cpp
 * @author your name (you@domain.com)
 * @brief 智能指针
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <memory>

// C++14已有该函数，C++11忘了
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {

    // std::shared_ptr 是一种智能指针，它能够记录多少个 shared_ptr 共同指向一个对象，
    // 从而消除显式的调用 delete，当引用计数变为零的时候就会将对象自动删除
    // 使用 std::shared_ptr 仍然需要使用 new 来调用，这使得代码出现了某种程度上的不对称
    // std::make_shared 就能够用来消除显式的使用 new，所以std::make_shared 会分配创建传入参数中的对象，
    // 并返回这个对象类型的std::shared_ptr指针
    {
        // auto pointer = new int(10); // illegal, no direct assignment
        // Constructed a std::shared_ptr
        auto foo     = [](std::shared_ptr<int> i) { (*i)++; };
        auto pointer = std::make_shared<int>(10);
        foo(pointer);
        std::cout << *pointer << std::endl;  // 11
        // The shared_ptr will be destructed before leaving the scope
    }

    // get() 方法来获取原始指针
    // reset() 来减少一个引用计数
    // use_count()来查看一个对象的引用计数
    {
        auto pointer  = std::make_shared<int>(10);
        auto pointer2 = pointer;                                                      // 引用计数+1
        auto pointer3 = pointer;                                                      // 引用计数+1
        int* p        = pointer.get();                                                // 这样不会增加引用计数
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;    // 3
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;  // 3
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;  // 3

        pointer2.reset();
        std::cout << "reset pointer2:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;    // 2
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;  // pointer2 已 reset; 0
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;  // 2
        pointer3.reset();
        std::cout << "reset pointer3:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;    // 1
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;  // 0
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;  // pointer3 已 reset; 0

        // std::cout << "delete p : \n";
        // delete p;
        // std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
        // 运行时出现异常
    }

    // std::unique_ptr 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象，从而保证代码的安全
    //  make_unique
    {
        std::cout << "------------\n";
        std::unique_ptr<int> pointer = std::make_unique<int>(10);  // make_unique 从 C++14 引入
        // std::unique_ptr<int> pointer2 = pointer;                    // 非法

        //既然是独占，换句话说就是不可复制。但是可以利用 std::move 将其转移给其他的 unique_ptr
        struct Foo {
            Foo() { std::cout << "Foo::Foo" << std::endl; }
            ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
            void foo() { std::cout << "Foo::foo" << std::endl; }
        };
        auto                 f = [](const Foo&) { std::cout << "f(const Foo&)" << std::endl; };
        std::unique_ptr<Foo> p1(std::make_unique<Foo>());
        // p1 不空, 输出
        if(p1) p1->foo();

        {
            std::cout << "------------\n";
            std::unique_ptr<Foo> p2(std::move(p1));
            // p2 不空, 输出
            f(*p2);
            // p2 不空, 输出
            if(p2) p2->foo();
            // p1 为空, 无输出
            if(p1) p1->foo();
            p1 = std::move(p2);
            // p2 为空, 无输出
            if(p2) p2->foo();
            std::cout << "p2 had destory" << std::endl;
        }
        // p1 不空, 输出
        if(p1) p1->foo();
        // Foo 的实例会在离开作用域时被销毁
    }

    // weak_ptr
    {
        {
            std::cout << "------------\n";
            struct A;
            struct B;

            struct A {
                std::shared_ptr<B> pointer;
                ~A() { std::cout << "A had destory" << std::endl; }
            };
            struct B {
                std::shared_ptr<A> pointer;
                ~B() { std::cout << "B had destory" << std::endl; }
            };
            auto a     = std::make_shared<A>();
            auto b     = std::make_shared<B>();
            a->pointer = b;
            b->pointer = a;
            a.reset();
            b.reset();
        }
        // 该块结束也没有输出，证明对象a,b并没有被析构,造成内存泄漏

        // 解决这个问题的办法就是使用弱引用指针 std::weak_ptr
        // std::weak_ptr是一种弱引用（相比较而言 std::shared_ptr 就是一种强引用）
        // 弱引用不会引起引用计数增加
        {
            std::cout << "------------\n";
            struct A;
            struct B;

            struct A {
                std::shared_ptr<B> pointer;
                ~A() { std::cout << "A had destory" << std::endl; }
                void info() { std::cout << "struct A\n"; }
            };
            struct B {
                std::weak_ptr<A> pointer;
                ~B() { std::cout << "B had destory" << std::endl; }
                void info() { std::cout << "struct B\n"; }
            };
            std::shared_ptr<B> b = std::make_shared<B>();
            std::shared_ptr<A> a = std::make_shared<A>();
            a->pointer           = b;
            b->pointer           = a;
            std::cout << "b.use_count = " << b.use_count() << std::endl;
            std::cout << "a.use_count = " << a.use_count() << std::endl;
            std::cout << "before a.reset()\n";
            a.reset();  //此时A已销毁
            std::cout << "after a.reset()\n";
            std::cout << "b.use_count = " << b.use_count() << std::endl;
            std::cout << "a.use_count = " << a.use_count() << std::endl;
            a->info();  //可以调用，函数独立于实体
            // a->pointer->info();  //不可以调用，pointer已不存在
            std::cout << "before b.reset()\n";
            b.reset();  //此时A已销毁
            std::cout << "after b.reset()\n";
            std::cout << "before block end\n";
        }
        std::cout << "block end\n";
    }

    //现代 C++ 将这项技术引进，在一定程度上消除了 new/delete 的滥用，是一种更加成熟的编程范式

    //问题
    // https://github.com/changkun/modern-cpp-tutorial/blob/master/assets/figures/pointers2.png
    //当a析构之后，A的引用变为了0（B中的pointer为弱指针，不增加引用计数），此时A会自动析构
    //由于析构是调用delete函数，会先析构（调用析构函数），再释放内存
    //当A析构时，发现成员量里有一个，shared_ptr(强引用)指向B，（这个无所谓吧，它指向别人，它析构会让别人的引用计数减一）
    //此时A可以析构？？还是不可以？？
    return 0;
}