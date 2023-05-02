/**
 *@file main.cpp
 * @author your name (you@domain.com)
 * @brief 安全实现赋值运算符
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

using namespace std;

class Bitmap {};
class Widget {
    //...
    void swap(Widget& rhs);
    Widget& operator= (const Widget& rhs);
    Widget& operator= (Widget rhs);
private:
    Bitmap* pb;
};

// rhs有可能等于 *this, 在自身赋值是出错
Widget& Widget::operator = (const Widget& rhs) {
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}

//1. 先判断再操作
Widget& Widget::operator= (const Widget& rhs) {
    if (this == &rhs) return *this;
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}

//2. 巧妙安排操作语句
Widget& Widget::operator= (const Widget& rhs) {
    Bitmap* temp = pb;
    pb = new Bitmap(*rhs.pb);
    delete temp;
    return *this;
}

//3. 利用swap
void Widget::swap(Widget& rhs) {

}

Widget& Widget::operator= (const Widget& rhs) {
    Widget temp(rhs);
    swap(temp);
    return *this;
}

//巧妙利用函数的局部变量
Widget& Widget::operator= (Widget rhs) {
    swap(rhs);
    return *this;
}

int main() {



    return 0;
}
