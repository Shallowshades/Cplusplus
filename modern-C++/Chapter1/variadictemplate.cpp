/**
 *@file variadictemplate.cpp
 * @author your name (you@domain.com)
 * @brief 不定模板参数
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <bitset>
#include <functional>
#include <vector>
#include <complex>
#include <initializer_list>
#include <algorithm>

using namespace std;

constexpr int N = 1e3 + 10;

template<typename T>
inline void hash_combine(size_t& seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(size_t& seed, const T& val) {
    hash_combine(seed, val);
}

//recursive
template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template < typename... Types>
inline size_t hash_val(const Types&... args) {
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

class CustomerHash {
public:
    std::size_t operator() (const CustomerHash& c) const {
        return hash_val(c.fname, c.lname, c.no);
    }

private:
    string fname;
    string lname;
    int no;
};

//处理空包
void printX() {}

//参数包
template <typename T, typename... Types> //模板参数包
void printX(const T& firstArg, const Types&... args) { //函数参数类型包
    cout << firstArg << endl;
    printX(args...);//函数参数包
}

template<typename... Types>
void printX(const Types&... args) {
    cout << sizeof...(args) << endl;
    printX(args...);
}

// template<typename... Values> class tuple;
// template<> class tuple<> {};

// template<typename Head, typename... Tail>
// class tuple<Head, Tail...>: private tuple<Tail...> {
//     using inherited = tuple<Tail...>;
// public:
//     tuple() {}
//     tuple(Head v, Tail... vtail): m_head(v), inherited(vtail...) {}

//     typename Head::type head() { return m_head; }
//     inherted& tail() { return *this; }

// protected:
//     Head m_head;
// };

int main() {

    printX("string", 2, 's', 3.14, bitset<16>(377), 42);

    bitset<N> bs(0);
    cout << bs.flip() << endl;
    std::cout << bs.count() << std::endl;

    printX("string", 2, 's', 3.14, bitset<16>(377), 42);

    {
        int values[]{ 1,2,3 };
        vector<int> v{2, 3, 5, 7, 11, 13, 17};
        vector<string> cities{"Berlin", "London"};
        complex<double> c{4.0, 3.0};
    }

    cout << max({ string("sda"), string("Asd"), string("sad"), string("asd") }) << endl;

    return 0;
}
