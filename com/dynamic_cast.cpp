#include <cassert>
#include <iostream>

using namespace std;

class A {
public:
    virtual void print() { std::cout << "A" << std::endl; }
};

class B {
public:
    virtual void print() { std::cout << "B" << std::endl; }
};

class C : public A, public B {
public:
    virtual void print() { std::cout << "C" << std::endl; }
};

int main() {
    // error case
    {
        C  c;
        A* a_ptr = dynamic_cast<A*>(&c);  // 成功，上行转换没有任何要求
        B* b_ptr = dynamic_cast<B*>(&c);  // 成功，上行转换没有任何要求

        // A a = dynamic_cast<A>(c);  // 错误，dynamic_cast无法用于转换类实例

        // C* c_ptra = dynamic_cast<C*>(a_ptr);  // 错误，类C不具备多态，无法进行下行转换
        // C* c_ptrb = dynamic_cast<C*>(b_ptr);  // 错误，类C不具备多态，无法进行下行转换
    }

    // + virtual function
    {
        C c;

        // 第一组
        A* a_ptr  = dynamic_cast<A*>(&c);
        B* b_ptr  = dynamic_cast<B*>(&c);
        C* c_ptra = dynamic_cast<C*>(a_ptr);  // 成功，类C具备多态性，可以使用dynamic_cast进行下行转换
        C* c_ptrb = dynamic_cast<C*>(b_ptr);  // 成功，类C具备多态性，可以使用dynamic_cast进行下行转换
        // 以下输出内容一致
        std::cout << &c << std::endl;
        std::cout << c_ptra << std::endl;
        std::cout << c_ptra << std::endl;

        // 第二组
        A  a;
        B  b;
        C* c_ptra1 = dynamic_cast<C*>(&a);  // 编译正常（好的编译器会给你个警告），转换结果为nullptr，说明转换失败
        C* c_ptrb1 = dynamic_cast<C*>(&b);  // 编译正常（好的编译器会给你个警告），转换结果为nullptr，说明转换失败
        assert(c_ptra1 == nullptr);
        assert(c_ptrb1 == nullptr);
        // 以下输出内容一致，都是0，说明c_ptra1和c_ptrb1都是nullptr
        if(c_ptra1 == nullptr) cout << "conversion failed\n";
        if(c_ptrb1 == nullptr) cout << "conversion failed\n";
        std::cout << c_ptra1 << std::endl;
        std::cout << c_ptrb1 << std::endl;
    }
    return 0;
}