/**
 * @file mutex.cpp
 * @author your name (you@domain.com)
 * @brief 互斥量
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

// std::mutex 是 C++11 中最基本的 mutex 类，通过实例化 std::mutex 可以创建互斥量，
// 而通过其成员函数 lock() 可以进行上锁，unlock() 可以进行解锁。
// 在实际编写代码的过程中，最好不去直接调用成员函数， 因为调用成员函数就需要在每个临界区的出口处调用 unlock()
// C++11还为互斥量提供了一个 RAII 语法的模板类 std::lock_guard
// RAII，也称为“资源获取就是初始化”，是c++等编程语言常用的管理资源、避免内存泄露的方法。
// 它保证在任何情况下，使用对象时先构造对象，最后析构对象。
// 简单的说，RAII 的做法是使用一个对象，
// 在其构造时获取资源，在对象生命期控制对资源的访问使之始终保持有效，最后在对象析构的时候释放资源。

int v;

int main() {

    // C++ 保证了所有栈对象在生命周期结束时会被销毁，所以这样的代码也是异常安全的。
    // 无论 critical_section() 正常返回、还是在中途抛出异常，都会引发堆栈回退，也就自动调用了 unlock()。
    {
        cout << "lock_guard---------------\n";
        auto critiacl_section = [](int change_v) -> void {
            static mutex      mtx;
            lock_guard<mutex> lock(mtx);
            v = change_v;  //执行竞争操作，临界区
            //离开作用域后mtx会被释放
        };

        thread t1(critiacl_section, 2);
        thread t2(critiacl_section, 3);
        if(t1.joinable()) t1.join();
        if(t2.joinable()) t2.join();
        cout << v << endl;
    }

    /**
     * @brief std::unique_lock 则是相对于 std::lock_guard 出现的，
     * std::unique_lock 更加灵活，
     * std::unique_lock 的对象会以独占所有权的方式管理 mutex对象上的上锁和解锁的操作。
     * （没有其他的 unique_lock 对象同时拥有某个 mutex 对象的所有权） 。
     * 所以在并发编程中，推荐使用 std::unique_lock。
     * std::lock_guard 不能显式的调用 lock 和 unlock，
     * 而 std::unique_lock 可以在声明后的任意位置调用， 可以缩小锁的作用范围，提供更高的并发度。
     * 如果用到了条件变量 std::condition_variable::wait 则必须使用 std::unique_lock 作为参数。
     *
     */

    {
        cout << "unique_lock-------------\n";
        auto critiacl_section = [](int change_v) -> void {
            static mutex       mtx;
            unique_lock<mutex> lock(mtx);
            v = change_v;  //执行竞争操作，临界区
            //离开作用域后mtx会被释放
            cout << "1 v = " << v << endl;
            lock.unlock();

            lock.lock();
            ++v;
            cout << "2 v = " << v << endl;
        };

        thread t1(critiacl_section, 2);
        thread t2(critiacl_section, 3);
        if(t1.joinable()) t1.join();
        if(t2.joinable()) t2.join();
    }

    return 0;
}