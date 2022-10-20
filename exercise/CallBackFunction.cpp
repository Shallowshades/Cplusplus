#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template<typename T> void print(const T& elem) { cout << elem << "\n"; }

int main() {

	
	vector<int> v;
	for (int i = 0; i < 5; ++i) v.push_back(rand() % 256);

	//[] 下标遍历
	for (int i = 0; i < 5; ++i) cout << v[i] << "\n";
	//迭代器遍历
	vector<int>::iterator it = v.begin();
	while (it != v.end()) cout << *it++ << "\n";
	//算法for_each,回调函数print<T>遍历
	for_each(v.begin(), v.end(), print<int>);

	return 0;
}