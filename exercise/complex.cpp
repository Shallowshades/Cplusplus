#include "complex.h"
#include <iostream>

using namespace std;

void test() {

	complex c1(2, 1);
	complex c2(4, 0);

	cout << c1 << "\n";
	cout << c2 << "\n";

	cout << c1 + c2 << "\n";
	cout << c1 - c2 << "\n";
	cout << c1 * c2 << "\n";
	cout << c1 / c2 << "\n";

	cout << conj(c1) << "\n";
	cout << norm(c1) << "\n";
	cout << polar(10, 4) << endl;

	cout << (c1 += c2) << endl;
	cout << (c1 -= c2) << endl;
	cout << (c1 *= c2) << endl;
	cout << (c1 /= c2) << endl;

	cout << (c1 == c2) << "\n";
	cout << (c1 != c2) << "\n";
	
	cout << +c2 << "\n";
	cout << -c2 << "\n";

	cout << (c2 - 2) << "\n";
	cout << (5 + c2) << "\n";
}
