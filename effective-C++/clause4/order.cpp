#include <iostream>
#include <cstdlib>

using namespace std;

class animal {
public:
    animal() { cout << "This is animal class structure!\n"; }
    virtual void speak() = 0;
    virtual ~animal() { "~animal()\n"; };
};

class cat: public animal {
public:
    cat() { cout << "This is cat class structure!\n"; }
    void speak() { cout << "cat speak: miaomiaomiao!\n"; }
    cat(const cat& c) {
        cout << "cat(const cat&)\n";
    }

    ~cat() { cout << "~cat()\n"; }
};

class dog: public animal {
public:
    dog() { cout << "This is dog class structure!\n"; }
    void speak() { cout << "dog speak: wangwangwang!\n"; }
    dog(const dog& d) {
        cout << "dog(const dog&)\n";
    }

    ~dog() { cout << "~dog()\n"; }
};

class pet: public animal {
public:
    pet(const dog& d, const cat& c):_d(d), _c(c) { cout << "This is pet class structure!\n"; }
    void speak() { cout << "pet speak: ????\n"; }

    ~pet() { cout << "~pet()\n"; }

    cat _c;
    dog _d;
};

int main() {

    dog d;
    cat c;
    {
        cout << " --------\n";
        pet p(d, c);            //继承父类 组合成员 子类自身
        cout << " --------\n";
        /*
            This is animal class structure!
            This is animal class structure!
            cat(const cat&)
            This is animal class structure!
            dog(const dog&)
            This is pet class structure!
        */
    }

    return 0;

}