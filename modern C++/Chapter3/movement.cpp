/**
 * @file movement.cpp
 * @author your name (you@domain.com)
 * @brief 移动语义
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <array>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class A {
public:
    int* pointer;
    A() : pointer(new int(1)) { cout << "ctor" << pointer << endl; }
    A(const A& a) : pointer(new int(*a.pointer)) { cout << "copy" << pointer << endl; }
    A(A&& a) : pointer(a.pointer) {
        a.pointer = nullptr;
        cout << "move" << pointer << endl;
    }
    ~A() {
        cout << "dtor" << pointer << endl;
        delete pointer;
    }
};

//防止编译器优化
A return_rvalue(bool test) {
    A a, b;
    if(test)
        return a;  //等价于static_cast<A&&>(a)
    else
        return b;  //等价于static_cast<A&&>(b)
}

class String;
ostream& operator<<(ostream&, const String&);
class String {

    friend ostream& operator<<(ostream&, const String&);

public:
    char& operator[](unsigned int index) { return *(buffer + index); }
    char& operator[](unsigned int index) const { return *(buffer + index); }
    String() : buffer(nullptr), size(0u){};
    String(const char* str) {
        size = 0;
        while(str[size] != '\0') ++size;
        buffer = new char[size];
        for(int i = 0; i < size; ++i) buffer[i] = str[i];
    }
    String(const String& str) {
        buffer = new char[str.size];
        size   = str.size;
        for(int i = 0; i < str.size; ++i) *(buffer + i) = str[i];
    }
    String(String&& str) : buffer(str.buffer) {
        str.buffer = nullptr;
        str.size   = 0;
    }

    ~String() {
        delete buffer;
        buffer     = nullptr;
        this->size = 0;
    }

private:
    char*        buffer;
    unsigned int size;
};

ostream& operator<<(ostream& os, const String& str) {
    copy(str.buffer, str.buffer + str.size, ostream_iterator<char>(os));
    return os;
}

int main() {

    // 避免了无意义的拷贝构造，加强了性能
    {
        A obj = return_rvalue(false);
        cout << "obj:" << obj.pointer << endl;
        cout << *obj.pointer << endl;
        // 1).首先会在 return_rvalue 内部构造两个 A 对象，于是获得两个构造函数的输出；
        // 2).函数返回后，产生一个将亡值，被A的移动构造（A(A &&)）引用，从而延长生命周期，并将这个右值中的指针拿到，保存到了 obj 中，而将亡值的指针被设置为 nullptr，防止了这块内存区域被销毁。
    }

    //
    {
        cout << "--------------\n";
        std::string              str = "Hello world.";
        std::vector<std::string> v;

        // 将使用 push_back(const T&), 即产生拷贝行为
        v.push_back(str);
        // 将输出 "str: Hello world."
        std::cout << "str: " << str << std::endl;

        // 将使用 push_back(const T&&), 不会出现拷贝行为
        // 而整个字符串会被移动到 vector 中，所以有时候 std::move 会用来减少拷贝出现的开销
        // 这步操作后, str 中的值会变为空
        v.push_back(std::move(str));
        // 将输出 "str: "
        std::cout << "str: " << str << std::endl;
    }

    //
    {
        cout << "--------------\n";
        vector<string> v1(10000000);
        clock_t        start1 = clock();
        for(int i = 0; i < 10000000; ++i) {
            string str = "Hello, world.";
            v1.push_back(str);
        }
        clock_t end1 = clock();
        cout << (1.0 * end1 - start1) / CLOCKS_PER_SEC << endl;
        v1.clear();

        vector<string> v2(10000000);
        clock_t        start2 = clock();
        for(int i = 0; i < 10000000; ++i) {
            string str = "Hello, world.";
            v2.push_back(std::move(str));
        }
        clock_t end2 = clock();
        cout << (1.0 * end2 - start2) / CLOCKS_PER_SEC << endl;
        v2.clear();
    }

    {
        {
            cout << "--------------\n";
            clock_t start1 = clock();
            for(int i = 0; i < 1000000; ++i) {
                String str =
                    "Helloworlddaklsjdfalkfuaoirfkamfsaokfjaiofjalkfjasoifjsaklgjasoigusalkgjaslkgjhasgflkasjfljasflsjaldfjalfjalfjasfjlajflasjfdlasdjflkasjflkasdjflaksjflkasfjlkasfjalksfjlkasfjaslfja\
                    sdjflaskfjlkasfjlkasfjalsfjlkafjlksdjflkafjlkasfjdlakfjalkfjalksfjlkafjakfdjafjalskfjaklfjalksfjalkfjalksfjalkfjalkdfjlkasfjlkasfdjlkasfjalksfjalkfjalskfjalksdfjlaskfjal\
                    skdfjalsfjlasdfjalsfjaslkfjlasfjlaskfjlsad";
                String copy_str(str);
            }
            clock_t end1 = clock();
            cout << (1.0 * end1 - start1) / CLOCKS_PER_SEC << endl;

            clock_t start2 = clock();
            for(int i = 0; i < 1000000; ++i) {
                String move_str(String(
                    "Helloworlddaklsjdfalkfuaoirfkamfsaokfjaiofjalkfjasoifjsaklgjasoigusalkgjaslkgjhasgflkasjfljasflsjaldfjalfjalfjasfjlajflasjfdlasdjflkasjflkasdjflaksjflkasfjlkasfjalksfjlkasfjaslfja\
                    sdjflaskfjlkasfjlkasfjalsfjlkafjlksdjflkafjlkasfjdlakfjalkfjalksfjlkafjakfdjafjalskfjaklfjalksfjalkfjalksfjalkfjalkdfjlkasfjlkasfdjlkasfjalksfjalkfjalskfjalksdfjlaskfjal\
                    skdfjalsfjlasdfjalsfjaslkfjlasfjlaskfjlsad"));
            }
            clock_t end2 = clock();
            cout << (1.0 * end2 - start2) / CLOCKS_PER_SEC << endl;

            cout << String("Hello,world\n") << endl;
        }
    }

    return 0;
}