/**
 *@file 01thread.cpp
 * @author your name (you@domain.com)
 * @brief 线程基础，线程参数默认传参方式是值拷贝
 * @version 0.1
 * @date 2024-03-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <exception>

void thread_work1(const std::string& str) {
    std::cout << str << std::endl;
}

class background_task {
public:
    void operator()() {
        std::cout << "func background_task called" << std::endl;
    }
};

struct func {
    int& _i;
    func(int& i) : _i(i) {}
    void operator()() {
        for (int i = 0; i < 3; ++i) {
            _i = i;
            std::cout << "_i is " << _i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

void oops() {
    int some_local_state = 0;
    func myfunc(some_local_state);
    std::thread functhread(myfunc);
    // 存在隐患 访问局部变量 局部变量随着代码块结束或者主线程退出回收
    functhread.detach();
}

void use_join() {
    int some_local_state = 0;
    func myfunc(some_local_state);
    std::thread functhread(myfunc);
    functhread.join();
}

void catch_exception() {
    int some_local_state = 0;
    func myfunc(some_local_state);
    std::thread functhread{ myfunc };
    try {
        // run 一会
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    catch (std::exception& e) {
        functhread.join();
        throw;
    }
    functhread.join();
}

class thread_guard
{
private:
    std::thread& _t;
public:
    explicit thread_guard(std::thread& t) : _t(t) {};
    ~thread_guard() {
        // RAII
        if (_t.joinable())
            _t.join();
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator = (const thread_guard&) = delete;
};

void auto_guard() {
    int some_local_state = 0;
    func myfunc(some_local_state);
    std::thread functhread{ myfunc };
    thread_guard guard{ functhread };
    std::cout << "auto guard finished" << std::endl;
}

void print_str(int i, std::string str) {
    std::cout << "i is " << i << " str is " << str << std::endl;
}

void danger_oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%d", some_param);
    // 在线程内部将const char* 转换为std::string
    // 转换的时机
    // 在构造线程时， const char* 是作为一个成员变量存储在thread的内部
    // 在真正调用的时候才会完成这个转化
    // 隐式转换在线程的调用上可能会造成崩溃问题
    std::thread t{ print_str, 3, buffer };
    t.detach();
    std::cout << "danger oops finished" << std::endl;
}

void safe_oops(int some_params) {
    char buffer[1024];
    sprintf(buffer, "%d", some_params);
    // 显示转换， 避免隐式转换
    std::thread t{ print_str, 3, std::string(buffer) };
    t.detach();
}

void change_param(int& param) {
    ++param;
}

void ref_oops(int some_param) {
    std::cout << "before change, param is " << some_param << std::endl;
    // 此时thread保存的some_param将是一个右值， 要使用std::ref将其包装成左值，因为thread函数调用的为一个左值
    std::thread t(change_param, std::ref(some_param));
    t.join();
    std::cout << "after change, param is " << some_param << std::endl;
}

class X {
public:
    void do_length_work() {
        std::cout << "do_length_work" << std::endl;
    }
private:

};

void bind_class_oops() {
    X my_x;
    // 绑定类成员函数时&一定要使用， 第一个参数为对象的地址，类内部使用this
    std::thread t(&X::do_length_work, &my_x);
    t.join();
}

int main() {

    std::string hellostr{ "Hello, world!" };

    // 函数对象
    {
        std::thread t1(thread_work1, hellostr);
        // 一定要等待或者分离交给后台
        t1.join();
    }

    //仿函数对象
    {
        //! 编译器会将t2当成一个函数对象, 返回一个std::thread类型的值, 函数的参数为一个函数指针,该函数指针返回值为background_task, 参数为void
        //! "std::thread (*)(background_task (*)())"
        // std::thread t2(background_task());
        // t2.join();


        // ()
        std::thread t3((background_task()));
        t3.join();

        // {}
        std::thread t4{ background_task() };
        t4.join();
    }

    // lambda表达式
    {
        std::thread t5([](const std::string& str) {
            std::cout << "lambda : str is " << str << std::endl;
            }, hellostr);
        t5.join();
    }

    //  detach 注意事项
    {
        // 局部变量被引用的隐患
        //oops();
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 解决方案
    /*
        通过智能指针传递参数，因为引用计数会随着赋值增加，可保证局部变量在使用期间不被释放，这也就是伪闭包策略。
        将局部变量的值作为参数传递，这么做需要局部变量有拷贝复制的功能，而且拷贝耗费空间和效率。
        将线程运行的方式修改为join，这样能保证局部变量被释放前线程已经运行结束。但是这么做可能会影响运行逻辑。有些时候希望程序在后台运行
    */
    {
        //use_join();

        //catch_exception();

        //auto_guard();
    }

    // 危险示例 ： 隐式转换
    {
        int local_state = 0;
        //danger_oops(local_state);

        //safe_oops(local_state);
        //std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    // 引用参数
    {
        int local_var = 0;
        ref_oops(local_var);
    }

    // 绑定类成员函数
    {
        bind_class_oops();
    }

    return 0;
}
