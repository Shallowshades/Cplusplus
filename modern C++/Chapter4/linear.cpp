/**
 * @file array.cpp
 * @author your name (you@domain.com)
 * @brief 线性容器
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <array>
#include <cmath>
#include <ctime>
#include <forward_list>
#include <iostream>
#include <vector>

int main() {

    // vector自动扩充，线性，整体移动

    // emplace_back()和push_back()的区别
    // emplace_back() 和 push_back() 的区别，就在于底层实现的机制不同。
    // push_back()向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
    //而emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
    {
        std::vector<int> v;
        std::cout << "size:" << v.size() << std::endl;          // 输出 0
        std::cout << "capacity:" << v.capacity() << std::endl;  // 输出 0

        // 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
        // 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        std::cout << "size:" << v.size() << std::endl;          // 输出 3
        std::cout << "capacity:" << v.capacity() << std::endl;  // 输出 4

        // 这里的自动扩张逻辑与 Golang 的 slice 很像
        v.push_back(4);
        v.push_back(5);
        std::cout << "size:" << v.size() << std::endl;          // 输出 5
        std::cout << "capacity:" << v.capacity() << std::endl;  // 输出 8

        // 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
        v.clear();
        std::cout << "size:" << v.size() << std::endl;          // 输出 0
        std::cout << "capacity:" << v.capacity() << std::endl;  // 输出 8

        // 额外内存可通过 shrink_to_fit() 调用返回给系统
        v.shrink_to_fit();
        std::cout << "size:" << v.size() << std::endl;          // 输出 0
        std::cout << "capacity:" << v.capacity() << std::endl;  // 输出 0

        constexpr unsigned int SIZE = 1e7 + 10;
        {
            clock_t          start = clock();
            std::vector<int> v(SIZE);
            for(int i = 0; i < SIZE; ++i) v.push_back(i);
            clock_t end = clock();
            std::cout << fabs(1.0 * start - end) / CLOCKS_PER_SEC << std::endl;
        }
        {
            clock_t          start = clock();
            std::vector<int> v(SIZE);
            for(int i = 0; i < SIZE; ++i) v.emplace_back(i);
            clock_t end = clock();
            std::cout << fabs(1.0 * start - end) / CLOCKS_PER_SEC << std::endl;
        }
    }

    // array“现代化”，封装了一些操作函数，比如获取数组大小以及检查是否非空，同时还能够友好的使用标准库中的容器算法
    {
        std::array<int, 4> arr1 = { 1, 2, 3, 4 };

        arr1.empty();  // 检查容器是否为空
        arr1.size();   // 返回容纳的元素数

        // 迭代器支持
        for(auto&& i : arr1) std::cout << i << " ";
        std::cout << std::endl;

        // 用 lambda 表达式排序
        std::sort(arr1.begin(), arr1.end(), [](int a, int b) { return b < a; });

        // 数组大小参数必须是常量表达式
        constexpr int        len  = 4;
        std::array<int, len> arr2 = { 1, 2, 3, 4 };

        // 非法,不同于 C 风格数组，std::array 不会自动退化成 T*
        // int *arr_p = arr;
    }

    //兼容C风格的接口
    {
        auto foo = [](int* p, int len) { std::cout << "invoke successfully!\n"; };

        std::array<int, 4> arr = { 1, 2, 3, 4 };

        // C 风格接口传参
        // foo(arr, arr.size()); // 非法, 无法隐式转换
        foo(&arr[0], arr.size());
        foo(arr.data(), arr.size());

        // 使用 `std::sort`
        std::sort(arr.begin(), arr.end());
    }

    // std::forward_list 是一个列表容器，使用方法和 std::list 基本类似。
    //和 std::list 的双向链表的实现不同，std::forward_list 使用单向链表进行实现，
    //提供了 O(1) 复杂度的元素插入，不支持快速随机访问（这也是链表的特点），
    //也是标准库容器中唯一一个不提供size() 方法的容器。
    //当不需要双向迭代时，具有比 std::list 更高的空间利用率。
    {
        std::forward_list<int> list;
        for(int i = 0; i < 6; ++i) list.emplace_front(i);
        for(auto&& elem : list) std::cout << elem << " ";
        std::cout << std::endl;
    }

    return 0;
}