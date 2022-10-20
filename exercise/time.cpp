#include <iostream>
#include <ctime>
#include <cstring>
#include <windows.h>

constexpr auto BST = (+1);
constexpr auto CCT = (+8);

using namespace std;

int main(){

    ///四种变量
    tm *Time_Struct; //保存时间和日期的结构
    time_t Time_Now; //适合存储日历时间类型 _int64
    clock_t Time_Colck_Start, Time_Colck_End; //适合存储处理器时间的类型
    size_t Time_Size; //无符号整数类型

    ///函数返回自程序启动起，处理器时钟所使用的时间。如果失败，则返回-1值
    Time_Colck_Start = clock();//处理器启动时间
    cout <<Time_Colck_Start << endl;
    cout <<1.0 * Time_Colck_Start / CLOCKS_PER_SEC << "\n"; //除以每秒的时钟数

    ///获取系统日期和时间，并把它编码成 time_t 格式
    time(&Time_Now); //以秒为单位
    cout << Time_Now << "\n";

    ///time_t的值被分解为 tm 结构，并用本地时区表示。
    Time_Struct = localtime(&Time_Now); 
    cout << "year =\t\t" << Time_Struct->tm_year << "\n";
    cout << "month =\t\t" << Time_Struct->tm_mon << "\n";
    cout << "day =\t\t" << Time_Struct->tm_mday << "\n";
    cout << "hour =\t\t" << Time_Struct->tm_hour << "\n";
    cout << "minute =\t" << Time_Struct->tm_min << "\n";
    cout << "second =\t" << Time_Struct->tm_sec << "\n";
    cout << "weekday =\t" << Time_Struct->tm_wday << "\n";
    cout << "yearday =\t" << Time_Struct->tm_yday << "\n";
    cout << "summerday =\t" << Time_Struct->tm_isdst << "\n";

    char Time_Str[60]; //时间接受字符串

    ///asctime将tm结构体转换成可读格式
    strcpy(Time_Str, asctime(Time_Struct)); 
    cout << Time_Str;

    Time_Colck_End = clock(); //处理器结束时间
    cout <<Time_Colck_End << "\n";
    cout <<1.0 * Time_Colck_End / CLOCKS_PER_SEC << "\n"; //除以每秒的时钟数
    cout <<(1.0 * Time_Colck_End - Time_Colck_Start) / CLOCKS_PER_SEC << "s\n"; //时间差

    ///返回以双精度浮点型 double 值表示的两个时间之间相差的秒数 (time1 - time2)
    time_t Time_Now2;
    Sleep(1000);
    time(&Time_Now2);
    double Time_Diff = difftime(Time_Now2,Time_Now);
    cout << Time_Diff << "\n";

    ///返回指向 tm 结构的指针,协调世界时（UTC）,格林尼治标准时间（GMT）表示
    Time_Struct = gmtime(&Time_Now2);

    ///函数返回一个 C 字符串，该字符串包含了可读格式的日期和时间信息
    strcpy(Time_Str, "Hello, world");
    strcpy(Time_Str,ctime(&Time_Now2));
    cout << Time_Str;

    cout.fill(0);
    cout.setf(ios_base::adjustfield,ios::right);
    cout << "当前世界时钟" << endl;

    cout << "伦敦时间 " ;
    cout.width(2);
    cout << Time_Struct->tm_hour + BST % 24 <<":";
    cout.width(2);
    cout << Time_Struct->tm_min % 60 << ":";
    cout.width(2);
    cout << Time_Struct->tm_sec % 60 << endl;

    cout << "中国时间 " ;
    cout.width(2);
    cout << Time_Struct->tm_hour + CCT % 24 <<":";
    cout.width(2);
    cout << Time_Struct->tm_min % 60 << ":";
    cout.width(2);
    cout << Time_Struct->tm_sec % 60 << endl;

    ///返回自1970年1月1日以来持续时间的秒数。如果发生错误，则返回-1值
    Time_Struct->tm_hour += CCT;
    Time_Now = mktime(Time_Struct);
    cout << Time_Now << "\n";

    ///格式化结构体tm表示的时间，并把它存储在str中
    strftime(Time_Str,30,"%Y-%m-%d %H:%M:%S", Time_Struct);
    cout << Time_Str << "\n";

    return 0;
}