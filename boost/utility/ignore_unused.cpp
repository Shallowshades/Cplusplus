#include <iostream>
#include <boost/core/ignore_unused.hpp>

using namespace std;
using namespace boost;

int func1(int x, int y) {
    int i;

    ignore_unused(x, i);

    return y;
}

int main() {

    func1(1, 1);

    return 0;
}
