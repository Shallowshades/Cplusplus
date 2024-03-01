#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

const string key = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'\nZXCVBNM,./";

int main() {
    unordered_map<char, int> m;
    for (int i = 0; i < key.size(); ++i)
        m[key[i]] = i;

    string s;
    while (getline(cin, s)) {
        string ans;
        for (auto& ch : s) {
            if (ch != ' ')
                ans.push_back(key[m[ch] - 1]);
            else
                ans.push_back(' ');
        }

        std::cout << ans << std::endl;
    }

    return 0;
}
