/**
 *@file date.cpp
 * @author your name (you@domain.com)
 * @brief 时间：时间点，时间段，时长
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>

#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES		//使weeks,months,years无效
#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR			//禁止date的默认构造函数
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost;
using namespace boost::gregorian;

void error_time();

int main() {

    ///日期

    //从字符串中产生（工厂函数）
    {
        date d1 = from_string("1999-03-27");
        date d2 = from_string("1999/03/27");
        date d3 = from_undelimited_string("19990327");

        cout << d1 << endl;
        cout << d2 << endl;
        cout << d3 << endl;
    }

    //当前日期
    {
        date d1 = day_clock::local_day();			//本地日期
        date d2 = day_clock::universal_day();		//UTC日期
        auto d3 = day_clock::universal_day_ymd();	//UTC

        cout << d1 << endl;
        cout << d2 << endl;
        cout << d3.year << " " << d3.month << " " << d3.day << endl;
    }

    //特殊值
    {
        date d1(neg_infin);
        date d2(pos_infin);
        date d3(not_a_date_time);
        date d4(max_date_time);
        date d5(min_date_time);

        cout << d1 << endl;
        cout << d2 << endl;
        cout << d3 << endl;
        cout << d4 << endl;
        cout << d5 << endl;
    }

    //非法日期异常
    {
        try {
            error_time();
        }
        catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }

    //接口方法
    {
        date d1 = day_clock::local_day();
        cout << d1.day_of_week() << endl;
        cout << d1.end_of_month() << endl;
        cout << d1.week_number() << endl;
        cout << d1.as_special() << endl;

        date d2(pos_infin);
        cout << d2.as_special() << endl;
    }

    //输出
    {
        date d(2000, 1, 1);
        cout << to_simple_string(d) << endl;			//yyyy-mmm-dd 默认格式 mmm为月份的英文
        cout << to_iso_string(d) << endl;				//yyyymmdd
        cout << to_iso_extended_string(d) << endl;		//yyyy-mm-dd
        cout << d << endl;								//yyyy-mmm-dd

        //cin >> d;										//2000-Jan-01 
        //cout << d;
    }

    //和C struct tm 的相互转换
    {
        date d(2017, 5, 20);
        tm t = to_tm(d);
        assert(t.tm_hour == 0 && t.tm_min == 0 && t.tm_sec == 0);	//将hms置零
        assert(t.tm_year == 117 && t.tm_mday == 20);				//起始时间1900

        date d2 = date_from_tm(t);
        assert(d == d2);
    }

    //时间长度
    {
        date_duration dd1(10);	//类名
        days dd2(-100);			//别名
        days dd3(255);

        assert(dd1 > dd2 && dd1 < dd3);
        assert(dd1 + dd2 == days(-90));
        assert((dd1 + dd3).days() == 265);
        assert(dd3 / 5 == days(51));

        weeks_duration w1(5);
        weeks w2(3);
        assert(w1.days() == 35);

        months m1(5);
        years y(2);

        months m2 = y + m1;
        assert(m2.number_of_months() == 29);
        assert((y * 2).number_of_years() == 4);
    }

    //运算
    {
        date d1(1999, 3, 27), d2(day_clock::local_day());
        cout << d2 - d1 << endl; //8837
        assert(d1 + (d2 - d1) == d2);

        d1 += days(10);								//1999 04 06
        assert(d1.day() == 6);
        d1 += months(2);							//1999 06 06
        assert(d1.month() == 6 && d1.day() == 6);
        d1 -= weeks(1);								//1999 05 30
        assert(d1.day() == 30);

        d2 -= years(10);							//2013 06 06
        assert(d2.year() == d1.year() + 14);

        //特殊日期
        {
            date d3(2017, 1, 1);
            date d4 = d3 + days(pos_infin);
            assert(d4.is_pos_infinity());

            d4 = d3 + days(not_a_date_time);
            assert(d4.is_not_a_date());
            d4 = date(neg_infin);
            days dd = d3 - d4;
            assert(dd.is_special() && !dd.is_negative());
        }
        //月末操作
        {
            date d(2000, 3, 30);	//月末，或者操作后>=月末，追加月末操作
            cout << d << endl;
            d -= months(1);			//2000 02 29
            cout << d << endl;
            d -= months(1);			//2000 01 31
            cout << d << endl;
            d += months(2);			//2000 03 31		
            cout << d << endl;

        }
    }

    ///日期区间 时间段
    //构造
    {
        date_period dp1(date(2017, 1, 1), days(20));
        date_period dp2(date(2017, 1, 1), date(2016, 1, 1));    //无效
        date_period dp3(date(2017, 3, 1), days(-20));           //无效

        date_period dp(date(2017, 1, 1), days(20));
        assert(dp.begin().day() == 1);
        cout << dp.last().day() << endl;
        cout << dp.end().day() << endl;
        cout << dp.length().days() << endl;

        cout << boolalpha << date_period(date(2017, 1, 1), date(2016, 1, 1)).is_null() << endl;
    }


    //TODO:
    //日期区间运算
    {

    }

    //其他功能
    {
        typedef gregorian_calendar calendar;
        cout << "Y2017 is " << (calendar::is_leap_year(2017) ? "" : "not") << " a leap year.\n";
        cout << calendar::end_of_month_day(2017, 2) << endl;
    }

    return 0;
}

void error_time() {
    date d1(1399, 12, 1);
    date d2(10000, 1, 1);
    date d3(2017, 2, 29);
}
