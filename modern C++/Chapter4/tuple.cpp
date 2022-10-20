/**
 * @file tuple.cpp
 * @author your name (you@domain.com)
 * @brief 元组
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <tuple>
#include <variant>

template <typename T>
auto tuple_len(T& tpl) {
    return std::tuple_size<T>::value;
}

//以后再看
// C++17
template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if constexpr(n >= sizeof...(T)) throw std::out_of_range("越界.");
    if(i == n) return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tpl) };
    return _tuple_index<(n < sizeof...(T) - 1 ? n + 1 : 0)>(tpl, i);
}
template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}
template <typename T0, typename... Ts>
std::ostream& operator<<(std::ostream& s, std::variant<T0, Ts...> const& v) {
    std::visit([&](auto&& x) { s << x; }, v);
    return s;
}

int main() {

    /*
    三个核心的函数：
    std::make_tuple:    构造元组?
    std::get:           获得元组某个位置的值?
    std::tie:           元组拆包
    */
    // C++11
    {
        auto get_student = [](int id) {
            // 返回类型被推断为 std::tuple<double, char, std::string>
            if(id == 0) return std::make_tuple(3.8, 'A', "zhangsan");
            if(id == 1) return std::make_tuple(2.9, 'C', "lisi");
            if(id == 2) return std::make_tuple(1.7, 'D', "wangwu");
            return std::make_tuple(0.0, 'D', "null");
            // 如果只写 0 会出现推断错, 编译失败
        };
        auto student = get_student(0);

        //依赖一个编译期的常量
        std::cout << "ID: 0, "
                  << "GPA: " << std::get<0>(student) << ", "
                  << "grade: " << std::get<1>(student) << ", "
                  << "name: " << std::get<2>(student) << '\n';

        double      gpa;
        char        grade;
        std::string name;

        // 元组进行拆包
        std::tie(gpa, grade, name) = get_student(1);
        std::cout << "ID: 1, "
                  << "GPA: " << gpa << ", "
                  << "grade: " << grade << ", "
                  << "name: " << name << '\n';

        //合并与遍历
        std::tuple<int, double> t(2, 4.5);
        auto                    new_tuple = std::tuple_cat(get_student(1), std::move(t));

        // 迭代
        for(int i = 0; i != tuple_len(new_tuple); ++i)
            // 运行期索引
            std::cout << tuple_index(new_tuple, i) << std::endl;
    }

    // C++14 使用类型来获取元组中的对象
    {
        std::cout << "--------------\n";
        std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
        std::cout << std::get<std::string>(t) << std::endl;
        // std::cout << std::get<double>(t) << std::endl;  // 非法, 引发编译期错误
        std::cout << std::get<3>(t) << std::endl;
    }

    // C++17
    {
        int                                  index = 1;
        std::tuple<std::string, double, int> t("123", 6.7, 8);
        // std::get<index>(t);
        // std::get<> 依赖一个编译期的常量，所以这种方式是不合法的

        //使用 std::variant<>
        std::cout << tuple_index(t, index) << std::endl;
    }

    return 0;
}