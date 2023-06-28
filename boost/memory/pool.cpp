/**
 *@file pool.cpp
 * @author your name (you@domain.com)
 * @brief 内存池
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>

#include <boost/optional/optional.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>

using namespace std;
using namespace boost;

/// @brief object_pool 测试类1
class demo1 {
public:
    demo1(const int n = 1, const double d = 2.0, const int p = 0)
        : m_nVal(n), m_dVal(d), m_pVal(new int(p)), m_bInitialized(make_optional(true)) {
        std::cout << "demo : new" << std::endl;
    }
    ~demo1() {
        if (m_pVal != nullptr)
            delete m_pVal;
        std::cout << "demo : deleted" << std::endl;
    }

    bool initialized() const { return m_bInitialized.is_initialized(); }
    void print() const {
        std::cout << m_nVal << "\t";
        std::cout << m_dVal << "\t";
        std::cout << *m_pVal << "\t";
        std::cout << boolalpha << m_bInitialized.value_or(false) << std::endl;
    }
private:
    int m_nVal;
    double m_dVal;
    int* m_pVal;
    optional<bool> m_bInitialized;
};

/// @brief object_pool 测试类1
class demo2 {
public:
    demo2(const int n = 1, const double d = 2.0, const char c = 'a', const int p = 0)
        : m_nVal(n), m_dVal(d), m_cVal(c), m_pVal(new int(p)), m_bInitialized(make_optional(true)) {
        std::cout << "demo : new" << std::endl;
    }
    ~demo2() {
        if (m_pVal != nullptr)
            delete m_pVal;
        std::cout << "demo : deleted" << std::endl;
    }

    bool initialized() const { return m_bInitialized.is_initialized(); }
    void print() const {
        std::cout << m_nVal << "\t";
        std::cout << m_dVal << "\t";
        std::cout << m_cVal << "\t";
        std::cout << *m_pVal << "\t";
        std::cout << boolalpha << m_bInitialized.value_or(false) << std::endl;
    }
private:
    int m_nVal;
    double m_dVal;
    char m_cVal;
    int* m_pVal;
    optional<bool> m_bInitialized;
};

/// @brief 自定义object_pool的构造函数，可以接受任意数量的参数
/// @tparam P object_pool
/// @tparam ...Args 可变参数类型包
/// @param p object_pool实例
/// @param ...args 可变参数包
/// @return object_pool模板类型的实例指针
template<typename P, typename ... Args>
inline typename P::element_type* construct(P& p, Args&& ... args) {
    typename P::element_type* mem = p.malloc();
    assert(mem != nullptr);
    new (mem) typename P::element_type(std::forward<Args>(args)...);    //指定内存位置构造 + 完美转发
    return mem;
}

int main() {

    //pool 只能用于普通数据类型 不调用构造函数
    {
        pool<> p1(sizeof(int));
        int* p = static_cast<int*>(p1.malloc());
        cout << boolalpha << p1.is_from(p) << endl;

        cout << p1.get_max_size() << endl;
        cout << p1.get_next_size() << endl;
        cout << p1.get_requested_size() << endl;

        p1.free(p);
        for (int i = 0;i < 100; ++i) p1.ordered_malloc(10);

        cout << p1.get_max_size() << endl;
        cout << p1.get_next_size() << endl;
        cout << p1.get_requested_size() << endl;
    }

#ifdef PROTO
    //object_pool 可用于对象 最多支持3个构造参数
    {
        //TODO：运行此处 退出代码错误
        object_pool<demo1> po;
        auto p = po.malloc();

        assert(po.is_from(p));

        //TODO: 未调用construct之前optional已经初始化了
        //std::cout << boolalpha << p->initialized() << std::endl;
        //p->print();

        p = po.construct(3, 3.14, 4);
        p->print();
    }
#else
    //可变参数模板
    {
        object_pool<demo2> po;
        auto p = construct(po, 5, 6.0, 'b', 7);
        p->print();
    }
#endif // PROTO

    //singleton_pool成员函数大都是静态，不需要声明定义，生命周期和程序的生命周期相同
    {
        struct pool_tag {};
        using spo = singleton_pool<pool_tag, sizeof(int)>;
        int* p = static_cast<int*>(spo::malloc());
        assert(spo::is_from(p));
        spo::release_memory();
    }

    return 0;
}























