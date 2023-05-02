#include <iostream>
#include <memory>

using namespace std;

int main() {

    auto ptr = make_shared<int>(int(7));
    cout << *ptr << endl;

    return 0;
}
