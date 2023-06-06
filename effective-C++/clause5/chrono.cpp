/**
 *@file chrono.cpp
 * @author your name (you@domain.com)
 * @brief chrono库
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>
using namespace std::chrono;


int main() {

    //duration 一段时间
    {
        auto fiveSeconds = std::chrono::seconds(5);
        std::cout << "start" << std::endl;
        std::this_thread::sleep_for(fiveSeconds);
        std::cout << "end" << std::endl;
    }
    {
        auto oneSecond = milliseconds(100);
        std::cout << "start" << std::endl;
        std::this_thread::sleep_for(oneSecond);
        std::cout << "end" << std::endl;
    }

    //custom duration
    {
        //自定义时间间隔，每个时间单位为1s
        auto customTwoSeconds = std::chrono::duration<double, std::ratio<1 / 1>>(2);
        std::cout << "start" << std::endl;
        std::this_thread::sleep_for(customTwoSeconds);
        std::cout << "end" << std::endl;
    }

    //transform 允许大向小转换，转换为更精确的
    //hour -> minute/second OK
    //second -> hour  NOT
    {
        auto day = std::chrono::hours(24);
        auto seconds = std::chrono::seconds(day);
        std::cout << day.count() << std::endl;
        std::cout << seconds.count() << std::endl;
        //如果非要转，使用duration_cast进行转换
        auto newDay = std::chrono::duration_cast<std::chrono::hours>(seconds);
        std::cout << newDay.count() << std::endl;
    }

    //epoch 从某个时间点起始的时间
    {
        auto timePoint = system_clock::now();
        std::cout << duration_cast<hours>(timePoint.time_since_epoch()).count() / 24 << std::endl;
    }

    //time point 特定的时间点
    //时间点 - 时间点 = 一段时间
    {
        auto old = steady_clock::now();
        std::vector<int> v(1000000);
        std::cout << std::count_if(v.begin(), v.end(), [](int i) {return i == 0;}) << std::endl;

        auto dur = steady_clock::now() - old;
        std::cout << dur.count() << std::endl;
        std::cout << duration_cast<microseconds>(dur).count() << std::endl;
    }

    {
        auto old = steady_clock::now();
        for (int i = 0;i < 1000000;i++) {
            std::cout << "test" << std::endl;
        }

        auto dur = steady_clock::now() - old;
        std::cout << dur.count() << std::endl;
        std::cout << duration_cast<microseconds>(dur).count() << std::endl;
        std::cout << duration_cast<milliseconds>(dur).count() << std::endl;
        std::cout << duration_cast<seconds>(dur).count() << std::endl;
        /*
            6628100309
            6628100
            6628
            6
        */
    }

    {
        auto old = steady_clock::now();
        for (int i = 0;i < 1000000;i++) {
            std::cout << "test\n";
        }

        auto dur = steady_clock::now() - old;
        std::cout << dur.count() << std::endl;
        std::cout << duration_cast<microseconds>(dur).count() << std::endl;
        std::cout << duration_cast<milliseconds>(dur).count() << std::endl;
        std::cout << duration_cast<seconds>(dur).count() << std::endl;
        /*
            5160746696
            5160746
            5160
            5
        */
    }

    return 0;
}
