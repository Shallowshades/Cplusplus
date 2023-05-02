/**
 *@file 15.cpp
 * @author your name (you@domain.com)
 * @brief 资源管理类中提供对原始资源的访问
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>

using namespace std;

class FontHandle {};
FontHandle getFont();
void releaseFont(FontHandle fh);

class Font {
public:
    explicit Font(FontHandle fh): f(fh) {}

    ~Font() { releaseFont(f); }
    FontHandle get() const {
        return f;
    }

    //转换函数
    // operator FontHandle() const {
    //     return f;
    // }

    explicit operator FontHandle() const {
        return f;
    }

private:
    FontHandle f;
};

int main() {

    Font f1(getFont());

    //FontHandle f2 = f1; //隐式调用转换函数

    FontHandle f3 = static_cast<FontHandle>(f1); //显示调用，引起注意

    return 0;
}
