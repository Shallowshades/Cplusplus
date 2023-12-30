/**
 *@file maxTHREAD_NUMBER.cpp
 * @author your name (you@domain.com)
 * @brief 一亿个数找最大的THREAD_NUMBER个数，要求效率高占用内存少
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <thread>
#include <queue>
#include <time.h>
#include <iostream>
#include <future>

using namespace std;

const size_t THREAD_NUMBER = 1000;

priority_queue<int, vector<int>, greater<int>> q[THREAD_NUMBER];

void deal(int start, int end, int index) {
    for (int i = start;i < end;++i) {
        q[index].push(i);
        if (q[index].size() > THREAD_NUMBER) {
            //cout << q.top() << endl;
            q[index].pop();
        }
    }
}

int main() {

    clock_t Time_Colck_Start, Time_Colck_End; //适合存储处理器时间的类型
    Time_Colck_Start = clock();//处理器启动时间

    //deal
    std::future<void> f[THREAD_NUMBER];
    for (int i = 0;i < THREAD_NUMBER;++i) {
        f[i] = std::async(std::launch::async, deal, i * 1e6, (i + 1) * 1e6, i);
    }

    for (int i = 0;i < THREAD_NUMBER;++i) {
        f[i].wait();
    }

    for (int i = 1;i < THREAD_NUMBER;++i) {
        while (!q[i].empty()) {
            q[0].push(q[i].top());
            q[i].pop();
        }
    }

    Time_Colck_End = clock(); //处理器结束时间
    cout << (1.0 * Time_Colck_End - Time_Colck_Start) / CLOCKS_PER_SEC << "s\n"; //时间差

    while (!q[0].empty()) {
        cout << q[0].top() << endl;
        q[0].pop();
    }

    return 0;
}