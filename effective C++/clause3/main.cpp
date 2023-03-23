/**
 * @file clause3.cpp
 * @author your name (you@domain.com)
 * @brief 尽可能使用const
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

//有理数
class Rational {};
const Rational operator * (const Rational& lhs, const Rational& rhs) {
    return Rational();
}
const bool operator == (const Rational& lhs, const Rational& rhs) {
    return true;
}

//文本块
class TextBlock {
public:
    TextBlock(const string& str = ""):text(str) {}
    const char& operator[](std::size_t pos) const {
        return text[pos];
    }
    //non-const调用const 避免代码的重复
    char& operator [](std::size_t pos) {
        //static_cast<const TextBlock&>(*this) -> const TextBlock&, 从而调用const版本 operator[]
        //const_cast<char&>(const char) -> char&,返回non-const char&
        return const_cast<char&>(static_cast<const TextBlock&>(*this)[pos]);
    }

    //一定要non-const调用const
    //因为可以修改的变量，可以修改，也可以不修改；但是不可以修改的变量，就不可以修改

private:
    std::string text;
};

void print(const TextBlock& ctb) {
    std::cout << ctb[0] << std::endl; //const
}

class CTextBlock {
public:
    CTextBlock(const char* const str) {
        pText = (char*)malloc(sizeof(char) * strlen(str));
        strcpy(pText, str);
    }
    //此处const只能保证在该函数内不能修改
    //inappropriate(but bitwise const)declaration of operator[]
    char& operator[](std::size_t pos)const {
        return pText[pos];
    }

    const string toString() const {
        return string(pText);
    }

    //只能在单线程情况,多线程加互斥量
    //此函数为常函数，但是又希望其在某些情况可以修改某些变量，那些被修改的变量加上mutable修饰符
    std::size_t CTextBlock::length() const {
        if (!lengthIsValid) {
            textLength = std::strlen(pText);//OK
            lengthIsValid = true;//OK
        }
        return textLength;
    }
private:
    char* pText;
    mutable std::size_t textLength;
    mutable bool lengthIsValid;
    //these data members may always be modified, even in const member functions
};

int main() {

    //const and pointer
    {
        char greeting[] = "Hello";
        char* p1 = greeting;
        const char* p2 = greeting;
        char* const p3 = greeting;
        const char* const p = greeting;

        std::cout << greeting << std::endl;
        greeting[3] = '#';
        std::cout << greeting << std::endl;
    }

    //vector
    {
        std::vector<int> vec({ 1,2,3,4,5,6 });
        const auto iter = vec.begin(); //iter like a `T* const`
        *iter = 10; //OK
        //++iter;   //error 没有与这些操作数匹配的 "++"运算符,没有++的常函数，也可能有

        auto citer = vec.cbegin();  //citer like a `const T*`
        //std::vector<int>::const_iterator
        // \*citer = 10;            //表达式必须是可修改的左值
        ++citer;                    //OK
    }

    //意外错误
    {
        Rational a, b, c;
        //...
        //(a * b) = c; //operator* 返回值不加const，此处将成功编译 

        if (a * b == c) {
            //若此处少写一个等号，且该类型又可以隐式转换为bool类型，将存在安全隐患
            //...
        }
    }

    //常函数
    {
        TextBlock tb("Hello");
        std::cout << tb[0] << std::endl;//non-const
        const TextBlock ctb("World");
        std::cout << ctb[0] << std::endl;//const

        tb[0] = 'x'; //OK
        //ctb[0] = 'x'; //error

        print(tb);
        print(ctb);
    }

    //C出问题的情况
    {
        const CTextBlock cctb("Hello");//declare constant object
        std::cout << cctb.toString() << std::endl;
        char* pc = &cctb[0];//call the const operator[] to get a pointer to cctb's data
        *pc = 'J';//cctb now has the value "Jello"
        std::cout << cctb.toString() << std::endl;
    }
    return 0;
}

/*
    1.将某些东西声明为const可以帮助编译器侦测出错误用法。
        const可以施加于`任何作用域内的对象`，`函数参数`，`函数返回类型`，`成员函数本体`
    2.编译器强制实施bitwise constness，但是编写程序时应该使用“概念上的常量性”（conceptual constness）
    3.当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复
*/