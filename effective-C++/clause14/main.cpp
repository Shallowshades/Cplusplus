/**
 *@file main.cpp
 * @author your name (you@domain.com)
 * @brief RAII对象的拷贝行为
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <mutex>

using namespace std;

/*
    lock_guard
    禁止拷贝构造和拷贝赋值

    禁止拷贝（std::unique_ptr）
    管理资源的引用计数（std::shared_ptr）
    拷贝底层资源（std::string）
    移动管理资源的所有权（std::unique_ptr）
*/

mutex m;

void bar() {
    //...
    lock_guard locker(m);
    //...
}

int main() {



    return 0;
}
