/**
 *@file thread_pool3.cpp
 * @author your name (you@domain.com)
 * @brief 线程池实现3，此实现成池，线程处于游离状态等待任务，worker函数为友元函数
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

class thread_pool;
void worker(thread_pool* pool);

class thread_pool {

    friend void worker(thread_pool* pool);
public:
    thread_pool(int threads_num);
    template<typename FUNC, typename... Args>
    void enqueue(FUNC&& func, Args&&... args);
    ~thread_pool();

private:
    vector<thread*> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop;
};

thread_pool::thread_pool(int threads_num) : stop(false) {
    for (int i = 0; i < threads_num; ++i) {
        //worker为成员函数时，在内部调用自带this，解析为this->worker(),会解析成函数调用
        //将worker改为友元函数， 但这样做将worker暴露在外，影响？？？
        thread* t = new thread(worker, this);
        threads.emplace_back(std::move(t));
    }

    for (int i = 0; i < threads_num; ++i)
        threads[i]->detach();
}

template<typename FUNC, typename... Args>
void thread_pool::enqueue(FUNC&& func, Args&&... args) {
    unique_lock<mutex> lock(mtx);
    // 完美转发右值引用
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

void worker(thread_pool* pool) {
    stringstream ss;
    ss << "create one " << this_thread::get_id() << "\n";
    cout << ss.str();
    while (!pool->stop) {
        function<void()> task;

        //------
        {
            unique_lock<mutex> lock(pool->mtx); // 局部锁
            pool->cv.wait(lock, [&pool] {return pool->stop || !pool->tasks.empty(); });
            if (pool->tasks.empty()) continue;
            task = move(pool->tasks.front());
            pool->tasks.pop();
        }
        //------

        //operator bool 检查是否包含了有效的目标(公开成员函数)
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