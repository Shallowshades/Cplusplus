/**
 *@file ptimer.cpp
 * @author your name (you@domain.com)
 * @brief 高精度计时器（取代timer和progress_timer）
 * @version 0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

#ifndef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG       //精确到纳秒
#endif // !BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef POSIX_PTIME_HPP___
#ifndef DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR            //禁止date的默认构造函数
#endif // !DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#endif // !POSIX_PTIME_HPP___

#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES		//使weeks,months,years无效, days有效
#include <boost/date_time/gregorian/gregorian.hpp>  

using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;

template<typename Clock = microsec_clock>
class basic_ptimer {
public:
    basic_ptimer() { restart(); }
    void restart() { _start_time = Clock::local_time(); }
    void elapsed() const { std::cout << Clock::local_time() - _start_time; }
    ~basic_ptimer() { elapsed(); }
private:
    ptime _start_time;
};

// using ptimer = basic_ptimer<microsec_clock>;
// using sptimer = basic_ptimer<second_clock>;

typedef basic_ptimer<microsec_clock> ptimer; //精度取决于是否定义了头文件的宏
typedef basic_ptimer<second_clock> sptimer;

int main() {

    {
        ptimer p;
    }

    {
        std::cout << std::endl;
        sptimer sp;
    }

    return 0;
}

//! error: no matching function for call to 'boost::posix_time::ptime::ptime()
//  ptime是一个date + 一个time_duration, 头文件上的宏定义仅用了date的默认构造，自然ptime的默认构造也不可用