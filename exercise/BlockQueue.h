#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <cassert>
#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue {
public:
    BlockingQueue() : m_mutex(), m_condition(), m_data() {}

    // 禁止拷贝构造
    BlockingQueue(const BlockingQueue&) = delete;
    // BlockingQueue(BlockingQueue&&) = delete;

    ~BlockingQueue() {}

    void push(T&& value) {
        // 往队列中塞数据前要先加锁
        std::unique_lock<std::mutex> lock(m_mutex);
        m_data.push(value);
        m_condition.notify_all();
    }

    void push(const T& value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_data.push(value);
        m_condition.notify_all();
    }

    T take() {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_data.empty()) { m_condition.wait(lock); }
        assert(!m_data.empty());
        T value(std::move(m_data.front()));
        m_data.pop();

        return value;
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_data.size();
    }

private:
    // 实际使用的数据结构队列
    std::queue<T> m_data;

    // 条件变量的锁
    std::mutex              m_mutex;
    std::condition_variable m_condition;
};
#endif  // BLOCKINGQUEUE_H

// #include <iostream>
// #include <mutex>
// #include <random>
// #include <thread>
// #include <windows.h>
// using namespace std;

// int                task = 12;
// BlockingQueue<int> blockingqueue;
// std::mutex         mutex_cout;

// void worker() {
//     int        value;
//     thread::id this_id = this_thread::get_id();
//     while(true) {
//         value        = blockingqueue.take();
//         uint64_t sum = 0;
//         for(int i = 0; i < value; i++) { sum += i; }

//         // 模拟耗时操作
//         Sleep(100);

//         // std::lock_guard<mutex> lock(mutex_cout);
//         std::cout << "workder: " << this_id << " " << __FUNCTION__ << " line: " << __LINE__ << " sum: " << sum << "value : " << value << std::endl;
//     }
//     cout << "thread id : " << this_id << " is over\n";
// }

// void master() {
//     srand(time(nullptr));
//     for(int i = 0; i < task; i++) {
//         int x = rand() % 1000000;
//         blockingqueue.push(x);
//         printf("%s %d %i %d\n", __FUNCTION__, __LINE__, i, x);
//         Sleep(30);
//     }
// }

// void test() {
//     //常量 函数名
//     // cout << __FUNCTION__ << endl;
//     thread              th_master(master);
//     std::vector<thread> th_workers;
//     for(int i = 0; i < 5; i++) { th_workers.emplace_back(thread(worker)); }

//     th_master.join();
//     for(int i = 0; i < 5; i++) { th_workers[i].join(); }
// }
