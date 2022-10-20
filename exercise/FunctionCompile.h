#pragma once

int func(void);
int func(int x);
int func(double x, char y);
int func(int x, double y, char z);
//void func(int x);//无法重载仅按返回值区分的函数

class A {
public:
	void func(void);
	virtual void func(int);
};

class B : public A {
public:
	void func();
	void func(int);
};

void testCompile() {
	func();
	func(5);
	func(2.5, 'k');
	func(2, 3.14, 'd');

	A a;
	B b;
	a.func();
	a.func(1);
	b.func();
	b.func(1);

	//"int __cdecl func(void)" (? func@@YAHXZ)
	//"int __cdecl func(int)" (? func@@YAHH@Z)
	//"int __cdecl func(double,char)" (? func@@YAHND@Z)
	//"int __cdecl func(int,double,char)" (? func@@YAHHND@Z)

	//"public: void __thiscall A::func(void)" (? func@A@@QAEXXZ)
	//"public: virtual void __thiscall A::func(int)" (? func@A@@UAEXH@Z)
	//"public: void __thiscall B::func(void)" (? func@B@@QAEXXZ)
	//"public: virtual void __thiscall B::func(int)" (? func@B@@UAEXH@Z)
}