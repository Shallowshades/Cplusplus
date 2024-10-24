#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>

using namespace std;
using ll = long long;
const int N = 1025;

// 初始形态
ll fib(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

namespace V1 {
    // 优化一
    // 有些递归得到的值会被重复递归, 所以记录一下
    ll nums[N]; //对于此数组要提前处理一下
    void deal() {
        // 优化一 处理
        fill(nums, nums + N, -1);
        nums[1] = 0;
        nums[2] = 1;
    }
    ll fib(int n) {
        if (nums[n] == -1)
            nums[n] = fib(n - 1) + fib(n - 2);
        return nums[n];
    }
}

namespace V2 {
    // 优化二
    // 递归消耗太多的栈内存, 当n值太大, 相比起动态规划速度也不如
    ll nums[N]; //对于此数组要提前处理一下
    void deal() {
        // 在这里处理是应对多实例的情况, 多次调用, 仅需处理一次
        nums[1] = 0;
        nums[2] = 1;
        for (int i = 3; i < N; ++i) {
            nums[i] = nums[i - 1] + nums[i - 2];
        }
    }
    ll fib(int n) {
        return nums[n];
    }
}

void testFib() {
    // 到50时,时间已经非常久了
    std::cout << fib(40) << std::endl;
}

void testFib1() {
    V1::deal();
    std::cout << V1::fib(1000) << std::endl;
}

void testFib2() {
    V2::deal();
    std::cout << V2::fib(1000) << std::endl;
}

void calcTime(function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << "s\n";
}

int main() {

    calcTime(testFib);
    calcTime(testFib1);
    calcTime(testFib2);

    // 测试结果
    /* 40 40 40
        63245986
        Elapsed time : 0.710352s
        63245986
        Elapsed time : 0.0001199s
        63245986
        Elapsed time : 0.0001992s
    */
    /* 40 1000 1000
        63245986
        Elapsed time: 0.631603s
        8261794739546030242
        Elapsed time: 0.0004395s
        8261794739546030242
        Elapsed time: 0.0003017s
    */

    return 0;
}