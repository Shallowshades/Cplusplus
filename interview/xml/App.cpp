// App.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "FileParse.h"

const int inf = 0x3f3f3f3f;

using namespace std;

int main() {

	FileParse file("./input.txt");
	file.parse();
	file.print();
	return 0;
}
