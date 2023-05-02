/**
 *@file array.cpp
 * @author your name (you@domain.com)
 * @brief new和delete的形式要统一
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <cstdlib>
#include <string>

using AddressLines = std::string[10];
using Address_t = size_t*;

int main() {

    //single object  (ptr)[object]
    //array object [n](ptr)[object][object][object][...]
    //n的大小于机器字长有关

    auto al = new AddressLines;
    for (int i = 0;i < 10;i++) al[i] = 'a' + i;
    auto len = *(reinterpret_cast<Address_t>(al) - 1);
    auto len2 = *(reinterpret_cast<size_t*>((reinterpret_cast<void**>(al) - 1)));
    auto len3 = *(static_cast<size_t*>(static_cast<void*>(al) - 1));
    std::cout << "len = " << len << std::endl;
    std::cout << "len2 = " << len2 << std::endl;
    std::cout << "len3 = " << len3 << std::endl;
    for (int i = 0;i < 10;i++) std::cout << al[i] << std::endl;
    delete[] al;

    //string::operator=(const char& ch);
    {
        AddressLines a;
        a[0] = 'a' + 1;

        auto b = new std::string[10];
        b[0] = 'b' + 1;

        auto c = new std::string;
        *c = 'c' + 1;

        std::string s;
        s = 's';
    }
    return 0;
}
