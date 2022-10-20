#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int main() {

    char* s[10] = {const_cast<char*>("asdaddsfffffffffffffffffa"),const_cast<char*>("addada") };
    //指针数组 数组的每个元素都是一个指针
    char p[5][20] = { '\0' };
    char(*str)[20] = p; 
    //数组指针 指向固定长度数组的指针
    strcpy(str[0], "sss");
    strcpy(str[1], "222");
    strcpy(str[2], "888");
    for (int i = 0; i < 5; ++i) cout << p[i] << "\n";

    cout <<"字符串常量adress: "<<(void*)("asdaddsfffffffffffffffffa")<<"\n";
    cout <<"局部字符串常量adress: "<< (void*)(&s[0]) << "\n";
    cout <<"局部字符串常量adress: "<< (void*)s << "\n";

    cout <<"局部字符串变量adress: "<< (void*)p <<"\n";
    cout <<"局部字符串变量adress: "<< (void*)str <<"\n";

    return 0;
}