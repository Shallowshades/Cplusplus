/**
 * @file vptr.cpp
 * @author your name (you@domain.com)
 * @brief 虚函数指针和虚函数表
 * @version 0.1
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <cstdio>
#include <iostream>
#include <typeinfo>

using namespace std;

class base {
public:
    base(int a = 0) : _a(a) {}
    ~base() {}

    virtual void func1() { cout << "base func1\n"; }
    virtual void func2() { cout << "base func2\n"; }
    virtual void func3() { cout << "base func3\n"; }

    int _a;
};

class drived : public base {
public:
    drived(int b = 0) : _b(b) {}
    ~drived() {}

    virtual void func1() { cout << "drived func1\n"; }
    virtual void func2() { cout << "drived func2\n"; }
    virtual void func3() { cout << "drived func3\n"; }

    int _b;
};

typedef size_t ptr;
typedef void (*funcptr)();

int main() {

    base*   b = new base();
    drived* d = new drived();

    cout << "sizeof(long) = " << sizeof(long) << endl;
    cout << "sizeof(unsigned int) = " << sizeof(unsigned int) << endl;
    cout << "sizeof(unsigned long) = " << sizeof(unsigned long) << endl;

    printf("b addr = %lX\n", reinterpret_cast<ptr>(b));
    printf("d addr = %lX\n", reinterpret_cast<ptr>(d));

    printf("b vptr addr = %lX\n", *reinterpret_cast<ptr*>(b));
    printf("d vptr addr = %lX\n", *reinterpret_cast<ptr*>(d));

    base*   b1 = new base();
    drived* d1 = new drived();

    printf("b1 vptr addr = %lX\n", *reinterpret_cast<ptr*>(b1));
    printf("d1 vptr addr = %lX\n", *reinterpret_cast<ptr*>(d1));

    size_t** vptr = reinterpret_cast<size_t**>(b);
    size_t* vtbl = *vptr;
    for(int i = 0; i < 3; i++) {
        funcptr func = reinterpret_cast<funcptr>(*(vtbl + i));
        func();
    }

    cout << reinterpret_cast<type_info*>(*(vtbl - 1))->name() << endl;

    return 0;
}