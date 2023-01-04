/**
 * @file point3d-adt.cpp
 * @author your name (you@domain.com)
 * @brief 在C++中，通过ADT(abstract data type)实现一个对象
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

using namespace std;

class point3d {
public:
    point3d(float x = 0.0, float y = 0.0, float z = 0.0):_x(x), _y(y), _z(z) {}

    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }

    void x(float xval) { _x = xval; }
    void y(float yval) { _y = yval; }
    void z(float zval) { _z = zval; }

    //etc...
private:
    float _x;
    float _y;
    float _z;
};

inline ostream& operator << (ostream& os, const point3d& pt) {
    return os << "(" << pt.x() << "," << pt.y() << "," << pt.z() << ")";
}

int main() {

    point3d* p1 = new point3d(1, 2, 3);

    cout << p1 << endl;
    cout << *p1 << endl;

    p1->x(2);
    p1->y(4);
    p1->z(6);

    cout << p1 << endl;
    cout << *p1 << endl;

    return 0;
}