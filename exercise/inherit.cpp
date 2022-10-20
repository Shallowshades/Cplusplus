// #include <iostream>
// #include <string>
// using namespace std;

// class Person {
// public:
// 	string name;
// protected:
// 	int age;
// private:
// 	int ID;
// };

// class Student_1 :public Person
// {
// public:
// 	void test()
// 	{
// 		cout << "name=" << name;
// 		cout << "age=" << age;
// 		cout << "ID=" << ID;
// 	}
// };

// class Student_2 :protected Person {
// public:
// 	void test()
// 	{
// 		cout << "name=" << name;
// 		cout << "age=" << age;
// 		cout << "ID=" << ID;
// 	}
// };

// class Student_3 :private Person {
// public:
// 	void test()
// 	{
// 		cout << "name = " << name;
// 		cout << "age = " << age;
// 		cout << "ID=" << ID;
// 	}
// };

// class Test :public Student_3 {
// public:
// 	void test()
// 	{
// 		cout << "name=" << name;
// 		cout << "age=" << age;
// 	}
// };

// int main()
// {
// 	Student_3 s;
// 	s.name = "hello";
// 	s.age = 12;
// 	return 0;
// }