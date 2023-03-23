#include <iostream>
using namespace std;
int Result;
// 主模板
template <int N>  // 模板
class Fibonacci {
public:
    enum { Result = Fibonacci<N - 1>::Result + Fibonacci<N - 2>::Result };  // 枚举，带有隐含计算
};
// 完全特化模板
template <>  // 带常参数1的构造函数
class Fibonacci<1> {
public:
    enum { Result = 1 };  // 给枚举赋初值1
};
// 完全特化模板
template <>  // 带参数0的模板
class Fibonacci<0> {
public:
    enum { Result = 0 };  // 给枚举赋初值0
};
int main() {

    std::cout << "第20项的Fibonacci数是:" << Fibonacci<20>::Result << std::endl;  // 隐含计算
    return 1;
}