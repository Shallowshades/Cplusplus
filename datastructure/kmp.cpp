#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<int>& v) {
    for(auto elem : v) std::cout << elem << " ";
    std::cout << std::endl;
}

void build_next(std::vector<int>& next, const std::string pattern) {
    next[0]        = 0;
    int prefix_len = 0;
    int i          = 1;
    while(i < pattern.size()) {
        if(pattern[prefix_len] == pattern[i])
            next[i++] = ++prefix_len;
        else {
            if(prefix_len == 0)
                next[i++] = 0;
            else
                prefix_len = next[prefix_len - 1];
        }
    }
    print(next);
}

int kmp(std::string str, std::string pattern) {
    std::vector<int> next(pattern.size());
    build_next(next, pattern);
    int i = 0, j = 0;
    while(i < str.size()) {
        if(str[i] == pattern[j])
            ++i, ++j;
        else if(j > 0)
            j = next[j - 1];
        else  //第一个字符匹配失败，就开始下一个子串的匹配
            i += 1;
    }
    if(j == pattern.size()) return i - j;
    return -1;
}

int main() {
    std::string str, pattern;
    std::cin >> str >> pattern;
    std::cout << kmp(str, pattern) << std::endl;
    return 0;
}