/**
 *@file time.cpp
 * @author your name (you@domain.com)
 * @brief 时间
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

#ifndef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG 
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG       //精确到纳秒
#endif // !BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG 
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main() {

    //基础构造
    {
        time_duration td(1, 10, 30, 1000);
        cout << td << endl;

        hours h(1);             //子类
        minutes m(10);
        seconds s(30);
        millisec ms(1);
        microsec us(1);
        nanosec ns(1);
        cout << h << endl;
        cout << m << endl;
        cout << s << endl;
        cout << ms << endl;
        cout << us << endl;
        cout << ns << endl;

        time_duration td1 = h + m + s + ms + us + ns;
        cout << td1 << endl;
    }

    //工厂构造
    {
        time_duration td = duration_from_string("1:10:30:000000001");
        cout << td << endl;
    }

    //属性方法
    {
        time_duration td(1, 10, 30, 1000);
        cout << td.hours() << endl;
        cout << td.minutes() << endl;
        cout << td.seconds() << endl;
        cout << td.total_seconds() << endl;
        cout << td.total_milliseconds() << endl;
        cout << td.total_microseconds() << endl;
        cout << td.total_nanoseconds() << endl;
    }

    //允许负值
    {
        hours h(-10);
        cout << boolalpha << h.is_negative() << endl;

        time_duration h2 = h.invert_sign();
        cout << h2 << endl;
    }

    //特数值
    {
        time_duration td1(not_a_date_time);
        assert(td1.is_special() && td1.is_not_a_date_time());

        time_duration td2(neg_infin);
        assert(td2.is_negative() && td2.is_neg_infinity());
    }

    //四则运算
    {
        time_duration td1 = hours(1);
        time_duration td2 = hours(2) + minutes(30);
        assert(td1 < td2);
        assert((td1 + td2).hours() == 3);
        assert((td1 - td2).is_negative());
        assert(td1 * 5 == td2 * 2);
        assert((td1 / 2).minutes() == td2.minutes());
    }

    //格式化
    {
        time_duration td(1, 10, 30, 1000);
        cout << to_simple_string(td) << endl;
        cout << to_iso_string(td) << endl;
    }

    //转换到tm，但是无法反向转换
    {
        time_duration td(1, 20, 30, 100);
        tm t = to_tm(td);
        cout << t.tm_hour << endl;
        cout << t.tm_min << endl;
        cout << t.tm_sec << endl;
        cout << t.tm_mon << endl;
        cout << t.tm_yday << endl;
        cout << t.tm_wday << endl;
        cout << t.tm_year << endl;
    }

    //时间精确度
    {
        time_duration td(1, 10, 30, 1000);
        cout << td << endl;
        assert(td.total_milliseconds() == td.total_seconds() * 1000);
        cout << td.fractional_seconds() << endl;

        cout << time_duration::unit() << endl; //取决于是否定义了宏

        assert(time_duration::resolution() == date_time::nano); //枚举值
        assert(time_duration::num_fractional_digits() == 9);    //小数后的位数0
    }

    //与时间精度无关
    {
        time_duration::tick_type my_millisec = time_duration::ticks_per_second() / 1000;
        time_duration td(1, 10, 30, 10 * my_millisec);
        cout << td << endl;
    }

    ///时间点对象
    //构造
    {
        ptime p(date(2000, 1, 1), hours(1)); //日期 + 时间段 (默认凌晨)
        ptime p1 = time_from_string("2017-7-7 01:01:59");
        ptime p2 = from_iso_string("20170707T010029");
        cout << p1 << endl;
        cout << p2 << endl;
    }

    //时钟类
    {
        ptime p1 = second_clock::local_time();              //精确到秒  本地时间
        ptime p2 = second_clock::universal_time();          //精确到秒  UTC时间
        ptime p3 = microsec_clock::local_time();             //精确到微秒
        ptime p4 = microsec_clock::universal_time();        //
        cout << p1 << endl;
        cout << p2 << endl;
        cout << p3 << endl;
        cout << p4 << endl;
    }

    //特殊值
    {
        ptime p1(not_a_date_time);
        cout << p1 << endl;
        ptime p2(pos_infin);
        cout << p2 << endl;
    }

    //操作
    {
        ptime p(microsec_clock::local_time());
        date d = p.date();
        time_duration td = p.time_of_day();
        cout << d << endl;
        cout << td << endl;
    }

    //运算
    {
        ptime p1(date(2020, 3, 3), hours(12) + minutes(30));
        ptime p2 = p1 + hours(3);

        cout << boolalpha << (p1 < p2) << endl;
        cout << p2 - p1 << endl;

        p2 += months(1);
        cout << p2 - p1 << endl;
    }

    //转化为字符串
    {
        ptime p(microsec_clock::local_time());
        cout << to_simple_string(p) << endl;
        cout << to_iso_string(p) << endl;
        cout << to_iso_extended_string(p) << endl;
    }

    //ptime <==> tm
    {
        ptime p(date(2017, 5, 30), hours(14));
        tm t = to_tm(p);
        cout << t.tm_year << endl;
        cout << t.tm_year << endl;
        ptime p2 = from_time_t(std::time(0));
        cout << p.date() << endl;
        cout << day_clock::local_day() << endl;
        cout << to_time_t(p2) << endl;
    }

    //时间区间
    {
        ptime p(date(2017, 1, 1), hours(12));
        time_period tp1(p, hours(8));
        time_period tp2(p + hours(8), hours(1));
        cout << tp1 << endl;
        cout << tp2 << endl;
        cout << boolalpha << (!tp1.intersects(tp2)) << endl;

        tp1.shift(hours(1));
        cout << tp1 << endl;
        tp2.expand(hours(2));
        cout << tp2 << endl;
    }

    //时间迭代器
    {
        ptime p(date(2017, 5, 31), hours(10));
        for (time_iterator t_iter(p, minutes(10)); t_iter < p + hours(1); ++t_iter) {
            cout << *t_iter << endl;
        }
    }

    return 0;
}