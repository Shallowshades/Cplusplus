/**
 * @file shared_ptr.cpp
 * @author your name (you@domain.com)
 * @brief shared_ptr 最智能的智能指针
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;

/**
 *@brief shared_ptr的一个用法
 *
 */
class shared {
private:
    shared_ptr<int> p;
public:
    shared(shared_ptr<int> p_) : p(p_) {}
    void print() { cout << "count:" << p.use_count() << " v=" << *p << endl; }
};

void print_func(shared_ptr<int> p) {    //此时会再次拷贝构造一个共享指针
    cout << "count:" << p.use_count() << " v=" << *p << endl;
}

/**
 * @brief 桥接模式
 *
 */
class sample {
private:
    class impl;
    shared_ptr<impl> p;
public:
    sample();
    void print();
};

class sample::impl {
public:
    void print() { cout << "impl print" << endl; }
};

sample::sample() :p(new impl) {}
void sample::print() { p->print(); }

/**
 *@brief 工厂模式
 *
 */
class abstract {
public:
    virtual void f() = 0;
    virtual void g() = 0;
protected:
    virtual ~abstract() = default;
};

class impl : public abstract{
public:
    impl() = default;
    virtual ~impl() = default;
public:
    virtual void f() override { cout << "class impl f" << endl; }
    virtual void g() override { cout << "class impl g" << endl; }
};

inline shared_ptr<abstract> create() { return make_shared<impl>(); }

/**
 *@brief 定制删除器
 *
 */
class socket_t {};
socket_t* open_socket() {
    cout << "open_socket" << endl;
    return new socket_t;
}

void close_socket(socket_t* s) {
    cout << "close_socket" << endl;
}

int main() {

    //使用
    {
        shared_ptr<int> spi(new int);
        assert(spi);
        cout << *spi << endl;
        *spi = 253;

        shared_ptr<string> sps(new string("smart"));
        cout << sps->size() << endl;

        //!shared_ptr<int> dont_to_this(new int[10]); 不能正确释放内存
    }

    //引用计数 比较运算
    {
        shared_ptr<string> sps1(new string("shared"));
        shared_ptr<string> sps2 = sps1;
        shared_ptr<string> sps3 = sps1;
        cout << sps1.use_count() << endl;           //仅仅用于测试或者调试，不高效
        cout << boolalpha << sps1.unique() << endl; //安全，高效

        using sp_t = shared_ptr<string>;
        map<sp_t, int> m;
        sp_t sp(new string("one"));
        m[sp] = 111;
        cout << m[sp] << endl;
    }

    //基本用法， 线程安全
    {
        shared_ptr<int> sp(new int(10));
        assert(sp.unique());

        shared_ptr<int> sp2 = sp;
        assert(sp == sp2 && sp.use_count() == 2);

        *sp2 = 100;
        assert(*sp == 100);

        sp.reset();
        assert(!sp);
    }

    //复杂用法
    {
        shared_ptr<int> p(new int(100));
        shared s1(p), s2(p);
        s1.print();
        s2.print();

        *p = 20;

        print_func(p);

        s1.print();
    }

    //make_shared工厂函数，消除显式new
    {
        shared_ptr<string> sps = make_shared<string>("make_shared");
        shared_ptr<vector<int>> spv = make_shared<vector<int>>(100, 2);
        assert(spv->size() == 100);

        //allocate_shared 多接受一个定制的内存分配器
    }

    //应用于标准容器
    {
        using vs = vector<shared_ptr<int>>;
        vs v(10);
        for (auto& pos : v) {
            pos = make_shared<int>(1);
            cout << *pos << ", ";
        }
        cout << endl;
    }

    //桥接模式
    {
        ::sample s;
        s.print();
    }

    //工厂模式
    {
        auto p = create();
        p->f();
        p->g();

        {
            abstract* q = p.get();
            //!delete q;      "abstract::~abstract() noexcept" (已声明 所在行数:67) 不可访问
        }

        //"粗鲁"的方法可以获取并操作原始指针，但是不建议做（退出作用域后程序异常）
        {
            // impl* q = static_cast<impl*>(p.get());
            // delete q;
        }
    }

    //定制删除器
    {
        socket_t* s = open_socket();
        shared_ptr<socket_t> p(s, close_socket);
        //shared_ptr<socket_t> p(s, &close_socket); 相同

        //C文件操作
        //shared_ptr<FILE> fp(fopne("./scoped_ptr.cpp, "r), fclose);

    }

    return 0;
}