#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

// release语句之前的所有变量的读写操作(including non-atomic and relaxed atomic)都对另一个线程中的acquire之后的代码可见。
void write_x_then_y() {
    std::cout << 2 << std::endl;
    x.store(true, std::memory_order_relaxed);	// 1 x 顺序无要求
    y.store(true, std::memory_order_release);	// 2 y release要求在此语句之前的,必须在它之前,不可重排到它之后
}

void read_y_then_x() {
    std::cout << 1 << std::endl;
    while (!y.load(std::memory_order_acquire));	// 3 y acquire要求在此语句之后的,必须在它之后,不可重排到它之前; 与release有同步关系
    if (x.load(std::memory_order_relaxed))		// 4
        ++z;
}

int main() {
    x.store(false);
    y.store(false);
    z.store(false);
    std::thread b(read_y_then_x);
    std::thread a(write_x_then_y);
    a.join();
    b.join();
    assert(z.load() != 0);
}