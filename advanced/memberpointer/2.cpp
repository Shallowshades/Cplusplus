#include <iostream>
#include <string>

/*
    字面常量
*/

using namespace std;

std::string operator""_r(const char* str, size_t size) {
    //std::cout << str << "\t" << size << std::endl;
    return { str };
}

int main() {

    std::cout << "123456"_r << std::endl;


    return 0;
}
