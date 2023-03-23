/**
 *@file point3d-parameter.cpp
 * @author your name (you@domain.com)
 * @brief 参数化
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <cassert>

using namespace std;

/**
 *@brief 坐标类型参数化
 *
 * @tparam T 坐标类型
 */
template <typename T>
class point3d {
public:
    point3d(T x = 0.0, T y = 0.0, T z = 0.0):_x(x), _y(y), _z(z) {}

    T x() const { return _x; }
    T y() const { return _y; }
    T z() const { return _z; }

    void x(T xval) { _x = xval; }
    void y(T yval) { _y = yval; }
    void z(T zval) { _z = zval; }

    //etc...
private:
    T _x;
    T _y;
    T _z;
};

template<typename T>
inline ostream& operator << (ostream& os, const point3d<T>& pt) {
    return os << "(" << pt.x() << "," << pt.y() << "," << pt.z() << ")";
}

/**
 *@brief 坐标类型，维度参数化
 *
 * @tparam T 坐标类型
 * @tparam dim 维度
 */
template <typename T, int dim>
class point {
public:
    point() {};
    point(T coords[dim]) {
        for (int i = 0;i < dim;++i) {
            _coords[i] = coords[i];
        }
    }

    T& operator [](int index) {
        assert(index < dim&& index >= 0);
        return _coords[index];
    }

    T operator[](int index)const {
        assert(index < dim&& index >= 0);
        return _coords[index];
    }

    //etc...
private:
    T _coords[dim];
};

template<typename T, int dim>
inline ostream& operator << (ostream& os, const point<T, dim>& pt) {
    os << "(";
    for (int i = 0;i < dim - 1;i++) {
        os << pt[i] << ",";
    }
    os << pt[dim - 1];
    os << ")";
    return os;
}

int main() {

    point3d<double>* p1 = new point3d<double>(1.0, 2.0, 3.0);
    cout << p1 << endl;
    cout << *p1 << endl;

    p1->x(2.0);
    p1->y(4.0);
    p1->z(6.0);
    cout << p1 << endl;
    cout << *p1 << endl;

    float coords[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    point<float, 5>* p2 = new point<float, 5>(coords);
    point<float, 5>* p3 = new point<float, 5>();

    cout << p2 << endl;
    cout << *p2 << endl;

    cout << p3 << endl;
    cout << *p3 << endl;

    return 0;
}