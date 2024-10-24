#include <iostream>
#include <array>
#include <bitset>
using namespace std;

class A {
    virtual void func() { std::cout << "class A" << std::endl; }
};

class B : public A {
    virtual void func() { std::cout << "class B" << std::endl; }
};

void check(A b) {
    std::cout << "Address of A b : " << *(void**)&b << std::endl;
}

void check(A* b) {
    std::cout << "Address of A* b : " << *(void**)b << std::endl;
}

int main() {

    bitset<1000> bs;
    array<int, 1000> arr;
    bs.set(500);
    std::cout << bs.all() << std::endl;
    std::cout << bs << std::endl;
    std::cout << sizeof(bs) * 8 << std::endl;
    std::cout << sizeof(arr) * 8 << std::endl;
    std::cout << typeid(bs).name() << std::endl;

    A a;
    B b;
    std::cout << "Address of A a : " << *(void**)&a << std::endl;
    std::cout << "Address of B b : " << *(void**)&b << std::endl;
    A c = b;
    std::cout << "Address of A b : " << *(void**)&c << std::endl;
    A& d = b;
    std::cout << "Address of A& b : " << *(void**)&d << std::endl;
    check(b);
    check(&b);

    return 0;
}
