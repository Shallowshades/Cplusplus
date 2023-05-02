/**
 * @file clause2.cpp
 * @author your name (you@domain.com)
 * @brief 尽量使用const,enum,inline替换#define
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>

using namespace std;

#define ASPECT_RATIO 1.653 //报错的时候只有1.653，根本不知道哪里出了问题
const double AspectRatio = 1.653;
const char* const authorName1 = "Scott Meyers"; //较次 两次const分别限定指针和内容
const std::string authorName2("Scott Meyers");  //较好

class GamePlayer1 {
private:
    static const int NumTurns = 5; //constant declaration
    int scores[NumTurns];
};

const int GamePlayer1::NumTurns;

class GamePlayer2 {
private:
    enum { NumTurns = 5 }; //"the enum hack",令NumTurns成为5的一个记号名称
    int scores[NumTurns];
};

/*
    1.enum hack的行为方面更像#define而不像const，例如取一个const地址是合法的，但是取一个enum、#define地址不合法
    2.enum hack是模板元编程的基础技术
*/

//function-like macro
#define CALL_WITH_MAX(a,b) f((a)>(b)?(a):(b)) 

void f(int val) {
    std::cout << val << std::endl;
}

//template
//包含在头文件中，加inline，否则报重复的错误
template<typename T>
inline void callWithMax(const T& a, const T& b) {
    f(a > b ? a : b);
}

int main() {

    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b); //f((++a)>(b)?(++a):(b))
    CALL_WITH_MAX(++a, b + 10); //f((++a)>(b+10)>(++a):(b+10))

    a = 5, b = 0;
    callWithMax(++a, b);
    callWithMax(++a, b + 10);

    return 0;
}

/*
    gcc -E a.c -o a.i # 预处理
    gcc -S a.i -o a.s # 编译
    gcc -c a.s -o a.o # 汇编
    gcc	a.o b.o -o a.out # 链接

    预处理 xx.i
    int a = 5, b = 0;
    f((++a)>(b)?(++a):(b));
    f((++a)>(b+10)?(++a):(b+10));

    对于单纯常量，最好以const对象或enum替换#define
    对于形似函数的宏（macros），最好改用inline函数替换#define
*/

