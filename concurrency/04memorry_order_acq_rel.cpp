#include <atomic>
#include <iostream>
#include <thread>

struct Node {
    int data;
    Node* next;
};

std::atomic<Node*> head{ nullptr };

void print_list() {
    Node* current = head.load(std::memory_order_acquire);
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void append(int value) {
    Node* new_node = new Node{ value, nullptr };

    // 使用 memory_order_acq_rel 来确保对 head 的修改对其他线程可见, 同时确保看到其他线程对 head 的修改
    Node* old_head = head.exchange(new_node, std::memory_order_acq_rel);
    //std::cout << value << std::endl;
    new_node->next = old_head;
}

void thread_func() {
    for (int i = 0; i < 10; ++i) {
        append(i);
    }
}

int main() {
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    t1.join();
    t2.join();


    return 0;
}