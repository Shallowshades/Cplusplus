#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>

using namespace std;

mutex m;
condition_variable cv;
string data;
bool ready = false;
bool processed = false;

void worker_thread() {
    // wait for main send msg
    unique_lock<mutex> lk(m);
    cv.wait(lk, []() { return ready; });

    // after wait, own locker
    std::cout << "worker : is processing data" << std::endl;
    ::data += " -> processed";

    // send data to main
    processed = true;
    std::cout << "worker : over" << std::endl;

    lk.unlock();
    cv.notify_one();
}

int main() {

    thread worker(worker_thread);
    worker.detach();

    ::data = string("sample data");
    this_thread::sleep_for(chrono::milliseconds(1000));

    // send msg to worker thread
    {
        lock_guard<mutex> lk(m);
        ready = true;
        std::cout << "main : data was already" << std::endl;
    }

    cv.notify_one();

    // wait for worker
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk, []() { return processed; });
    }

    std::cout << "return to main : data = " << ::data << std::endl;

    return 0;
}