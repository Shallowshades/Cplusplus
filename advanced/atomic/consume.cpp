#include <atomic>
#include <iostream>
#include <assert.h>
#include <thread>
#include <string>
#include <chrono>

struct X {
    int i;
    std::string s;
};

std::atomic<X*> p;
std::atomic<int> a;

void create_x() {
    X* x = new X;
    x->i = 42;
    x->s = "hello";
    // a一定在p之前执行，但是a不一定对use_x可见。
    // 因为加载内存的时候，不一定会把a带过去
    a.store(99, std::memory_order_relaxed);
    p.store(x, std::memory_order_release);
}

void use_x() {
    X* x;
    while (!(x = p.load(std::memory_order_consume))) {
        // 休眠1ms
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
    // 这三个断言只有a会发生断言，因为虽然p声明为release，但是p并不依赖于a，所以a没有被顺序标记，
    // cpu会认为a和p没有关系，所以切换内存的时候，会把p的依赖带回来，但是不一定会把a带回来。
    assert(x->i == 42);
    assert(x->s == "hello");
    assert(a.load(std::memory_order_relaxed) == 99);
}

int main() {
    std::thread t1(create_x);
    std::thread t2(use_x);
    t1.join();
    t2.join();
}
