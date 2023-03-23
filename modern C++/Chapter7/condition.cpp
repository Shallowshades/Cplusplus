/**
 * @file condition.cpp
 * @author your name (you@domain.com)
 * @brief 条件变量与生产者消费者模型
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

int main() {
    queue<int>         produced_nums;
    mutex              mtx;
    condition_variable cv;
    bool               notified = false;

    // producer
    auto producer = [&]() {
        for(int i = 0;; ++i) {
            this_thread::sleep_for(chrono::milliseconds(900));
            unique_lock<mutex> lock(mtx);
            cout << "producing" << i << endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };

    // consumer
    auto consumer = [&]() {
        while(true) {
            unique_lock<mutex> lock(mtx);
            while(!notified) { cv.wait(lock); }  //避免虚假唤醒

            // give producer a chance
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(1000));
            lock.lock();

            while(!produced_nums.empty()) {
                cout << "consuming..." << produced_nums.front() << endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    //分别运行在不同的线程中
    thread pro[3], con[5];
    for(int i = 0; i < 3; ++i) pro[i] = thread(producer);
    for(int i = 0; i < 5; ++i) con[i] = thread(consumer);

    /**
     * @brief 线程jion() 阻塞主线程到子线程结束
     *
     */

    for(int i = 0; i < 1; ++i)
        if(pro[i].joinable()) pro[i].join();
    for(int i = 0; i < 2; ++i)
        if(con[i].joinable()) con[i].join();

    return 0;
}