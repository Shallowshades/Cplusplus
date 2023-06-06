/**
 * @file thread.cpp
 * @author your name (you@domain.com)
 * @brief 并行与并发
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <ctime>
#include <iostream>
#include <thread>
// C++11本身支持的多线程，需包含该头文件
// 需要mingw的posix版本
// posix可移植操作系统接口（英语：Portable Operating System Interface，缩写为POSIX）

using namespace std;

int main() {

    // jion加入主线程，阻塞主线程
    {
        auto thread1 = []() -> void {  //子线程1(可调用对象作为线程的入口)
            cout << "thread 1 begin!" << endl;
            for(int i = 0; i < 30; ++i) cout << "I'm thread 1" << endl;
            cout << "thread 1 end!" << endl;
        };

        thread myThread(thread1);
        //线程一旦被创建就开始执行了，在遇到join之前，与main并发执行的

        cout << "1 main function start" << endl;
        cout << "I'm main function 1" << endl;
        cout << "I'm main function 2" << endl;
        cout << "I'm main function 3" << endl;
        cout << "I'm main function 4" << endl;
        if(myThread.joinable()) myThread.join();  //可以加入时才能加入主线程
        //此时主线程阻塞等待子线程结束

        cout << "I'm main function 5" << endl;
        cout << "I'm main function 6" << endl;
        cout << "I'm main function 7" << endl;
        cout << "I'm main function 8" << endl;
        cout << "1 main function end!" << endl;
    }

    // detach 将子线程交给系统托管
    {
        auto thread2 = []() -> void {  //子线程2(可调用对象作为线程的入口)
            cout << "thread 2 begin!" << endl;
            for(int i = 0; i < 30; ++i) cout << "I'm thread 2" << endl;
            cout << "thread 2 end!" << endl;
        };

        thread myThread(thread2);
        //线程一旦被创建就开始执行了，在遇到join之前，与main并发执行的

        cout << "2 main function start" << endl;
        cout << "I'm main function 1" << endl;
        cout << "I'm main function 2" << endl;
        cout << "I'm main function 3" << endl;
        cout << "I'm main function 4" << endl;
        if(myThread.joinable()) myThread.detach();  //可以加入时才能加入主线程

        cout << "I'm main function 5" << endl;
        cout << "I'm main function 6" << endl;
        cout << "I'm main function 7" << endl;
        cout << "I'm main function 8" << endl;
        cout << "2 main function end!" << endl;
    }

    //既不jion也不detach，会terminate called without an active exception
    {
        auto thread3 = []() -> void {  //子线程3(可调用对象作为线程的入口)
            cout << "thread 3 begin!" << endl;
            for(int i = 0; i < 30; ++i) cout << "I'm thread 3" << endl;
            cout << "thread 3 end!" << endl;
        };

        thread myThread(thread3);

        cout << "3 main function start" << endl;
        cout << "I'm main function 1" << endl;
        cout << "I'm main function 2" << endl;
        cout << "I'm main function 3" << endl;
        cout << "I'm main function 4" << endl;
        cout << "I'm main function 5" << endl;
        cout << "I'm main function 6" << endl;
        cout << "I'm main function 7" << endl;
        cout << "I'm main function 8" << endl;
        cout << "3 main function end!" << endl;
    }

    return 0;
}