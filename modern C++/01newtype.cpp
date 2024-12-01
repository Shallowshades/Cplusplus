/**
 *@file 01newtype.cpp
 * @author your name (you@domain.com)
 * @brief 新类型
 * @version 0.1
 * @date 2024-11-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <limits>
#include <cuchar>

using namespace std;

template<typename T>
void print(T t) {
    std::cout << typeid(t).name() << "\t" << sizeof(t) << "\t" << t << std::endl;
}

int main() {

    // long long 
    {
        long long int x = 456;
        long long y = 865;
        auto z = 4864ULL;
        print(x);
        print(y);
        print(z);
    }

    // 少使用宏,多使用模板
    {
        std::cout << "std::numeric_limits<long long>::max() = " << std::numeric_limits<long long>::max() << std::endl;
        std::cout << "std::numeric_limits<long long>::min() = " << std::numeric_limits<long long>::min() << std::endl;
        std::cout << "std::numeric_limits<unsigned long long>::max() = " << std::numeric_limits<unsigned long long>::max() << std::endl;
        std::cout << "std::numeric_limits<unsigned long long>::min() = " << std::numeric_limits<unsigned long long>::min() << std::endl;
    }

    // char16_t char32_t 对应utf-16和utf-32
    {
        // unicode 最大个数为0x10ffff

        // utf-32 4B完全容纳 固定长度

        // utf-16 2B加映射  固定长度
        //0x0000 - 0xD7FF   直接映射
        //0xE000 - 0xFFFF   直接映射
        //0xD800 - 0xDFFF   映射0x010000 - 0x10FFFF
        //映射方法: 字符编码 - 0x10000 = 20bit
        //高位10bit映射0xD800 - 0xDBFF
        //地位10bit映射0xDC00 - 0xDFFF
        //例如:0x10437 - 0x10000 = 0x00437
        //高位10bit为0x1, 低位10bit为0x37
        //分别加上映射起始值
        //0x1 + 0xD800 = 0xD801
        //0x37 + 0xDC00 = 0xDC37

        // utf-8 不定长编码
        /*
            代码范围十六进制                                    UTF-8二进制                                         注释
            000000～00007F 128个代码                            0zzzzzzz                                        ASCII字符范围，字节由零开始
            000080～0007FF 1920个代码                           110yyyyy 10zzzzzz                               第1字节由110开始，接着的字节由10开始
            000800～00D7FF 00E000～00FFFF 61440个代码           1110xxxx 10yyyyyy 10zzzzzz                      第1字节由1110开始，接着的字节由10开始
            010000～10FFFF 1048576个代码                        11110www 10xxxxxx 10yyyyyy 10zzzzzz             第1字节由11110开始，接着的字节从10开始
        */

        char utf8c = u8'a';             // C++17标准
        //char utf8c = u8'好';          // 存储空间不足
        char16_t utf16c = u'好';
        char32_t utf32c = U'好';
        char utf8[] = u8"你好世界";
        char16_t utf16[] = u"你好世界";
        char32_t utf32[] = U"你好世界";

        std::cout << hex << utf8c << "\t" << dec << sizeof(utf8c) << std::endl;
        std::cout << hex << utf16c << "\t" << dec << sizeof(utf16c) << std::endl;
        std::cout << hex << utf32c << "\t" << dec << sizeof(utf32c) << std::endl;
        std::cout << hex << utf8 << "\t" << dec << sizeof(utf8) << std::endl;
        std::cout << hex << utf16 << "\t" << dec << sizeof(utf16) << std::endl;
        std::cout << hex << utf32 << "\t" << dec << sizeof(utf32) << std::endl;


        // c11
        /*
            c++ include <cuchar>
            size_t mbrtoc16( char16_t* pc16, const char* s, size_t n, mbstate_t* ps );
            size_t c16rtomb( char* s, char16_t c16, mbstate_t* ps );
            size_t mbrtoc32( char32_t* pc32, const char* s, size_t n, mbstate_t* ps );
            size_t c32rtomb( char* s, char32_t c32, mbstate_t* ps );
        */
        char16_t utf16buffer[1024];
        //mbrtowc(utf16buffer, utf8, sizeof(utf8), nullptr);

        // TODO: 流处理
        u32string str = U"你好,世界";
        std::cout << str.c_str() << "\t" << str.size() << std::endl;
    }

    return 0;
}
