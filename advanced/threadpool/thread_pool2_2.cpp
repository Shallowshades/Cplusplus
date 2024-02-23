/**
 *@file thread_pool2.cpp
 * @author your name (you@domain.com)
 * @brief 线程池实现2-2，此实现成池，线程处于游离状态等待任务，worker函数为成员函数，隐含第一个参数（自身）
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
#include <chrono>
#include <sstream>

using namespace std;

class thread_pool {
public:
    thread_pool(int threads_num);
    template<typename FUNC, typename... Args>
    void enqueue(FUNC&& func, Args&&... args);
    ~thread_pool();

private:
    void worker();

private:
    vector<thread*> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop;
};

thread_pool::thread_pool(int threads_num) : stop(false) {
    for (int i = 0; i < threads_num; ++i) {
        // worker为成员函数时，在内部调用自带this，解析为this->worker(),会解析成函数调用
        // 成员函数的第一个参数为其自身对象， 隐含
        thread* t = new thread(&thread_pool::worker, this);
        threads.emplace_back(std::move(t));
    }

    for (int i = 0; i < threads_num; ++i)
        threads[i]->detach();
}

template<typename FUNC, typename... Args>
void thread_pool::enqueue(FUNC&& func, Args&&... args) {
    unique_lock<mutex> lock(mtx);
    tasks.emplace([&] { forward<FUNC>(func)(forward<Args>(args)...); });
    cv.notify_one();
}

thread_pool::~thread_pool() {
    {
        unique_lock<mutex> lock(mtx);
        stop = true;
    }

    cv.notify_all();
    for (int i = 0; i < threads.size(); ++i)
        delete threads[i];
}

void thread_pool::worker() {
    stringstream ss;
    ss << "create one " << this_thread::get_id() << "\n";
    cout << ss.str();

    //-------
    while (!this->stop) {
        function<void()> task;

        //------
        {
            unique_lock<mutex> lock(this->mtx); // 局部锁
            this->cv.wait(lock, [this] {return this->stop || !this->tasks.empty(); });
            if (tasks.empty()) continue;
            task = move(this->tasks.front());
            this->tasks.pop();
        }
        //------

        if (task) task();
    }
}

void func() {
    //std::cout << "come on!!!\n";
    this_thread::sleep_for(chrono::milliseconds(20));
    std::cout << std::this_thread::get_id() << " : Task completed one\n";
}

int main() {
    thread_pool pool(10);
    function<void()> f = func;
    for (int i = 0; i < 100; ++i) {
        pool.enqueue(func);
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    //pool.enqueue(f);
    //pool.enqueue([]() {std::cout << "try once!!\n"; }); //部分回车没有输出
    this_thread::sleep_for(chrono::seconds(2));
}