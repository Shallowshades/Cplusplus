#include "point.h"
#include <iostream>

using namespace std;

class circle;

ostream& operator<<(ostream&, const circle&);

class circle {
public:
    circle(const point& center = point(0, 0), const int& radius = 0) : _center(center), _radius(radius) {}

    point center() const { return _center; }
    int   radius() const { return _radius; }

    void center(const point& center) { _center = center; }
    void radius(const int& radius) { _radius = radius; }

private:
    int   _radius;
    point _center;

    friend ostream& operator<<(ostream&, const circle&);
};

inline ostream& operator<<(ostream& os, const circle& x) { return os << x._center << " " << x._radius; }

void relationship(const circle& c, const point& p) {
    int d1 = (c.center().axis_x() - p.axis_x()) * (c.center().axis_x() - p.axis_x()) + (c.center().axis_y() - p.axis_y()) * (c.center().axis_y() - p.axis_y());
    int d2 = c.radius() * c.radius();
    if(d1 > d2)
        cout << "点在圆外\n";
    else if(d1 == d2)
        cout << "点在圆上\n";
    else
        cout << "点在圆内\n";
}

int main() {

    point p1(0, 0);

    circle c1(p1, 5);
    circle c2((0, 0), 5);

    point p2(0, 1);
    point p3(0, 5);
    point p4(12, 12);

    relationship(c1, p2);
    relationship(c1, p3);
    relationship(c1, p4);

    relationship(c2, p2);
    relationship(c2, p3);
    relationship(c2, p4);

    cout << p1 << "\n";
    cout << c1 << "\n";

    cout << c2 << "\n";

    point p5(9, 129);
    std::cout << "override [] : \n";
    std::cout << p5[0] << std::endl;
    std::cout << p5[1] << std::endl;

    return 0;
}