#pragma once

#include <iostream>

using namespace std;

class B;
class A {
public:
	//shared_ptr<B> pb_;
	weak_ptr<B> pb_;
	~A()
	{
		cout << "A delete\n";
	}
};
class B {
public:
	//shared_ptr<A> pa_;
	weak_ptr<A> pa_;
	~B()
	{
		cout << "B delete\n";
	}

	void print() {
		cout << "B print()\n";
	}
};
void fun() {
	shared_ptr<B> pb(new B());
	shared_ptr<A> pa(new A());
	pb->pa_ = pa;
	pa->pb_ = pb;
	cout << pb.use_count() << endl;
	cout << pa.use_count() << endl;

	pa.reset();

	cout << pb.use_count() << endl;
	cout << pa.use_count() << endl;
	cout << pb->pa_.use_count() << endl;
}

void smartPoint() {
	//auto_ptr C++11������
	{
		auto_ptr<string> p1(new string("hello,world"));
		auto_ptr<string> p2 = p1;
		//cout << *p1 << endl; //ʹ��p1�ᱨ��
		cout << *p2 << endl;
	}

	//unique��ռ
	{
		unique_ptr<string> p1(new string("hello, world"));
		unique_ptr<string> p2(nullptr);
		//unique_ptr<string> p2 = p1;//����ʱ����
		//p2 = p1;// ��Ϊ��������Ϳ�����ֵ�����Ѿ���ɾ��
		cout << *p1 << endl;
		//cout << *p2 << endl;
	}

	//unique����ȡ��ʱ����
	{
		unique_ptr<string> p1(new string("hello, world"));
		unique_ptr<string> p2(nullptr);
		//p2 = p1;							//������������
		unique_ptr<string> p3(nullptr);
		p3 = unique_ptr<string>(new string("joker")); //����������
	}

	//ʹ��move��������
	{
		cout << "move-----------\n";
		unique_ptr<string> p1(new string("hello, world"));
		unique_ptr<string> p2(nullptr);
		p2 = move(p1);
		if (p1) {
			cout << *p1 << endl;
		}
		else {
			cout << "p1 is nullptr\n";
		}

		p1 = unique_ptr<string>(new string("joker"));
		cout << "*p1 = " << *p1 << "\n*p2 = " << *p2 << endl;
	}

	//����
	{
		cout << "shared_ptr----------------\n";
		shared_ptr<string> p1(new string("hello,world"));
		shared_ptr<string> p2 = p1;
		shared_ptr<string> p3(new string("joker"));
		cout << typeid(shared_ptr<string>::element_type).name() << endl;
		cout << "*p1 = " << *p1 << endl;
		cout << "*p3 = " << *p3 << endl;
		p1.swap(p3);
		cout << "*p1 = " << *p1 << endl;
		cout << "*p3 = " << *p3 << endl;
		cout << p2.use_count() << endl;

		p3.reset();
		cout << p2.use_count() << endl;
		if (p3 == nullptr) {
			cout << "p3 reset\n";
		}

		cout << boolalpha << p2.unique() << endl;
	}

	//weak_ptr
	{
		system("cls");
		cout << "weak_ptr----------\n";
		fun();

		//����ͨ��weak_ptrֱ�ӷ��ʶ���ķ���
		shared_ptr<B> pb(new B());
		shared_ptr<A> pa(new A());
		pb->pa_ = pa;
		pa->pb_ = pb;
		//pa->pb->print();//�޷�ʹ��
		shared_ptr<B> p = pa->pb_.lock();
		cout << p.use_count() << endl;
		p->print();
	}
}