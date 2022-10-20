#pragma once

#include <iostream>

class point;

std::ostream& operator<<(std::ostream&, const point&);

class point {
public:
    point(const int& x = 0, const int& y = 0) : _x(x), _y(y) {}

    void axis_x(const int& x) { _x = x; }
    void axis_y(const int& y) { _y = y; }

    int axis_x() const { return _x; }
    int axis_y() const { return _y; }

    auto operator[](const int i) const { return i ? _y : _x; }

private:
    int _x, _y;

    friend std::ostream& operator<<(std::ostream&, const point&);
};

inline std::ostream& operator<<(std::ostream& os, const point& x) { return os << "(" << x._x << "," << x._y << ")"; }