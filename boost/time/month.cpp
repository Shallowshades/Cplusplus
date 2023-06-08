/**
 *@file month.cpp
 * @author your name (you@domain.com)
 * @brief 打印月历
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost;
using namespace boost::gregorian;

void paint(const date& d);
void paint_weekday(const date& d);
void paint_monthday(const date_period& dp);

int main() {

    //打印当年的月历
    for (date d(day_clock::local_day()); d.year() < 2024; d += months(1)) {
        cout << "========== " << d.month() << " ==========" << endl;
        paint(d);
    }
    system("pause");
    return 0;
}

void paint(const date& d) {
    date_period dp(date_period((d - months(1)).end_of_month() + days(1), d.end_of_month() + days(1)));
    paint_weekday(dp.begin());
    paint_monthday(dp);
}

void paint_weekday(const date& d) {
    for (greg_weekday weekday = 0; ; weekday = weekday + 1) {
        cout << weekday << "\t";
        if (weekday == greg_weekday::max()) break;
    }
    cout << endl;
    for (greg_weekday weekday = 0; weekday < d.day_of_week(); weekday = weekday + 1) {
        cout << "\t";
    }
}

void paint_monthday(const date_period& dp) {
    for (day_iterator iter = dp.begin(); iter != dp.end(); ++iter) {
        cout << iter->day() << "\t";
        if (iter->day_of_week() == greg_weekday::max() && iter->day() != dp.last().day())
            cout << endl;
    }
    cout << "\n\n";
}
