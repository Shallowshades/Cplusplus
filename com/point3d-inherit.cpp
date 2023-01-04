/**
 *@file point3d-inherit.cpp
 * @author your name (you@domain.com)
 * @brief C++通过一个三层结构完成一个对象
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

using namespace std;

class point {
public:
    point(float x = 0.0):_x(x) {}

    float x() const { return _x; }

    void x(float xval) { _x = xval; }

    //etc...
protected:
    float _x;
};

class point2d: public point {
public:
    point2d(float x = 0.0, float y = 0.0): point(x), _y(y) {}

    float y() const { return _y; }

    void y(float yval) { _y = yval; }

    //etc...
protected:
    float _y;
};

class point3d: public point2d {
public:
    point3d(float x = 0.0, float y = 0.0, float z = 0.0):point2d(x, y), _z(z) {}

    float z() const { return _z; }

    void z(float zval) { _z = zval; }

    //etc...
protected:
    float _z;
};

inline ostream& operator << (ostream& os, const point3d& pt) {
    return os << "(" << pt.x() << "," << pt.y() << "," << pt.z() << ")";
}

int main() {

    point3d* p1 = new point3d(1, 2, 3);
    //cout << p1 << endl;
    cout << *p1 << endl;

    p1->x(2);
    p1->y(4);
    p1->z(6);

    //cout << p1 << endl;
    cout << *p1 << endl;

    return 0;
}