/**
 * @file sfinae.cpp
 * @author your name (you@domain.com)
 * @brief 有两个不同类型的计数器（counter），一种是普通的整数类型，另外一种是一个复杂对象，它从接口 ICounter 继承，这个接口有一个成员叫做increase实现计数功能。
 * @version 0.1
 * @date 2023-01-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <type_traits>
#include <utility>
#include <cstdint>

//直接实现
namespace simple{
    class ICounter{
    public:    
        virtual void increase() = 0;
        virtual ~ICounter(){}
    };

    class Counter : public ICounter{
    public:
        Counter(int val = 0) : count(val) {};
        void increase() override{
            ++count;
        }
        int count;
    };

    std::ostream& operator << (std::ostream& os, const Counter& counter){
        return os << counter.count;
    }

    template<typename T>
    void inc_counter(T& counterObj){
        counterObj.increase();
    }

    template<>
    void inc_counter<uint32_t>(uint32_t& intTypeCounter){
        ++intTypeCounter;
    }

    void doSomething(){
        Counter cntObj;
        uint32_t cntUI32 = 0;

        inc_counter(cntObj);
        inc_counter(cntUI32);

        std::cout << cntObj << std::endl;
        std::cout << cntUI32 << std::endl;
    }
};

//使用enable_if实现
namespace enable{
    class ICounter{
    public:    
        virtual void increase() = 0;
        virtual ~ICounter(){}
    };

    class Counter : public ICounter{
    public:
        Counter(int val = 0) : count(val) {};
        void increase() override{
            ++count;
        }
        int count = 0;
    };

    std::ostream& operator << (std::ostream& os, const Counter& counter){
        return os << counter.count;
    }

    //is_integral<T>::value返回一个布尔类型的编译器常数
    //enable_if<C> 的作用就是，如果这个 C 值为 True，那么 enable_if<C>::type 就会被推断成一个 void 或者是别的什么类型，
    //让整个函数匹配后的类型变成 void inc_counter<int>(int & counterInt, void* dummy = nullptr); 
    //如果这个值为 False ，那么 enable_if<false> 这个特化形式中，压根就没有这个 ::type，于是替换就失败了
    template<typename T>
    void inc_counter(T& counterObj, typename std::enable_if<std::is_base_of<ICounter,T>::value>::type* = nullptr){
        counterObj.increase();
    }

    template<typename T>
    void inc_counter(T& intTypeCounter, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr){
        ++intTypeCounter;
    }

    void doSomething(){
        Counter cntObj;
        uint32_t cntUI32 = 0;

        inc_counter(cntObj);
        inc_counter(cntUI32);

        std::cout << cntObj << std::endl;
        std::cout << cntUI32 << std::endl;
    }
};

//因为 increase 毕竟是个虚函数。假如 Counter 需要调用的地方实在是太多了，这个时候非常期望 increase 不再是个虚函数以提高性能,整继承层级
namespace old{
    struct ICounter {};
    struct Counter: public ICounter {
        void increase() {
            ++count;
        }   
        int count = 0;
    };

    std::ostream& operator << (std::ostream& os, const Counter& counter){
        return os << counter.count;
    }

    template <typename T>
    void inc_counter(T& counterObj,typename std::enable_if<std::is_base_of<ICounter,T>::value>::type* = nullptr){
        counterObj.increase();
    };

    template <typename T>
    void inc_counter(T& counterInt, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr) {
         ++counterInt; 
    }

    void doSomething() {
        Counter cntObj;
        uint32_t cntUI32 = 0;

        // blah blah blah
        inc_counter(cntObj); 
        inc_counter(cntUI32); 

        std::cout << cntObj << std::endl;
        std::cout << cntUI32 << std::endl;
    }
}

//C++14之后
namespace now{
    struct Counter {
        void increase() {
            ++count;
        }
        int count = 0;
    };

    template <typename T>
    void inc_counter(T& intTypeCounter, std::decay_t<decltype(++intTypeCounter)>* = nullptr) {
        ++intTypeCounter;
    }

    template <typename T>
    void inc_counter(T& counterObj, std::decay_t<decltype(counterObj.increase())>* = nullptr) {
        counterObj.increase();
    }

    void doSomething() {
        Counter cntObj;
        uint32_t cntUI32 = 0;

        // blah blah blah
        inc_counter(cntObj);
        inc_counter(cntUI32);
    }
};

//C++20
/*
    对模板参数约束
    对T的要求得有++
    template <typename T> concept Incrementable = requires (T t) { ++t; }
    template <Incrementable T>
    void inc_counter(T& intTypeCounter) { 
        ++intTypeCounter;
    }

    ==

    template <typename T> requires (requires (T t) { ++t; })
    void inc_counter(T& cnt);
*/


int main(){

    simple::doSomething();
    enable::doSomething();
    old::doSomething();

    return 0;
}