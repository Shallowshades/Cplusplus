/**
 *@file com.cpp
 * @author your name (you@domain.com)
 * @brief C++对象模型
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <cxxabi.h>

using namespace std;

class point {
public:
    point(float xval):_x(xval) {}
    virtual ~point() {}

    float x()const { return _x; }
    static int pointCount() { return _point_count; }
    //size_t addr() const { return &_x; }
    float _x;
protected:
    virtual ostream& print(ostream& os)const { return os << _x; }
    static int _point_count;
};

inline ostream& operator << (ostream& os, const point& pt) { return os << pt.x(); }

int main() {

    point* p1 = new point(3.14);
    //p1->print();
    cout << *p1 << endl;
    cout << "sizeof(p1) = " << sizeof(p1) << endl;
    cout << "sizeof(*p1) = " << sizeof(*p1) << endl;
    cout << "p1 = " << p1 << endl;
    cout << "&p1->_x = " << &(p1->_x) << endl;

    cout << typeid(*p1).name() << endl;
    //cout << typeid(*p1).before(typeid(*p1)) << endl;typeid
    cout << typeid(*p1).hash_code() << endl;
    cout << boolalpha << typeid(*p1).__is_function_p() << endl;
    cout << boolalpha << typeid(*p1).__is_pointer_p() << endl;

    return 0;
}
