// 顺序一致隐含着总体顺序
#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() {
    x.store(true, std::memory_order_seq_cst);	// 可以不写，这是默认
}
void write_y() {
    y.store(true, std::memory_order_seq_cst);	// 可以不写，这是默认
}

void read_x_then_y() {
    // 最先体现在这两句代码，while和if
    // 如果是顺序严格的，那么一定是先执行while，再执行if
    // 如果是顺序不严格的，那么就可能是先执行if，再执行while
    // 因为在cpu看来，while里面没有用到if里面的变量，就会认为它们之间是没有关系的，
    // 就会先给if装载值，然后等while执行完了，直接给if执行，而不会再去给if装在值，这就会导致问题。
    while (!x.load(std::memory_order_seq_cst));

    // 执行到此处时， y有可能被改为true
    if (y.load(std::memory_order_seq_cst))
        ++z;

}

void read_y_then_x() {
    // while 和 if 未使用相同变量， 编译器会认为他们之间没有关联， 可能先执行if
    while (!y.load(std::memory_order_seq_cst));

    // 执行到此处时， x一定被改为true了
    if (x.load(std::memory_order_seq_cst))
        ++z;
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    std::cout << z << "\n";	// 要么==1，要么==2；
}
