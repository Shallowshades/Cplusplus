/**
 *@file 02thread.cpp
 * @author your name (you@domain.com)
 * @brief 线程的归属权 线程并发数量控制以及获取线程id等基本操作
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <thread>
#include <memory>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <chrono>

 // std::move
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

void some_function() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "some_function" << std::endl;
    }
}

void some_other_function() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "some_other_function" << std::endl;
    }
}

void dangerous_use() {
    std::thread t1(some_function);
    std::thread t2 = std::move(t1);
    t1 = std::thread(some_other_function);
    std::thread t3;
    t3 = std::move(t2);
    // 此时t1已经有一个线程了，再给他赋值将会调用terminate函数造成崩溃
    //t1 = std::move(t3);
    std::this_thread::sleep_for(std::chrono::seconds(20));

}

// safe 当返回临时变量thread时，匹配不到拷贝构造和拷贝赋值，自然就调用移动
// RVO NRVO机制 https://zhuanlan.zhihu.com/p/665538550
std::thread f() {
    return std::thread(some_function);
}

void param_function(int a) {
    for (int i = 0; i < 1; ++i) {
        std::stringstream ss;
        ss << "param is " << a << std::endl;
        std::cout << ss.str();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

std::thread g() {
    std::thread t(param_function, 43);
    return t;
}

struct func {
    int& _i;
    func(int& i) : _i(i) {}
    void operator()() {
        for (int i = 0; i < 3; ++i) {
            _i = i;
            std::cout << "_i is " << _i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

class thread_guard
{
private:
    std::thread& _t;
public:
    explicit thread_guard(std::thread& t) : _t(t) {};
    ~thread_guard() {
        // RAII
        if (_t.joinable())
            _t.join();
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator = (const thread_guard&) = delete;
};

void auto_guard() {
    int some_local_state = 0;
    func myfunc(some_local_state);
    std::thread functhread{ myfunc };
    thread_guard guard{ functhread };
    std::cout << "auto guard finished" << std::endl;
}

void print_str(int i, std::string str) {
    std::cout << "i is " << i << " str is " << str << std::endl;
}

class joining_thread {
private:
    std::thread _t;
public:
    joining_thread()noexcept = default;
    template<typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&&... args)
        : _t(std::forward<Callable>(func), std::forward<Args>(args)...) {}
    explicit joining_thread(std::thread t) noexcept : _t(std::move(t)) { /*std::cout << "id " << std::this_thread::get_id() << " -> std::thread t" << std::endl;*/ }
    joining_thread(joining_thread&& other) noexcept : _t(std::move(other._t)) { /*std::cout << "id " << std::this_thread::get_id() << " -> std::thread&& t" << std::endl;*/ }
    joining_thread& operator = (joining_thread&& other) noexcept {
        // 若当前线程可汇合，则汇合等待完成后在移动赋值
        if (_t.joinable())
            _t.join();
        _t = std::move(other._t);
        return *this;
    }
    joining_thread& operator = (joining_thread& other) noexcept {
        // 若当前线程可汇合，则汇合等待完成后在移动赋值
        if (_t.joinable())
            _t.join();
        _t = std::move(other._t);
        return *this;
    }
    ~joining_thread() {
        if (_t.joinable())
            _t.join();
    }

    void swap(joining_thread other) {
        _t.swap(other._t);
    }

    std::thread::id get_id()const noexcept {
        return _t.get_id();
    }

    bool joinable() const noexcept {
        return _t.joinable();
    }

    void join() {
        _t.join();
    }

    void detach() {
        _t.detach();
    }

    std::thread& as_thread() noexcept {
        return _t;
    }

    const std::thread& as_thread() const noexcept {
        return _t;
    }
};

void use_jointhread() {
    //  template<typename Callable, typename... Args>
    //  explicit joining_thread(Callable && func, Args&&... args)
    joining_thread j1([](int maxindex) {
        for (int i = 0; i < maxindex; ++i) {
            std::stringstream ss;
            ss << "in thread id " << std::this_thread::get_id() << " cur index is " << i << std::endl;
            std::cout << ss.str();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        }, 10);

    // 
    joining_thread j2(std::thread([](int maxindex) {
        for (int i = 0; i < maxindex; ++i) {
            std::stringstream ss;
            ss << "in thread id " << std::this_thread::get_id() << " cur index is " << i << std::endl;
            std::cout << ss.str();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        }, 10));

    //
    joining_thread j3(std::thread([](int maxindex) {
        for (int i = 0; i < maxindex; ++i) {
            std::stringstream ss;
            ss << "in thread id " << std::this_thread::get_id() << " cur index is " << i << std::endl;
            std::cout << ss.str();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        }, 10));

    j1 = std::move(j3);
}

void use_vector() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i) {
        threads.emplace_back(param_function, i);
    }
    for (auto&& entry : threads)
        entry.join();
}

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    const size_t length = std::distance(first, last);
    if (!length) return init;
    const size_t min_per_thread = 25;
    const size_t max_threads = (length + min_per_thread - 1) / min_per_thread;
    const size_t hardware_threads = std::thread::hardware_concurrency();
    const size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    const size_t block_size = length / num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    Iterator block_start = first;
    for (size_t i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    for (auto& entry : threads)
        entry.join();
    return accumulate(results.begin(), results.end(), init);
}

void use_parallel_acc() {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i)
        vec.push_back(i);
    int sum = 0;
    using namespace std::chrono;
    auto start = steady_clock::now();
    sum = parallel_accumulate<std::vector<int>::iterator, int>(vec.begin(), vec.end(), sum);
    auto end = steady_clock::now();
    std::cout << duration_cast<microseconds>(end - start).count() << std::endl;
    std::cout << "sum is " << sum << std::endl;
}

int main() {

    //每个线程都应该有其归属权，也就是归属给某个变量管理
    {
        //dangerous_use();
    }

    // joining_thread
    {
        //use_jointhread();
    }

    // 容器
    {
        //use_vector();
    }

    //并行计算
    {
        use_parallel_acc();
    }

    return 0;
}
