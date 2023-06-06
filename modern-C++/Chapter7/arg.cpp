/**
 * @file arg.cpp
 * @author your name (you@domain.com)
 * @brief 带传参(基本参数类型)的子线程
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <thread>
using namespace std;

int main() {

    //值传递
    {
        cout << "value-----------\n";
        auto thread1 = [](int ti, int tj) -> void {
            cout << "child start" << endl;
            cout << "ti{" << &ti << "} = " << ++ti << endl;
            cout << "tj{" << &tj << "} = " << ++tj << endl;
            cout << "child end" << endl;
        };

        cout << "main start" << endl;
        int ti = 4, tj = 5;
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        thread t(thread1, ti, tj);
        t.join();
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        cout << "main end" << endl;
    }

    //传统引用传递
    {
        cout << "&-------------\n";
        //此处只能用const接受,无法修改
        auto thread1 = [](const int& ti, const int& tj) -> void {
            cout << "child start" << endl;
            cout << "ti{" << &ti << "} = " << ti << endl;
            cout << "tj{" << &tj << "} = " << tj << endl;
            cout << "child end" << endl;
        };

        cout << "main start" << endl;
        int ti = 4, tj = 5;
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        thread t(thread1, ti, tj);
        t.join();
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        cout << "main end" << endl;
    }

    // ref引用传递
    {
        cout << "ref-------------\n";
        auto thread1 = [](int& ti, int& tj) -> void {
            cout << "child start" << endl;
            cout << "ti{" << &ti << "} = " << ++ti << endl;
            cout << "tj{" << &tj << "} = " << ++tj << endl;
            cout << "child end" << endl;
        };

        cout << "main start" << endl;
        int ti = 4, tj = 5;
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        thread t(thread1, ref(ti), ref(tj));
        t.join();
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        cout << "main end" << endl;
    }

    //传指针 存在主线程已经被销毁，但是子线程还在使用那块内存的隐患
    {
        cout << "point------------\n";
        auto thread1 = [](int* ti, int* tj) -> void {
            cout << "child start" << endl;
            cout << "ti{" << &ti << "} = " << ++*ti << endl;
            cout << "tj{" << &tj << "} = " << ++*tj << endl;
            cout << "child end" << endl;
        };

        cout << "main start" << endl;
        int ti = 4, tj = 5;
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        thread t(thread1, &ti, &tj);
        t.join();
        cout << "ti{" << &ti << "} = " << ti << endl;
        cout << "tj{" << &tj << "} = " << tj << endl;
        cout << "main end" << endl;
    }

    return 0;
}
