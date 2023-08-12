#include <string>
#include <locale>
#include <codecvt>
#include <iostream>

using namespace std;

// convert string to wstring
inline std::wstring to_wide_string(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}
// convert wstring to string 
inline std::string to_byte_string(const std::wstring& input)
{
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}

int main() {
    wstring wstr = L"你好-世界";
    string str; cin >> str;

    wstring inwstr;
    for (int i = 0; i < str.size(); ++i) {
        wchar_t ch = str[i];
        if (ch > 127)
            ch = (ch << 16) + str[i + 1];

        inwstr.push_back(ch);
    }

    std::cout << boolalpha << (wstr == inwstr) << std::endl;
}