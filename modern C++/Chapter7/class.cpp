/**
 * @file class.cpp
 * @author your name (you@domain.com)
 * @brief 自定义类型
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <thread>
using namespace std;

class A {
public:
    A(int data = 0) : _data(data) { cout << "{" << this << "}ctor" << endl; };
    A(const A& a) : _data(a._data) { cout << "{" << this << "}copy" << endl; };
    A(A&& a) : _data(a._data) { cout << "{" << this << "}move" << endl; };
    ~A() { cout << "{" << this << "}dtor" << endl; };

    int  data() const { return _data; };
    int& data() { return _data; };

private:
    int _data;
};

int main() {

    //传值 copy 3次
    {
        cout << "value------------" << endl;
        auto thread1 = [](int val, A a) -> void {
            cout << "child thread start" << endl;
            cout << "val{" << &val << "} = " << ++val << endl;
            cout << "a{" << &a << "} = " << ++a.data() << endl;
            cout << "child thread end" << endl;
        };

        cout << "main thread start" << endl;
        int val = 2;
        A   a(3);
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        thread t(thread1, val, a);
        t.join();
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        cout << "main thread end" << endl;
    }

    //引用 copy 2 次
    {
        cout << "&------------" << endl;
        //接受只能const
        auto thread1 = [](const int& val, const A& a) -> void {
            cout << "child thread start" << endl;
            cout << "val{" << &val << "} = " << val << endl;
            cout << "a{" << &a << "} = " << a.data() << endl;
            cout << "child thread end" << endl;
        };

        cout << "main thread start" << endl;
        int val = 2;
        A   a(3);
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        thread t(thread1, val, a);
        t.join();
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        cout << "main thread end" << endl;
    }

    // ref 不copy
    {
        cout << "ref------------" << endl;
        auto thread1 = [](int& val, A& a) -> void {
            cout << "child thread start" << endl;
            cout << "val{" << &val << "} = " << ++val << endl;
            cout << "a{" << &a << "} = " << ++a.data() << endl;
            cout << "child thread end" << endl;
        };

        cout << "main thread start" << endl;
        int val = 2;
        A   a(3);
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        thread t(thread1, ref(val), ref(a));
        t.join();
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        cout << "main thread end" << endl;
    }

    // point 存在主线程已经被销毁，但是子线程还在使用那块内存的隐患
    {
        cout << "point------------" << endl;
        auto thread1 = [](int* val, A* a) -> void {
            cout << "child thread start" << endl;
            cout << "val{" << &val << "} = " << ++val << endl;
            cout << "a{" << &a << "} = " << ++a->data() << endl;
            cout << "child thread end" << endl;
        };

        cout << "main thread start" << endl;
        int val = 2;
        A   a(3);
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        thread t(thread1, &val, &a);
        t.join();
        cout << "val{" << &val << "} = " << val << endl;
        cout << "a{" << &a << "} = " << a.data() << endl;
        cout << "main thread end" << endl;
    }

    //用临时变量作为实参时，会更高效，由于临时变量会隐式自动进行移动操作，这就减少了整体构造函数的调用次数。
    //而一个命名变量的移动操作就需要std::move()。
    //隐式调用move 2 次
    {
        cout << "temporary------------" << endl;
        auto thread1 = [](const A& a) -> void {
            cout << "child thread start" << endl;
            cout << "a{" << &a << "} = " << a.data() << endl;
            cout << "child thread end" << endl;
        };

        cout << "main thread start" << endl;
        thread t(thread1, A(2));
        t.join();
        cout << "main thread end" << endl;
    }

    return 0;
}