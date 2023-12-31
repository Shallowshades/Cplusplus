/**
 *@file heap.hpp
 * @author your name (you@domain.com)
 * @brief 堆排序 max1000特化
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <iostream>

bool less(int a, int b) { return a < b ? true : false; }
const size_t SIZE = 1000;
class heap {
public:
    heap(int start) {
        for (int i = 0; i < SIZE; ++i) {
            mArray[i] = start + i;
        }
        BuildHeap();
    }
    ~heap() = default;
    int top() const { return mArray[0]; }
    void replace_top(const int& elem) {
        mArray[0] = elem;
        HeapAdjust(0);
    }
    //inline void operator delete[](void* ptr) { delete ptr; }
private:
    void HeapAdjust(int k) {
        for (int i = 2 * k + 1; i < SIZE; i *= 2) {
            if (i < SIZE - 1 && ::less(mArray[i], mArray[k]) || ::less(mArray[i + 1], mArray[k])) {//有两个子节点
                if (::less(mArray[i], mArray[i + 1])) std::swap(mArray[i], mArray[k]);
                else std::swap(mArray[++i], mArray[k]);
            }
            else if (::less(mArray[i], mArray[k])) {//只有一个子节点
                std::swap(mArray[i], mArray[k]);
            }
            else {//已满足堆结构
                break;
            }
            k = i;//调整父节点的下标
        }
    }
    void BuildHeap() {
        for (int i = SIZE / 2; i >= 0; --i) {
            HeapAdjust(i);
        }
    }



public:
    int mArray[SIZE];
};