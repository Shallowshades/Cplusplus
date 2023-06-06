#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

using u8 = unsigned char;
using u32 = unsigned int;
int main() {

    //char32_t str[1024];
    u8 str[1024];
    cin >> str;
    //cout << strlen(str) << endl;

    for (int i = 0; str[i] != 0; i += 3) {
        u32 ch = (((static_cast<int>(str[i]) << 8) + str[i + 1]) << 8) + str[i + 2];
        cout << ch << " ";

        printf("%X\n", ch);
    }

    // for (int i = 0; str[i] != 0; i++) {
    //     cout << u32(str[i]) << " ";
    //     // int ch = str[i] << 16;
    //     // ch += (str[i + 1] << 8);
    //     // ch += str[i + 2];

    //     // cout << ch << "\t";

    //     // char s[100];
    //     // itoa(ch, s, 16);
    //     // cout << s << endl;
    // }
    //cout << str;

    return 0;
}