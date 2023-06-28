/**
 *@file intrusive_ptr.cpp
 * @author your name (you@domain.com)
 * @brief 自定义引用计数的智能指针
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>

using namespace std;
using namespace boost;

namespace impl {
    /// @brief 自定义数据类型， 包含一个引用计数变量
    struct counted_data {
        int m_nCount = 0;

        counted_data() : m_nCount(0) { cout << "构造成功\n"; }
        ~counted_data() { cout << "析构成功\n"; }
    };

    /// @brief 回调函数 添加引用计数
    /// @param p 实例的指针
    void intrusive_ptr_add_ref(counted_data* p) { ++p->m_nCount; }
    /// @brief 回调函数 释放引用计数
    /// @param p 实例的指针
    void intrusive_ptr_release(counted_data* p) { if (!--p->m_nCount) delete p; }
};

namespace inhert {
    /// @brief 自定义数据类型， 继承辅助计数类
    struct counted_data : public intrusive_ref_counter<counted_data> { //计数类的默认策略是线程安全
        counted_data() { cout << "构造成功\n"; }
        ~counted_data() { cout << "析构成功\n"; }
    };
}

int main() {

    //
    {
        using namespace impl;
        using counted_ptr = intrusive_ptr<counted_data>;

        counted_ptr p1(new counted_data);
        if (p1) cout << "构造成功\n";

        cout << "m_nCount = " << p1->m_nCount << endl;

        counted_ptr p2(p1);
        cout << "m_nCount = " << p2->m_nCount << endl;

        //TODO: 此处有问题 退出代码异常
        // counted_ptr weak_p(p1.get(), false);
        // cout << "m_nCount = " << weak_p->m_nCount << endl;

        p2.reset();
        if (!p2) cout << "释放成功\n";
        cout << "m_nCount = " << p1->m_nCount << endl;
    }

    //
    {
        using namespace inhert;
        using counted_ptr = intrusive_ptr<counted_data>;

        counted_ptr p1(new counted_data);
        if (p1) cout << "构造成功\n";

        cout << "m_nCount = " << p1->use_count() << endl;

        counted_ptr p2(p1);
        cout << "m_nCount = " << p2->use_count() << endl;

        //TODO: 此处有问题 退出代码异常
        // counted_ptr weak_p(p1.get(), false);
        // cout << "m_nCount = " << weak_p->use_count() << endl;

        p2.reset();
        if (!p2) cout << "释放成功\n";
        cout << "m_nCount = " << p1->use_count() << endl;
    }

    return 0;
}