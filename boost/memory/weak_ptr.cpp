/**
 *@file weak_ptr.cpp
 * @author your name (you@domain.com)
 * @brief 弱指针,协助shared_ptr工作
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <algorithm>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from.hpp>

using namespace boost;

/// @brief 自我管理类 继承enable_shared_from_this
class self_shared : public enable_shared_from_this<self_shared> {
public:
    self_shared(int val) : m_nVal(val) {}
    int getValue() const { return m_nVal; }
    void setValue(int val) { m_nVal = val; }
    void print() const { std::cout << "self_shared : " << m_nVal << std::endl; }
private:
    int m_nVal;
};

class node {
public:
    using ptr_type = weak_ptr<node>;    //!shared_ptr

    node() = default;
    ~node() { std::cout << "node : deleted" << std::endl; }

    ptr_type getNext() const { return m_pNext; }
    void setNext(ptr_type next) { m_pNext = next; }
private:
    ptr_type m_pNext;
};

int main() {

    //基本用法
    {
        shared_ptr<int> sp(new int(10));
        std::cout << sp.use_count() << std::endl;

        weak_ptr<int> wp = sp;
        std::cout << wp.use_count() << std::endl;

        if (!wp.expired()) {
            shared_ptr<int> sp2 = wp.lock();
            *sp2 = 100;
            std::cout << sp.use_count() << std::endl;
        }

        std::cout << sp.use_count() << std::endl;

        sp.reset();
        std::cout << sp.use_count() << std::endl;

        assert(wp.expired());
        assert(!wp.lock());

        std::cout << std::boolalpha << wp.expired() << std::endl;
        std::cout << std::boolalpha << (wp.lock() == nullptr) << std::endl;
    }

    //对象的自我管理
    {
        shared_ptr<self_shared> sp = make_shared<self_shared>(313);
        sp->print();

        shared_ptr<self_shared> sp2 = sp->shared_from_this();
        sp2->setValue(1000);
        sp->print();
    }

    //打破循环引用
    {
        auto p1 = make_shared<node>();
        auto p2 = make_shared<node>();

        p1->setNext(p2);
        p2->setNext(p1);

        std::cout << p1.use_count() << std::endl;
        std::cout << p2.use_count() << std::endl;
    }

    return 0;
}