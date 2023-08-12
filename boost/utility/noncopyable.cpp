#include <iostream>
#include <algorithm>
#include <string>

#include <boost/noncopyable.hpp>

using namespace std;
using namespace boost;

class do_not_copy : boost::noncopyable { //公有私有皆可， 表明是HAS-A的关系
public:

private:

};

/// @brief 使用default和delete更清晰地实现
class noncopyable {
public:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    const noncopyable& operator=(const noncopyable&) = delete;
};

int main() {

    do_not_copy d1;
    //do_not_copy d2(d1);
    do_not_copy d3;
    //d3 = d1;



    return 0;
}