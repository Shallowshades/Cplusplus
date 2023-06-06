/**
 * @file regex.cpp
 * @author your name (you@domain.com)
 * @brief 正则表达式
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

// 对 URL 资源链接进行判断时， 使用正则表达式也是工业界最为成熟的普遍做法
// C++11 提供的正则表达式库操作 std::string 对象，
// 模式 std::regex (本质是 std::basic_regex)进行初始化，
// 通过 std::regex_match 进行匹配， 从而产生 std::smatch （本质是 std::match_results 对象）。

int main() {

    // 1.
    {
        // 在 C++ 中 \ 会被作为字符串内的转义符，
        // 为使 \. 作为正则表达式传递进去生效，需要对 \ 进行二次转义，从而有 \\.
        std::string fnames[] = { "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt" };
        std::regex  txt_regex("[a-z]+\\.txt");
        //\.表示匹配.
        //但是\作为转义符号，要写\\

        for(const auto& fname : fnames) { std::cout << fname << ":" << std::regex_match(fname, txt_regex) << std::endl; }

        //[a-z]+\.txt: 在这个正则表达式中,
        //[a-z] 表示匹配一个小写字母, + 可以使前面的表达式匹配多次， 因此 [a-z]+ 能够匹配一个小写字母组成的字符串。
        //在正则表达式中一个 . 表示匹配任意字符，而 \.则表示匹配字符 .，
        //最后的 txt 表示严格匹配 txt 则三个字母。
        //因此这个正则表达式的所要匹配的内容就是由纯小写字母组成的文本文件。
    }

    // 2.
    //常用的形式就是依次传入 std::string/std::smatch/std::regex 三个参数， 
    //其中 std::smatch 的本质其实是 std::match_results。 
    //故而在标准库的实现中， std::smatch 被定义为了std::match_results<std::string::const_iterator>， 
    //也就是一个子串迭代器类型的 match_results。 使用 std::smatch 可以方便的对匹配的结果进行获取
    {
        std::string fnames[] = { "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt" };
        std::regex  base_regex("([a-z]+)\\.txt");
        std::smatch base_match;
        for(const auto& fname : fnames) {
            if(std::regex_match(fname, base_match, base_regex)) {
                // std::smatch 的第一个元素匹配整个字符串
                // std::smatch 的第二个元素匹配了第一个括号表达式
                if(base_match.size() == 2) {
                    std::string base = base_match[1].str();
                    std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
                    std::cout << fname << " sub-match[1]: " << base << std::endl;
                }
            }
        }
    }
    return 0;
}