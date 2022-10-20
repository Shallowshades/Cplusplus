//多态
#include <iostream>
#include <cstdlib>

using namespace std;

class animal {
public:
	animal(){ cout<<"This is animal class structure!\n";}
    virtual void speak() = 0;
};

class cat : virtual public animal {
public:
	cat(){ cout<<"This is cat class structure!\n";}
    void speak() { cout << "cat speak: miaomiaomiao!\n"; }
};

class dog : virtual public animal {
public:
	dog(){ cout<<"This is dog class structure!\n";}
    void speak() { cout << "dog speak: wangwangwang!\n"; }
};

class monster : public dog, public cat{
public:
	monster(){ cout<<"This is monster class structure!\n";}
	void speak() { cout << "monster speak: ???\n"; }
};

void speak(animal* A) { A->speak(); }
void speak(animal& A) { A.speak(); }

int main(){

    //指针
    cat* c = new cat(); 
    speak(c);
    dog* d = new dog();
    speak(d);
	monster* m = new monster();
	speak(m);

	cout<<"---------------------\n";

    //引用
    cat _c;
    speak(&_c);
    dog _d;
    speak(&_d);
	monster _m;
	speak(_m);
    
	cout<<sizeof(animal)<<"\n";
	cout<<sizeof(cat)<<"\n";
	cout<<sizeof(dog)<<"\n";
	cout<<sizeof(monster)<<"\n";

    return 0;

}