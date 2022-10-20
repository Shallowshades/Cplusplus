#include <iostream>
using namespace std;

class ABSCacutator {
public:
	int a, b;
	virtual void getResult() = 0;
};

class Add : public ABSCacutator {
public:
	void getResult() { cout << "add :" << a + b << "\n"; }
};

class Sub : public ABSCacutator {
public:
	void getResult() { cout << "sub :" << a - b << "\n"; }
};

void calc(ABSCacutator* cal, int a, int b) { cal->getResult(); }

int main() {
	
	

	return 0;
}
