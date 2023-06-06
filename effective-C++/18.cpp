/**
 * @file 18.cpp
 * @author your name (you@domain.com)
 * @brief 让接口更容易被使用
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

using namespace std;

namespace proto {
    class Date {
    public:
        Date(int month, int day, int year);
    };
} // namespace proto


namespace solution1 {
    struct Day {
        explicit Day(int d): val(d) {}
        int val;
    };

    struct Month {
        explicit Month(int m): val(m) {}
        int val;
    };

    struct Year {
        explicit Year(int y): val(y) {}
        int val;
    };

    class Date {
    public:
        Date(const Month& m, const Day& d, const Year& y): year(y), month(m), day(d) {};
    private:
        Year year;
        Month month;
        Day day;
    };

} // namespace solution1

int main() {

    //新类型预防错误调用
    {
        using namespace solution1;
        //Date d(30, 3, 1995); 
        //Date d(Day(30), Month(3), Year(1995));
        Date d(Month(3), Day(30), Year(1995));
    }

    //自定义类型尽可能与内建类型行为一致
    {

    }



    return 0;
}
