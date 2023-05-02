#include <iostream>

using namespace std;

class IAnimal {
public:
    virtual void eat() = 0;
    virtual void sleep() = 0;
};

class dog: public IAnimal {
public:
    void eat() { cout << "dog eat...\n"; }
    void sleep() { cout << "dog sleep...\n"; }
};

class cat: public IAnimal {
public:
    void eat() { cout << "cat eat...\n"; }
    void sleep() { cout << "cat sleep...\n"; }
};

int main() {

    IAnimal* animal = new cat;
    animal->eat();
    animal->sleep();

    animal = new dog;
    animal->eat();
    animal->sleep();

    return 0;
}
