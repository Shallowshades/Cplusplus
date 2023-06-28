/**
 *@file scoped_ptr.cpp
 * @author your name (you@domain.com)
 * @brief scoped_ptr智能指针 相较于标准库的unique_ptr
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>

using namespace std;
using namespace boost;

class ptr_owned final {
public:
    scoped_ptr<int> m_ptr;      //持有scoped_ptr的对象也不可拷贝和赋值
};

struct posix_file {
    posix_file(const char* file_name) { cout << "Open file:" << file_name << endl; }
    ~posix_file() { cout << "close file" << endl; }
};

int main() {

    //基本用法
    {
        scoped_ptr<string> sp(new string("text"));
        assert(sp);
        assert(sp != nullptr);

        cout << *sp << endl;
        cout << sp->size() << endl;
    }

    //不可拷贝和赋值，拥有它的对象也会被限制
    {
        ptr_owned p1;
        //ptr_owned p2 = p1;    //error
    }

    //一种用法
    {
        scoped_ptr<posix_file> fp(new posix_file("/boost/boost.h"));
        scoped_ptr<int> p(new int);

        //检测是否拥有一个有效的指针，确切的说是一个资源（文件描述符、socket、操作系统handle、数据库连接）
        if (p) *p = 100, cout << *p << endl;

        //置空scoped_ptr, 建议不使用
        p.reset();

        //隐式转换为nullptr，判断scoped_ptr不拥有任何指针
        assert(p == 0);

        if (!p) cout << "scoped_ptr == nullptr" << endl;
    }

    //相比于unique_ptr(可以像原始指针一样比较，和shared_ptr一样定制删除器，也可以安全的放入标准容器)
    {
        unique_ptr<int> up(new int);
        assert(up);
        *up = 10;
        cout << *up << endl;

        up.reset();
        assert(!up);

        //工厂函数make_unique
        auto p1 = boost::make_unique<int>(10);
        auto p2 = std::make_unique<int>(10);
        assert(p1 && *p1 == 10);
        assert(p2 && *p2 == 10);
    }

    return 0;
}