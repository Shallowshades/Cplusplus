/**
 *@file point3d-struct.cpp
 * @author your name (you@domain.com)
 * @brief C语言风格实现一个对象
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

using namespace std;

struct point3d {
    float x, y, z;
};

#define POINT3D_PRINT(pd) printf("(%g %g %g)\n", pd->x, pd->y, pd->z);
#define X(p,xval) (p->x) = (xval)
#define Y(p,yval) (p->y) = (yval)
#define Z(p,zval) (p->z) = (zval)

void point3d_print(const point3d* pd) {
    printf("(%g %g %g)\n", pd->x, pd->y, pd->z);
}

void point3d_print(const point3d pd) {
    printf("(%g %g %g)\n", pd.x, pd.y, pd.z);
}

int main() {

    point3d* p1 = new point3d();
    point3d* p2 = new point3d({ 1.6, 2.4, 5.6 });
    point3d_print(p1);
    point3d_print(p2);

    POINT3D_PRINT(p1);
    POINT3D_PRINT(p2);

    X(p1, 2);
    Y(p1, 8);
    Z(p1, 3);
    POINT3D_PRINT(p1);

    point3d p3 = *p2;
    //POINT3D_PRINT(p3);
    point3d_print(p3); //唯独函数可以通过重载区分指针和值
    //X(p3, 3.2);

    return 0;
}