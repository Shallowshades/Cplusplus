#include <iostream>
#include <mutex>
#include <string_view>
#include <syncstream>
#include <thread>
#include <functional>
#include <cstdio>
#include <sstream>
#include <condition_variable>

volatile int data = 0;
std::mutex mtx;
std::condition_variable cv;
bool processed = false;

/// @brief 安全自增 有锁保护
/// @param iterations 
void safe_increment(int iterations) {
    // TODO: 
    // 当多个线程同时发起时, 有可能存在一些线程还未获取锁,其他线程已经结束的情况
    // 这些线程未被计入cv中, 被忽略了
    const std::lock_guard<std::mutex> lock(mtx);
    while (iterations--) ++data;

    std::stringstream ss;
    ss << "thread id #" << std::this_thread::get_id() << ", data = " << ::data;
    std::cout << ss.str() << std::endl;

    processed = true;
    cv.notify_one();
}

/// @brief 不安全自增
/// @param iterations 
void unsafe_increment(int iterations) {
    while (iterations--) ++data;

    // TODO:
    // 当其中一个线程提前结束时,另一个线程还未获取mtx,此时在cv上等待的线程只有一个
    // 也就是另一个线程,没有被cv计入其中
    const std::lock_guard<std::mutex> lock(mtx);

    std::stringstream ss;
    ss << "thread id #" << std::this_thread::get_id() << ", data = " << ::data;
    std::cout << ss.str() << std::endl;

    processed = true;
    cv.notify_one();
}

/// @brief 测试两种自增
/// @param func_name 
/// @param func 
void test(std::string func_name, std::function<void(int)> func) {
    // set init value
    data = 0;

    char output[1024];
    sprintf(output, "before %s, data = %d", func_name.data(), ::data);
    std::cout << output << std::endl;

    processed = false;
    std::thread t1(func, 1'000'000);
    std::thread t2(func, 1'000'000);
    if (t1.joinable()) t1.detach();
    if (t2.joinable()) t2.detach();

    // wait for worker thread over notify
    std::unique_lock<std::mutex> looker(mtx);
    cv.wait(looker, []() { return processed; });

    sprintf(output, "after %s, data = %d\n", func_name.data(), ::data);
    std::cout << output << std::endl;
};

int main() {

    test("safe_increment", safe_increment);
    test("unsafe_increment", unsafe_increment);

    return 0;
}
