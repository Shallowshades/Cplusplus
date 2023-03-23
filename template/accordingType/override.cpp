/**
 * @file override.cpp
 * @author your name (you@domain.com)
 * @brief C++通过重写（虚函数）实现不同类型不同操作
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;

class IAnimal{
public:
    virtual void yell() = 0;
};

class IDog : public IAnimal{
public:
    virtual void yell(){
        cout << "wangwang..." <<endl;
    }
};

class ICat : public IAnimal{
public:
    virtual void yell(){
        cout << "miaomiao..." << endl;
    }
};

IAnimal* GetAnimalFromSystem(){
    IAnimal* animal = new IDog;
    return animal;
}

int main(){

    IAnimal* animal = GetAnimalFromSystem();

    IDog* maybeDog = dynamic_cast<IDog*>(animal);
    if(maybeDog){
        maybeDog->yell();
    }
    ICat* maybeCat = dynamic_cast<ICat*>(animal);
    if(maybeCat){
        maybeCat->yell();
    }

    return 0;
}