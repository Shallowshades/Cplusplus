/**
 *@file atomic.cpp
 * @author your name (you@domain.com)
 * @brief 原子
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

constexpr auto THREAD_NUM = 10;

atomic<int> a;
int b;
void incNumber(int num);

int main() {

    /*
          对于原子操作来讲，是不可能看到原子操作只完成了部分这种情况的， 它要么是做了，要么就是没做，只有这两种可能。
          虽然mutex也可以提供共享资源的访问的保护，但是加锁一般针对一个代码段，atomic针对的一般都是一个变量；
          而且原子操作更加接近底层，因而效率一般比使用互斥量更高。可以说，原子操作轻松地化解了互斥访问共享数据的难题。
    */

    /// 构造
    {
        // 默认构造并且使用函数初始化
        atomic<int> a;
        atomic_init(&a, 100);

        // 初始化构造
        atomic<int> b(200);

        // 禁止拷贝 当涉及两个对象时， 无法保证其原子性
    }

    /// 成员函数
    // store()	存储一个值到原子对象，等价于使用等号。
    // load()	加载原子对象中存入的值，等价与直接使用原子变量
    // exchange() 返回原来里面存储的值，然后this会再存储新的值，相当于将上面两个load()和store()合成起来
    // compare_exchange_weak(T & expected, T desired, ....）	
    // 交换 - 比较操作是比较原子变量值和所提供的期望值，
    // 如果二者相等，则this存储提供的期望值desired，
    // 如果不等则将期望值expected更新为原子变量的实际值，更新成功则返回true反之则返回false
    // compare_exchange_strong(T & expected, T desired, ......)
    // 如果当前的变量this的值等于expected值时，则将this值改为desired，并返回true；否则，不对this的值进行修改，expected被赋值为this的值，并返回false.
    {
        atomic<int> a;

        //1. use store()
        a.store(100);

        cout << "\n 1. After a.store(100) : a = " << a << endl;

        //2. use load()
        int x = a.load();
        cout << "\n 2. After x=a.load()   : x = " << x << endl;

        //3. use exchange()
        int y = a.exchange(200);
        cout << "\n 3. a.exchange(200) will return original value of a :" << y << endl;
        cout << "\n 4. After a.exchange(200), a=" << a << endl;

        //4. usecompare_exchange_weak
        int expected1 = 300;
        int expected2 = 200;
        cout << "\n 5. test compare_exchange_weak()\n";

        cout << "      a = " << a << ", expecte1 = " << expected1 << ", desired = 400" << endl;
        bool isSucess = a.compare_exchange_weak(expected1, 400);
        cout << "     Is first exchage sucess: " << (isSucess ? "Sucess" : "Fail") << ".      a = " << a << "; expeced1 = " << expected1 << endl;

        cout << "\n      a = " << a << ", expecte2 = " << expected2 << ", desired = 400" << endl;
        isSucess = a.compare_exchange_weak(expected2, 400);
        cout << "     Is second exchage sucess: " << (isSucess ? "Sucess" : "Fail") << ".   a =  " << a << "; expeced2 = " << expected2 << endl;


        //5. usecompare_exchange_strong
        int expected3 = 500;
        int expected4 = 400;
        cout << "\n 6. test compare_exchange_strong()\n";

        cout << "      a = " << a << ", expecte3 = " << expected3 << ", desired = 500" << endl;
        isSucess = a.compare_exchange_strong(expected3, 600);
        cout << "     Is first exchage sucess: " << (isSucess ? "Sucess" : "Fail") << ".      a = " << a << "; expeced3 = " << expected3 << endl;

        cout << "\n      a = " << a << ", expecte4 = " << expected4 << ", desired = 600" << endl;
        isSucess = a.compare_exchange_strong(expected4, 600);
        cout << "     Is second exchage sucess: " << (isSucess ? "Sucess" : "Fail") << ".   a =  " << a << "; expeced4 = " << expected4 << endl;
    }

    /// 特化成员函数
    /*
        特化成员函数 	        描述	说明
        fetch_add	        原子地以当前值和参数的算术加法结果替换掉当前值，并返回原始值。	        适用于整形和指针类型的std::atomic 特化版本
        fetch_sub	        原子地以当前值和参数的算术减法结果替换掉当前值，并返回原始值。	        适用于整形和指针类型的std::atomic 特化版本
        fetch_and	        原子地以当前值与参数进行 “与操作”， 并返回原始值，整个操作是原子性的	只适用于整形的原子对象
        fetch_or	        原子地以当前值与参数进行 “或操作” ，并返回原始值，整个操作是原子性的	只适用于整形的原子对象
        fetch_xor	        原子地以当前值与参数进行 “异或操作” ，并返回原始值，整个操作是原子性的	只适用于整形的原子对象
        operator++	        令原子值增加一，并返回生成的值	                                     适用于整形和指针类型的std::atomic 特化版本
        operator++(int) 	令原子值增加一，并返回之前的值	                                     适用于整形和指针类型的std::atomic 特化版本
        operator–-	        令原子值减一，并返回生成的值	                                     适用于整形和指针类型的std::atomic 特化版本
        operator–-(int)	    令原子值减一，并返回之前的值	                                     适用于整形和指针类型的std::atomic 特化版本
        operator+=		                                                                       适用于整形和指针类型的std::atomic 特化版本
        operator-=		                                                                       适用于整形和指针类型的std::atomic 特化版本
        operator&=		                                                                       只适用于整形的原子对象
        operator|=		                                                                       只适用于整形的原子对象
        operator^=		                                                                       只适用于整形的原子对象
    */
    {
        atomic_init(&a, 0);
        b = 0;

        thread th[THREAD_NUM];
        for (int i = 0; i < THREAD_NUM; ++i) {
            th[i] = thread(incNumber, 100);
        }

        for (int i = 0; i < THREAD_NUM; ++i) {
            if (th[i].joinable())
                th[i].join();
        }

        cout << " a = " << a << endl;
        cout << " b = " << b << endl;
    }

    /// atomic_flag
    // atomic_flag是一种简单的原子类型，表示一个布尔标志，该类型的对象只有两种状态：成立或置零。
    // 只支持两种操作：test_and_set和clear。
    {
        // 构造
        // std::atomic_flag 只有默认构造函数，拷贝构造函数已被禁用，因此不能从其他的 std::atomic_flag 对象构造一个新的 std::atomic_flag 对象。
        // automic_flag内含又一个标志位，在使用之前使用宏ATOMIC_FLAG_INIT进行初始化，将其中的标志初始化为置零状态。
        // 无论在哪里声明、处于什么作用域，atomic_flag永远以置零状态开始。

        // 1. test_and_set()
        // 检测其中的标志位，如果是0，就置位1，返回0；如果是1就不变，返回1，这些操作都是原子性的。
        // 2. clear()
        // 用于把标志位置位0。使用前面说的ATOMIC_FLAG_INIT对std::atomic_flag 对象进行初始化，那么可以保证该 std::atomic_flag 对象在创建时处于 clear 状态。
        // 可以看出atomic_flag严格受限，无法用作普通的布尔标志，因此最好还是使用atomic<bool>
    }

    /// 内存顺序（memory_order)
    // atomic的相关函数，基本都有一个memory_order的选项可供使用者去选择。
    /*
        由于CPU和编译器为了提高程序的执行效率，很有可能会对代码做乱序优化，将代码重新打乱，排序，提前缓存给cpu去执行，
        这个乱序优化在单线程上是没有问题的，因为编译器会保证打乱后的代码的语意和打乱之前是一样的。

        但是在多线程编程中，这个乱序优化很有可能会带来副作用：因为不同线程之间的缓冲区是不可见的，
        如果当两个线程之间的变量有某种关系的依赖的时候，这种依赖就可能因为cpu的乱序执行而被破坏掉，
        因为在cpu看来，单独一个线程内，这些变量是没有依赖的，就做了乱序优化，就导致了副作用。

        所以，使用内存顺序来控制编译器的行为，以防程序得到不预期的结果
    */

    typedef enum memory_order {
        memory_order_relaxed,   // relaxed
        memory_order_consume,   // consume
        memory_order_acquire,   // acquire
        memory_order_release,   // release
        memory_order_acq_rel,   // acquire/release
        memory_order_seq_cst    // sequentially consistent
    } memory_order;
    /*
        memory_order_relaxed
        在某个时间点执行该原子操作。这是最松散的内存顺序，没有同步或顺序制约，仅对此操作要求原子性，不能保证不同线程中的内存访问是按照原子操作的顺序进行的。即只保证当前操作的原子性，不考虑线程间的同步，其他线程可能读到新值，也可能读到旧值。

        memory_order_consume
        一旦释放线程中所有对内存的访问(这些访问依赖于释放操作(并且对加载线程有副作用))都发生了，则命令执行该操作。

        memory_order_acquire
        一旦释放线程中的所有内存访问(这些访问对加载线程有副作用)都发生了，则命令执行该操作。

        memory_order_release
        该操作在消耗或获取操作之前执行，作为对内存的其他访问的同步点，这些访问可能对加载线程产生副作用。

        memory_order_acq_rel
        该操作加载获取和存储释放(如上面的memory_order_acquisition和memory_order_release所定义)。

        memory_order_seq_cst
        该操作以顺序一致的方式进行排序：使用该内存顺序的所有操作都是在所有可能对涉及的其他线程产生副作用的内存访问都已经发生之后才执行的。这是最严格的内存顺序，意味着操作不能重排，通过非原子内存访问确保线程交互之间的意外副作用最小。对于消耗和获取负载，顺序一致的存储操作被认为是释放操作。

        如果没有为特定的操作指定一个顺序选项，则内存顺序选项对于所有原子类型默认都是memory_order_seq_cst，即按照最严格内存顺序执行。
    */

    return 0;
}


void incNumber(int num) {
    for (int i = 0; i < num; ++i) {
        this_thread::sleep_for(chrono::milliseconds(1));
        a.fetch_add(1);
        b += 1;
    }
}

/*
memory_order_relaxed
唯一的要求是在同一线程中，对同一原子变量的访问不可以被重排，不同的原子变量的操作顺序是可以重排的。它不提供任何跨线程的内存顺序保证。
memory_order_release & memory_order_acquire & memory_order_consume
Acquire-Release能保证不同线程之间的Synchronizes-With关系，这同时也约束到同一个线程中前后语句的执行顺序。release语句之前的所有变量的读写操作(including non-atomic and relaxed atomic)都对另一个线程中的acquire之后的代码可见。目前memory_order_consume是不建议使用的。
memory_order_acq_rel
它结合了memory_order_acquire 和 memory_order_release 的特性，确保了本线程原子操作的读取时能看到其他线程的写入（acquire 语义），并且本线程的写入对其他线程可见（release 语义），主要用于read-modify-write操作，如fetch_sub/add或compare_exchange_strong/weak。
memory_order_seq_cst
它满足memory_order_acq_rel的所有特性，除此之外，它强制受影响的内存访问传播到每个CPU核心。它不仅保证了单个原子变量操作的全局顺序，而且保证了所有使用顺序一致性内存序的原子变量之间的操作顺序在所有线程的观测中是一致的。
*/