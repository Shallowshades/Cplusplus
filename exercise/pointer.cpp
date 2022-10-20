#include <iostream>
using namespace std;
void fuck(int a, int b) {
	cout << "A = " << a << "\n";
	cout << "B = " << b << "\n";
}
void swap1(int a, int b) {
	int t = a; a = b; b = t;
}
void swap2(int& a, int& b) {
	int t = a; a = b; b = t;
}
int main() {
	int a = 10;
	int* p = &a;
	int** q = &p;

	cout << "&a = " << &a << "\n";
	cout << "a = " << a << "\n";

	cout << "&p = " << &p << "\n";
	cout << "p = " << p << "\n";

	cout << "&q = " << &q << "\n";
	cout << "q = " << q << "\n";
	cout << "*q = " << *q << "\n";
	cout << "**q = " << **q << "\n";

	double b = 10.0;
	double* c = &b;

	//32位系统中指针的大小都是4个字节 4byte 32bit
	cout << "sizeof int = " << sizeof(int) << "\n";
	cout << "sizeof *int = " << sizeof(int*) << "\n";
	cout << "sizeof double = " << sizeof(double) << "\n";
	cout << "sizeof *double = " << sizeof(double*) << "\n";

	//空指针
	int* d = NULL;

	//野指针
	int* e = (int*)0x12121311;

	//const 限定符
	const int* f = &a; //指向可变，值不可变
	int* const g = &a; //指向不可变，值可变
	const int* const h = &a; //指向不可变，值不可变

	//指针 与 数组
	int arr[8] = { 251,212,4,21,2,4,521,13 };
	int* l = arr;
	for (int i = 0; i < 8; i++) cout << l[i] << " "; cout << "\n";

	//指针 与 函数
	//传参 
	//1. 值传递
	//2. 地址传递

	int x1 = 10, x2 = 20;
	swap1(x1, x2);
	cout << "x1 = " << x1 << " x2 = " << x2 << "\n";

	int y1 = 40, y2 = 50;
	swap2(y1, y2);
	cout << "y1 = " << y1 << " y2 = " << y2 << "\n";

	//函数指针
	void (*pos)(int, int) = fuck; //函数指针
	//int* pos(int, int); //返回一个int指针
	pos(123321, 456654); 

	return 0;
}