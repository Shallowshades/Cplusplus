#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <sstream>

using namespace std;

class thread_pool;
void worker(thread_pool* pool);

class thread_pool {

    friend void worker(thread_pool* pool);
public:
    thread_pool(int threads_num);
    template<typename FUNC, typename... Args>
    void enqueue(FUNC&& func, Args&&... args);
    ~thread_pool();

private:
    vector<thread*> threads;
    queue<function<void()>> tasks; // 参数个数任意 返回类型任意（接收时有没有问题？）
    mutex mtx;
    condition_variable cv;
    bool stop;
};

thread_pool::thread_pool(int threads_num) : stop(false) {
    for (int i = 0; i < threads_num; ++i) {
        //worker为成员函数时，在内部调用自带this，解析为this->worker(),会解析成函数调用
        //将worker改为友元函数， 但这样做将worker暴露在外，影响？？？
        thread* t = new thread(worker, this);
        threads.emplace_back(std::move(t));
    }

    for (int i = 0; i < threads_num; ++i)
        threads[i]->detach();
}

template<typename FUNC, typename... Args>
void thread_pool::enqueue(FUNC&& func, Args&&... args) {
    unique_lock<mutex> lock(mtx);
    tasks.emplace([&] { forward<FUNC>(func)(forward<Args>(args)...); });
    cv.notify_one();
}

thread_pool::~thread_pool() {
    {
        unique_lock<mutex> lock(mtx);
        stop = true;
    }

    cv.notify_all();
    for (int i = 0; i < threads.size(); ++i)
        delete threads[i];
}

void worker(thread_pool* pool) {
    stringstream ss;
    ss << "create one " << this_thread::get_id() << "\n";
    cout << ss.str();
    while (!pool->stop) {
        function<void()> task;

        //------
        {
            unique_lock<mutex> lock(pool->mtx); // 局部锁
            pool->cv.wait(lock, [&pool] {return pool->stop || !pool->tasks.empty(); });
            if (pool->tasks.empty()) continue;
            task = move(pool->tasks.front());
            pool->tasks.pop();
        }
        //------

        //operator bool 检查是否包含了有效的目标(公开成员函数)
        if (task) task();
    }
}

void func() {
    //std::cout << "come on!!!\n";
    this_thread::sleep_for(chrono::milliseconds(20));
    std::cout << std::this_thread::get_id() << " : Task completed void\n";
}

void func1(int a) {
    this_thread::sleep_for(chrono::milliseconds(20));
    stringstream ss;
    ss << std::this_thread::get_id() << " : Task completed params " << a << endl;
    cout << ss.str();
}

bool func2() {
    this_thread::sleep_for(chrono::milliseconds(20));
    stringstream ss;
    ss << std::this_thread::get_id() << " : Task completed bool " << endl;
    cout << ss.str();
    return true;
}

int main() {
    thread_pool pool(10);
    function<void()> f = func;
    for (int i = 0; i < 100; ++i) {
        pool.enqueue(func1, i);
        this_thread::sleep_for(chrono::milliseconds(1));
        pool.enqueue(func);
        this_thread::sleep_for(chrono::milliseconds(1));
        pool.enqueue(func2);
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    //pool.enqueue(f);
    //pool.enqueue([]() {std::cout << "try once!!\n"; }); //部分回车没有输出
    this_thread::sleep_for(chrono::seconds(2));
}