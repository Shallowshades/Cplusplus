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

#include <thread>
#include <algorithm>
#include <time.h>
#include <iostream>
#include "heap.h"

using namespace std;

const size_t THREAD_NUMBER = 50;
const size_t MAX_NUMBER = 1e9;
const size_t ANSWER_NUMBER = 1024;

heap* q[THREAD_NUMBER];

void deal(int start, int end, int index) {
    for (int i = start + ANSWER_NUMBER; i < end; ++i) {
        q[index]->replace_top(i);
    }
}

int main() {

    clock_t Time_Colck_Start, Time_Colck_End;
    Time_Colck_Start = clock();

    //deal
    std::thread* t[THREAD_NUMBER];
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        q[i] = new heap(static_cast<unsigned long long>(i) * MAX_NUMBER / THREAD_NUMBER);
        t[i] = new thread(deal, static_cast<unsigned long long>(i) * MAX_NUMBER / THREAD_NUMBER, (static_cast<unsigned long long>(i) + 1) * MAX_NUMBER / THREAD_NUMBER, i);
    }
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        if (t[i]->joinable())
            t[i]->join();

        delete t[i];
    }
    for (int i = 1; i < THREAD_NUMBER; ++i) {
        for (int j = 0; j < ANSWER_NUMBER; ++j) {
            q[0]->replace_top(q[i]->mArray[j]);
        }
    }

    Time_Colck_End = clock();
    cout << (1.0 * Time_Colck_End - Time_Colck_Start) / CLOCKS_PER_SEC << "s\n"; //时间差
    std::sort(q[0]->mArray, q[0]->mArray + ANSWER_NUMBER);
    for (int i = 24; i < ANSWER_NUMBER; ++i) {
        std::cout << q[0]->mArray[i] << std::endl;
    }

    /*
    * 1.重复释放
    * 2.作用域
    * 3.修改了数组前的标记（数组长度）
    */
    /*for (int i = 0; i < THREAD_NUMBER; ++i) {
        delete q[i];
    }*/

    return 0;
}