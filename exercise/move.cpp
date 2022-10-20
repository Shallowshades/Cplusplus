//强制移动
//1、运算符static_cast<>将对象的类型强制转换为右值引用
//2、C++11头文件utility中声明的函数std::move()
#include <iostream>
#include <utility>

using namespace std;

class useless {
public:
	useless();									//default ctor
	explicit useless(int k);	
	useless(int k, char ch);
	useless(const useless& u);					//copy ctor
	useless(useless&& u);						//move ctor
	~useless();									//default dtor
	useless operator + (const useless& u) const;
	useless operator = (const useless& u);		//copy assignment
	useless operator = (useless&& u);			//move assignment
	void ShowData() const;
private:
	int n;						//number of element
	char* pc;					//pointer to data
	static int ct;				//number of object
	void ShowObject() const;
};

//implementation
int useless::ct = 0;

useless::useless() {
	++ct;
	n = 0;
	pc = nullptr;
}

useless::useless(int k) : n(k) {
	++ct;
	pc = new char[n];
}

useless::useless(int k, char ch) :n(k) {
	++ct;
	pc = new char[n];
	for (int i = 0; i < n; ++i) pc[i] = ch;
}

useless::useless(const useless& u) :n(u.n) {
	++ct;
	pc = new char[n];
	for (int i = 0; i < n; ++i) pc[i] = u.pc[i];
}

useless::useless(useless&& u) : n(u.n) {
	++ct;
	pc = u.pc;			//steal address
	u.pc = nullptr;		//give old object nothing in return
	u.n = 0;
}

useless::~useless(){
	delete[] pc;
}

useless useless::operator + (const useless& u) const {
	useless temp = useless(n + u.n);
	for (int i = 0; i < n; ++i) temp.pc[i] = pc[i];
	for (int i = n; i < temp.n; ++i) temp.pc[i] = u.pc[i - n];
	return temp;
}

useless useless::operator=(const useless& u) {
	cout << "copy assignment operator called:\n";
	if (this == &u) return *this;
	delete[] pc;
	n = u.n;
	pc = new char[n];
	for (int i = 0; i < n; ++i) pc[i] = u.pc[i];
	return *this;
}

useless useless::operator = (useless&& u) {
	cout << "move assignment operator called:\n";
	if (this == &u) return *this;
	delete[] pc;
	n = u.n;
	pc = u.pc;
	u.n = 0;
	u.pc = nullptr;
	return *this;
}

void useless::ShowData() const {
	if (!n) cout << "(object empty)";
	else
		for (int i = 0; i < n; ++i) cout << pc[i];
	cout << endl;
}

void useless::ShowObject() const {
	cout << "Number of elements: " << n;
	cout << " Data address: " << (void*)pc << endl;
}

//application
int main() {

	{
		useless one(10, 'x');
		useless two = one + one;			//calls move ctor
		cout << "object one: ";
		one.ShowData();
		cout << "object two: ";
		two.ShowData();

		useless three, four;
		cout << "three = one\n";
		three = one;						//automatic copy assignment
		cout << "now object three = ";
		three.ShowData();
		cout << "and object one = ";
		one.ShowData();
		cout << "four = one + two\n";
		four = one + two;					//automatic move assignment
		cout << "now object four = ";
		four.ShowData();
		cout << "four = move(one)\n";
		four = move(one);					//forced move assignment
		cout << "now object four = ";
		four.ShowData();
		cout << "and object one = ";
		one.ShowData();
		
		cout << "\n---------------------\n";
		cout << "four = static_cast<useless&&>(two)\n";
		four = static_cast<useless&&>(two);	//forced move assignment
		cout << "now object four = ";
		four.ShowData();
		cout << "and object two = ";
		two.ShowData();
	}

	return 0;
}