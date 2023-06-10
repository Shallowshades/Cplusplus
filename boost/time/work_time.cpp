/**
 *@file work_time.cpp
 * @author your name (you@domain.com)
 * @brief 上班时间段
 * @version 0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>
#include <map>

#ifndef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG       //精确到纳秒
#endif // !BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef POSIX_PTIME_HPP___
#ifndef DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR            //禁止date的默认构造函数
#endif // !DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#endif // !POSIX_PTIME_HPP___

#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES		//使weeks,months,years无效，, days有效
#include <boost/date_time/gregorian/gregorian.hpp>  

using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;

class work_time {
public:
    typedef std::map<time_period, std::string> map_t;
    work_time() { init(); }
    void init();
    void greeting(const ptime& t);
private:
    map_t map_ts;
};

void work_time::init() {
    ptime p(day_clock::local_day());
    map_ts[time_period(p, hours(9))] = std::string("It's too early, just relax.");
    p += hours(9);
    map_ts[time_period(p, hours(3) + minutes(30))] = std::string("It's AM, please work hard.");
    p += hours(3) + minutes(30);
    map_ts[time_period(p, hours(1))] = std::string("It's lunch time, are you hungry?");
    p += hours(1);
    map_ts[time_period(p, hours(4) + minutes(30))] = std::string("It's PM, ready to go home.");
    p += hours(4) + minutes(30);
    map_ts[time_period(p, hours(6))] = std::string("Are you still working? you do need a rest.");
}

void work_time::greeting(const ptime& t) {
    for (auto&& tp : map_ts) {
        if (tp.first.contains(t)) {
            std::cout << tp.second << std::endl;
            break;
        }
    }
}

int main() {

    work_time wt;
    wt.greeting(second_clock::local_time());

    return 0;
}