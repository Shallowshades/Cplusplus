/**
 * @file nullptr.cpp
 * @author your name (you@domain.com)
 * @brief nullptr空指针
 * @version 0.1
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <type_traits>

void foo(char*);
void foo(int);

int main() {
    // decltype 用于类型推导，而 std::is_same 用于比较两个类型是否相同
    if(std::is_same<decltype(NULL), decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if(std::is_same<decltype(NULL), decltype((void*)0)>::value)
        std::cout << "NULL == (void *)0" << std::endl;
    if(std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullptr" << std::endl;

    foo(0);  // 调用 foo(int)
    // foo(NULL);    // 该行不能通过编译
    foo(nullptr);  // 调用 foo(char*)
    return 0;
}

void foo(char*) {
    std::cout << "foo(char*) is called" << std::endl;
}
void foo(int i) {
    std::cout << "foo(int) is called" << std::endl;
}