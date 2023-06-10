/**
 *@file advanced.cpp
 * @author your name (you@domain.com)
 * @brief date_time的宏， 自定义字面值，格式化时间, 夏令时
 * @version 0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>  
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;

inline days operator "" _D(unsigned long long n) { return days(n); }
inline weeks operator "" _W(unsigned long long n) { return weeks(n); }
inline date operator "" _YMD(const char* s, std::size_t) { return from_string(s); }

int main() {

    //自定义字面值
    {
        auto d = 100_D;
        auto w = 1_W;
        auto today = "2023/6/10"_YMD;

        std::cout << d.days() << std::endl;
        std::cout << w.days() << std::endl;
        std::cout << today << std::endl;
    }

    //格式化时间
    {
        date_facet* dfacet = new date_facet("%Y年%m月%d日");
        std::cout.imbue(std::locale(std::cout.getloc(), dfacet));
        std::cout << day_clock::local_day() << std::endl;

        time_facet* tfacet = new time_facet("%Y年%m月%d日%H时%M分%S%F秒");
        std::cout.imbue(std::locale(std::cout.getloc(), tfacet));
        std::cout << microsec_clock::local_time() << std::endl;

    }

    //夏令时
    {
        //时区数据库对象， csv文件位于 libs/date_time/data
        tz_database tz_db;
        tz_db.load_from_file("C:/Program Files/boost/boost_1_78_0/libs/date_time/data/date_time_zonespec.csv");

        time_zone_ptr shz = tz_db.time_zone_from_region("Asia/Shanghai");           //上海
        time_zone_ptr sfz = tz_db.time_zone_from_region("America/Los_Angeles");     //洛杉矶

        std::cout << shz->has_dst() << std::endl;                                   //有无夏令时
        std::cout << shz->std_zone_name() << std::endl;                             //时区名称

        local_date_time dt_bj(
            date(day_clock::local_day()),                                           //日期点
            hours(microsec_clock::local_time().time_of_day().hours()),              //时间长度
            shz,                                                                    //时区指针
            false);                                                                 //有无夏令时
        local_date_time dt_sf = dt_bj.local_time_in(sfz);
        std::cout << dt_bj << std::endl;
        std::cout << dt_sf << std::endl;

        time_duration flight_time = hours(12);
        dt_bj += flight_time;

        dt_sf = dt_bj.local_time_in(sfz);

        std::cout << dt_bj << std::endl;
        std::cout << dt_sf << std::endl;
    }

    return 0;
}