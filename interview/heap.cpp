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

#include <algorithm>
#include <functional>
#include <iostream>
#include <exception>

bool greater(int a, int b) { return a > b ? true : false; }
bool less(int a, int b) { return a < b ? true : false; }

template<typename T, int SIZE = 1025, bool(*FUNC)(T, T) = less>
class heap {
public:
    heap(int start) {
        for (int i = 0; i < 1000; ++i) {
            mArray[i] = start + i;
        }
        BuildHeap(mArray, 1000);
    }
    T top() const { return mArray[0]; }
    void replace_top(T elem) {
        mArray[0] = elem;
        HeapAdjust(mArray, 0, SIZE);
    }
    // T& operator [](int index) {
    //     if (index < 0 || index >= SIZE)
    //         throw new std::exception("index out of range");

    //     return mArray[index];
    // }
private:
    void HeapAdjust(T A[], int k, int n) {
        for (int i = 2 * k; i < n; i *= 2) {
            if (i < n - 1 && FUNC(A[i], A[k]) || FUNC(A[i + 1], A[k])) {//有两个子节点
                if (FUNC(A[i], A[i + 1])) swap(A[i], A[k]);
                else swap(A[++i], A[k]);
            }
            else if (FUNC(A[i], A[k])) {//只有一个子节点
                swap(A[i], A[k]);
            }
            else {//已满足堆结构
                break;
            }
            k = i;//调整父节点的下标
        }
    }
    void BuildHeap(T A[], int n) {
        for (int i = n / 2; i >= 0; --i) {
            HeapAdjust(A, i, n);
        }
    }
private:
    T mArray[SIZE];
};

int main() {

    return 0;
}