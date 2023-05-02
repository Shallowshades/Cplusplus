#include <iostream>

using namespace std;

void func1(int& x) {
    ++x;
}

void func2(int* x) {
    ++* x;
}

int main(){

    int x = 1;
    func1(x);
    func2(&x);

    return 0;
}
