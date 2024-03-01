/**
 *@file thread_pool1.cpp
 * @author your name (you@domain.com)
 * @brief 线程池实现1，此实现并不算池，没有线程处于游离状态等待任务，而是任务来了开线程，超过线程数就不行了
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class thread_pool {

public:
    thread_pool(int threads_num) : stop(false) {
        for (int i = 0;i < threads_num; ++i) {
            threads.emplace_back([this] {   //very good
                while (true) {
                    function<void()> task;

                    //------ 
                    {
                        unique_lock<mutex> lock(this->mtx); // 局部锁
                        this->cv.wait(lock, [this] {return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty()) return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    //------

                    task();
                    std::cout << "Task completed one\n";
                }
                });
        }
    }

    template<typename FUNC, typename... Args>
    void enqueue(FUNC&& func, Args&&... args) {
        unique_lock<mutex> lock(mtx);
        tasks.emplace([&] { forward<FUNC>(func)(forward<Args>(args)...); });
    }

    ~thread_pool() {
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }

        cv.notify_all();
        for (auto& t : threads)
            t.join();
    }

private:
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop;
};

void func() {
    std::cout << "come on!!!\n";
}

int main() {
    thread_pool pool(10);
    function<void()> f = func;
    pool.enqueue(func);
    pool.enqueue(f);
    pool.enqueue([]() {std::cout << "try once!!\n";}); //部分回车没有输出

    for (int i = 0; i < 20; ++i)
        pool.enqueue(func);
}