/**
 * @file atomic.cpp
 * @author your name (you@domain.com)
 * @brief 原子操作与内存模型
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> count   = { 0 };
std::atomic<int> counter = { 0 };

int main() {

    //
    {
        int a    = 0;
        int flag = 0;
        std::cout << "a{" << &a << "} = " << a << std::endl;

        std::thread t1([&]() {
            while(flag != 1) {}
            int b = a;
            std::cout << "a{" << &a << "} = " << a << std::endl;
            std::cout << "b{" << &b << "} = " << b << std::endl;
        });

        std::thread t2([&]() {
            a = 5;
            std::cout << "a{" << &a << "} = " << a << std::endl;
            flag = 1;
        });

        t1.join();
        t2.join();
    }

    //
    {
        std::cout << "atomic add---------------\n";
        std::thread t1([]() { count.fetch_add(1); });
        std::thread t2([]() {
            count++;     // 等价于 fetch_add
            count += 1;  // 等价于 fetch_add
        });
        t1.join();
        t2.join();
        std::cout << count << std::endl;
    }

    //
    {
        std::cout << "meet the requirement of cpu's momery align--------\n";
        struct A {
            float     x;
            int       y;
            long long z;
        };

        std::atomic<A> a;
        // std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    }

    // the order of memory
    {
        std::cout << "relaxed-------------\n";
        std::vector<std::thread> vt;
        for(int i = 0; i < 100; ++i) {
            vt.emplace_back([&]() { counter.fetch_add(1, std::memory_order_relaxed); });
        }

        for(auto& t : vt) { t.join(); }
        std::cout << "current counter:" << counter << std::endl;
    }

    //
    {
        std::cout << "release/consume-----------\n";
        // 初始化为 nullptr 防止 consumer 线程从野指针进行读取
        int               v;
        std::atomic<int*> ptr(nullptr);
        std::thread       producer([&]() {
            int* p = new int(42);
            v      = 1024;
            ptr.store(p, std::memory_order_release);
        });
        std::thread       consumer([&]() {
            int* p;
            while(!(p = ptr.load(std::memory_order_consume))) {}
            std::cout << "p: " << *p << std::endl;
            std::cout << "v: " << v << std::endl;
        });
        producer.join();
        consumer.join();
    }

    //
    {
        std::cout << "release/acquire/rel_acq--------\n";
        std::vector<int> v;
        std::atomic<int> flag = { 0 };
        std::thread      release([&]() {
            v.push_back(42);
            flag.store(1, std::memory_order_release);
        });
        std::thread      acqrel([&]() {
            int expected = 1;
            // must before compare_exchange_strong
            while(!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) expected = 1;  // must after compare_exchange_strong
            // flag has changed to 2
        });
        std::thread      acquire([&]() {
            while(flag.load(std::memory_order_acquire) < 2) {}
            std::cout << v.at(0) << std::endl;  // must be 42
        });
        release.join();
        acqrel.join();
        acquire.join();
    }

    //
    {
        std::cout << "seq_cst-------------\n";
        std::atomic<int>         counter = { 0 };
        std::vector<std::thread> vt;
        for(int i = 0; i < 100; ++i) {
            vt.emplace_back([&]() { counter.fetch_add(1, std::memory_order_seq_cst); });
        }
        for(auto& t : vt) { t.join(); }
        std::cout << "current counter:" << counter << std::endl;
    }

    return 0;
}