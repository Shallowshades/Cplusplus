#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y() {
    // x和y的加载有顺序关系，并且x必须在y之前完成加载
    x.store(true, std::memory_order_relaxed);	// 1
    y.store(true, std::memory_order_release);	// 2
}

void read_y_then_x() {
    // 程序装载的时候，因为x和y的store有顺序，所以x和y的load也会被规定顺序
    // 这里指定acquire，所以y必须在x前面加载
    while (!y.load(std::memory_order_acquire));	// 3
    if (x.load(std::memory_order_relaxed))		// 4
        ++z;

    //1 先于 2， 2 先于 3， 3 先于 4， 所以 1 先于 4， z不可能为0
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread c(write_x_then_y);
    std::thread d(read_y_then_x);
    c.join();
    d.join();
    std::cout << z << "\n";
    assert(z.load() != 0);
}
