#pragma once



#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES		//使weeks,months,years无效
#ifndef DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR            //禁止date的默认构造函数
#endif // !DATE_TIME_NO_DEFAULT_CONSTRUCTOR	
#include <boost/date_time/gregorian/gregorian.hpp>  

#ifndef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG       //精确到纳秒
#endif // !BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/posix_time/posix_time.hpp>