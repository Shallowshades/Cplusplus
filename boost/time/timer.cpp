/**
 *@file timer.cpp
 * @author your name (you@domain.com)
 * @brief 定时器
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <algorithm>

#include <boost/version.hpp>
#include <boost/timer.hpp>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main() {

    //
    {
        cout << BOOST_VERSION << endl;
        cout << BOOST_LIB_VERSION << endl;

        cout << BOOST_PLATFORM << endl;
        cout << BOOST_COMPILER << endl;
        cout << BOOST_STDLIB << endl;
    }

    ///定时器 timer (已摒弃， 但具有学习意义)
    //基本用法
    {
        timer t;
        cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;
        cout << "min timespan:" << t.elapsed_min() << "s" << endl;
        cout << "now time elapsed:" << t.elapsed() << "s" << endl;
    }

    //继承自timer
    {
        progress_timer t;
    }

    return 0;
}