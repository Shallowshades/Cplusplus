#include <iostream>
#include <string>

using namespace std;

class person;

ostream& operator << (ostream& os, const person& p);

class person;

class person {
public:
	//构造函数的分类
	//按照参数：有参 无参 （无参又称为默认构造函数）
	//按照类型：普通 拷贝

	//c++中拷贝构造函数调用时机通常有三种情况
	//使用一个已经创建完毕的对象来初始化一个新对象
	//值传递的方式给函数参数传值
	//以值方式返回局部对象 (值返回：先拷贝一个新对象，再析构局部对象，再将接受者关联到新对象)

	//默认情况下，c++编译器至少给一个类添加3个函数
	//1.默认构造函数(无参，函数体为空)
	//2.默认析构函数(无参，函数体为空)
	//3.默认拷贝构造函数, 对属性进行值拷贝
	//构造函数调用规则如下 :
	//如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
	//如果用户定义拷贝构造函数，c++不会再提供其他构造函数

	//拷贝函数的深拷贝和浅拷贝
	//编译器提供的默认拷贝函数是浅拷贝，就是做简单的赋值操作
	//自己实现拷贝构造函数，解决浅拷贝带来的问题（指针），在堆区申请新的内存为深拷贝

	//浅拷贝可能带来的问题
	//堆区内存的重复释放

	//构造函数的初始化列表
	//传统赋值初始化相当于，先声明类再赋值
	//初始化列表相当于，直接声明了一个带初始值的对象，省略了赋值操作
	//在大型项目中，class类中成员变量极多的情况下，初始化列表效率更高

	//当其他类对象作为类成员时，先构造其他类，再构造本类（砖 -> 房）
	//析构的顺序与构造相反，因为栈区是先进后出filo

	//静态成员(static)分为:

	//静态成员变量
	//所有对象共享一份数据
	//在编译阶段分配内存(全局区)
	//类内声明，类外初始化
	//两种访问方式：1、通过对象进行访问；2、通过类名进行访问
	
	//静态成员函数
	//所有对象共享一个函数
	//静态成员函数只能访问静态成员变量，不可以访问非静态成员变量(无法区分非静态成员变量属于哪一个对象)


	person() { cout << "无参构造函数\n"; }
	person(const int& age) :_age(age) { cout << "有参构造函数\n"; }
	person(const person& p) : _age(p._age) { cout << "拷贝构造函数\n"; }

	~person() { cout << "析构函数\n"; } //将堆区开辟的数据内存释放

private:
	int _age;
	friend ostream& operator << (ostream& os, const person& p);
};

inline ostream& operator << (ostream& os, const person& p) { return os << "age = " << p._age; }

person test(const person p) { return p; }

int  main() {

	cout << "拷贝传递测试------\n";
	person p;
	person p0 = test(p); //值传递时触发第一次拷贝，值返回时触发第二次拷贝，但是在被拷贝变量析构之前
	cout << "拷贝传递测试------\n";


	person p1; //调用默认构造函数,不加() 
	//person p1(); //编译器会认为是一个函数声明
	person p2(10);
	person p3(p2);

	person p4 = p3;

	cout << "匿名对象------------\n";
	person(20); //匿名对象，此行结束，编译器会回收此对象
	//person(p4); //不要利用拷贝构造函数初始化匿名函数，编译器会编译成 person p4，造成重复定义
	cout << "匿名对象------------\n";

	cout << p1 << "\n";
	cout << p2 << "\n";
	cout << p3 << "\n";
	cout << p4 << "\n";

	//显示构造函数调用
	person p5 = person(20);
	person p6 = person(p5);

	//隐式构造函数调用
	person p7 = 30;  //preson p7 = person(30);
	person p8 = p7;  //person p8 = person(p7);

	cout << p5 << "\n";
	cout << p6 << "\n";
	cout << p7 << "\n";
	cout << p8 << "\n";

	return 0;
}