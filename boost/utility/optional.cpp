#include <iostream>
#include <optional>

using namespace std;

int main() {

    optional<bool> opt;

    if (opt.has_value())
        cout << opt.value() << endl;
    else
        cout << "no value" << endl;

    return 0;
}