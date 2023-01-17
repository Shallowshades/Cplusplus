/**
 * @file future.cpp
 * @author your name (you@domain.com)
 * @brief 期物 可以用来获取异步任务的结果 简单的线程同步手段，即屏障（barrier）
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <future>
#include <iostream>
#include <thread>

int main() {
    // 将一个lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([]() {
        static int sum = 0;
        for(int i = 0; i < 2e9 + 7; ++i) sum += i;
        return sum;
    });
    // 获得 task 的期物
    std::future<int> result = task.get_future();  // 在一个线程中执行 task
    std::thread(std::move(task)).detach();
    std::cout << "waiting..." << std::endl;
    result.wait();  // 在此设置屏障，阻塞到期物的完成
    // 输出执行结果
    std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;
    //在封装好要调用的目标后，可以使用 get_future() 来获得一个 std::future 对象，以便之后实施线程同步。 return 0;
}