/**
 *@file 2staticlist.hpp
 * @author your name (you@domain.com)
 * @brief 静态链表
 * @version 0.1
 * @date 2024-03-08
 *
 * @copyright Copyright (c) 2024
 *
 */

 /**
  *@brief 思路： 主要记录首和尾，尾部是用来插入，主要问题在于删除之后的空位回收，采取达到一定数量后一起回收，数组内存采取一次性分配方式，防止扩容反复移动
                去掉一次性分配也可以，直接emplace在尾部可以，这样更省事
  *
 */
#pragma once

#include <iostream>
#include <vector>
#include <memory>

template<typename T, size_t SIZE>
class static_list;

template<typename T, size_t SIZE = 1024>
class static_list {
public:

    struct node {
        T val;
        int nextIdx;

        node() : val(-1), nextIdx(-1) { } // 此处val(-1)只是为了测试方便观察
        node(T v, int idx) : val(v), nextIdx(idx) { }
    };

    static_list();
    ~static_list() = default;

    static_list(const static_list& list) = delete;
    static_list& operator = (const static_list& list) = delete;


    bool empty() const { return m_iSize == 0; }
    size_t size() const { return m_iSize; }

    int insert(T elem);
    bool erase(T elem);
    bool find(T elem) const;

    void print() {
        std::cout << "--------------------------\n";
        for (auto&& elem : m_vecAry) {
            std::cout << elem.val << " " << elem.nextIdx << "\n";
        }
        std::cout << "--------------------------\n";
    }

    //private:
            // 作为私有， 根据策略进行调整， 手动操作为了测试
    void adjust();

private:
    std::vector<node> m_vecAry;
    size_t m_iSize;
    size_t m_iFree;
    size_t m_iHeadIdx;
    size_t m_iRearIdx;
    size_t m_iCapicity;
};

template<typename T, size_t SIZE>
static_list<T, SIZE>::static_list()
    : m_iSize(0)
    , m_iFree(0)
    , m_iHeadIdx(-1)
    , m_iRearIdx(-1)
    , m_iCapicity(SIZE)
{
    // 一次性分配一部分， 避免扩容反复移动
    m_vecAry.resize(m_iCapicity, node());

}

// 如果采用扫描数组的方法找到删除产生的空位，效率很低
// 不如直接在尾部添加，空位统一处理
template<typename T, size_t SIZE /*= 1024*/>
int static_list<T, SIZE>::insert(T elem)
{
    ++m_iSize;

    // 容量不够， 扩容
    if (m_iSize + m_iFree >= m_iCapicity) {
        m_iCapicity = 2 * m_iCapicity;
        m_vecAry.resize(m_iCapicity);
    }

    // 链头特殊处理
    if (m_iRearIdx == -1)
        m_iHeadIdx = m_iRearIdx + 1;
    else
        m_vecAry[m_iRearIdx].nextIdx = m_iRearIdx + 1;


    // 插入
    m_vecAry[++m_iRearIdx] = node{ elem, -1 }; // -1 表示空指针
    return m_iRearIdx;
}

template<typename T, size_t SIZE>
bool static_list<T, SIZE>::erase(T elem)
{
    size_t curIdx = m_iHeadIdx;
    size_t lastIdx = -1;
    while (curIdx != -1) {
        if (m_vecAry[curIdx].val == elem) {
            // find it, reset head or rear if it is
            if (lastIdx == -1) {
                // erase head
                m_iHeadIdx = m_vecAry[curIdx].nextIdx;
            }

            if (m_vecAry[curIdx].nextIdx == -1) {
                // erase rear
                m_iRearIdx = lastIdx;
                --m_iFree; // 尾部会直接被下次使用，而不计入已使用的被删除的空间
            }

            if (lastIdx != -1) {
                // 头部直接略过
                m_vecAry[lastIdx].nextIdx = m_vecAry[curIdx].nextIdx;
            }

            --m_iSize;
            ++m_iFree;

            if (m_iFree > 0.5 * m_iCapicity || m_iFree > 20) {
                // 可以根据不同策略，清空删除产生的空位
                adjust();
            }

            return true;
        }
        lastIdx = curIdx;
        curIdx = m_vecAry[curIdx].nextIdx;
    }
    return false;
}

template<typename T, size_t SIZE /*= 1024*/>
bool static_list<T, SIZE>::find(T elem) const
{
    size_t curIdx = m_iHeadIdx;
    while (curIdx != -1) {
        if (m_vecAry[curIdx].val == elem)
            return true;

        curIdx = m_vecAry[curIdx].nextIdx;
    }
    return false;
}

template<typename T, size_t SIZE /*= 1024*/>
void static_list<T, SIZE>::adjust()
{
    if (m_iFree == 0)
        return;

    std::vector<node> tmp(m_iCapicity, node());
    size_t curIdx = m_iHeadIdx;
    size_t vecIdx = 0;
    while (curIdx != -1) {
        tmp[vecIdx] = m_vecAry[curIdx];
        if (m_vecAry[curIdx].nextIdx != -1) {
            tmp[vecIdx].nextIdx = vecIdx + 1;
            vecIdx += 1;
        }

        curIdx = m_vecAry[curIdx].nextIdx;
    }

    if (m_iHeadIdx != -1) {
        m_iHeadIdx = 0;
        m_iRearIdx = vecIdx;
    }

    m_iFree = 0;
    m_vecAry.swap(tmp);
}


int main() {

    static_list<int, 8> list1;

    // 观察扩容是否正常
    std::cout << "观察扩容是否正常" << std::endl;
    for (int i = 0; i < 12; ++i)
        list1.insert(i);
    list1.print();

    // 观察删除
    std::cout << "观察删除" << std::endl;
    static_list<int, 16> list2;
    for (int i = 0; i < 14; ++i)
        list2.insert(i);

    {
        // 删除中间
        std::cout << "删除中间" << std::endl;
        for (int i = 2; i < 8; ++i)
            list2.erase(i);
        list2.print();

        // 触发调整
        std::cout << "触发调整" << std::endl;
        for (int i = 8; i < 11; ++i)
            list2.erase(i);
        list2.print();

        // 调整后添加
        std::cout << "调整后添加" << std::endl;
        for (int i = 14; i < 20; ++i)
            list2.insert(i);
        list2.print();

        // 删除头部 不会观察到变化，只改变了头部指针的位置
        std::cout << "删除头部 不会观察到变化，只改变了头部指针的位置" << std::endl;
        list2.erase(0);
        list2.print();

        //删除尾部
        std::cout << "删除尾部" << std::endl;
        list2.erase(19);
        list2.print();

        //调整，观察头部
        std::cout << "调整，观察头部" << std::endl;
        list2.adjust();
        list2.print();

        // 删到一个
        std::cout << "删到一个， 既是头，亦是尾," << std::endl;
        for (int i = 11; i < 19; ++i)
            list2.erase(i);
        list2.print();

        //仅剩一个， 既是头，亦是尾
        std::cout << "仅剩一个，删除调整" << std::endl;
        list2.erase(1);
        list2.adjust();
        list2.print();

        //再次插入观察
        std::cout << "再次插入观察" << std::endl;
        for (int i = 0; i < 10; ++i)
            list2.insert(i);
        list2.print();
    }

    // 测试查找
    std::cout << "测试查找" << std::endl;
    static_list<int, 8> list3;
    for (int i = 0; i < 6; ++i)
        list3.insert(i);

    std::cout << (list3.find(3) ? "find it" : "not find") << std::endl;
    list3.erase(3);
    std::cout << (list3.find(3) ? "find it" : "not find") << std::endl;

}