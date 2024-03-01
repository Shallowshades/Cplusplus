#include <iostream>
#include <string>

using namespace std;

int main() {

    string s;
    int cnt = 0;
    while (getline(cin, s)) {
        string ans;
        for (auto& ch : s) {
            if (ch == '"') {
                if (++cnt % 2)
                    ans.push_back('`'), ans.push_back('`');
                else
                    ans.push_back('\''), ans.push_back('\'');
            }
            else ans.push_back(ch);
        }
        std::cout << ans << std::endl;
    }

    return 0;
}
