/**
 * @file pointer.cpp
 * @author your name (you@domain.com)
 * @brief T* 匹配 Type*， T = Type， * = *
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

//匹配非指针对象
template <typename T>
class RemovePointer{
public:
    typedef T Result;
};

//特化匹配指针对象
template<typename T>
class RemovePointer<T*>{
public:
    typedef T Result;
};

void foo(){
    RemovePointer<float*>::Result x = 5.0f;
    std::cout << x << std::endl;
}

void copyElem(void* dst, const void* src){
    //TODO: copy
}

void movePointer(const void* ptr, size_t bytes){
    //TODO: move pointer
}

//c中的copy
void copy(void* dst, const void* src, size_t elemSize, size_t elemCount, void(*copyElem)(void* dstElem,const void* srcElem)){
    const void* reader = src;
    void* writer = dst;
    for(size_t i = 0; i < elemCount; ++i){
        copyElem(writer,reader);
        movePointer(reader,elemSize);
        movePointer(writer,elemSize);
    }
}

//语言设计最重要的一点原则：一致性

//C++采用模板实现
template <typename T>
void copy(T* dst, const T* src, size_t elemCount){
    for(size_t i = 0;i < elemCount; ++i){
        dst[i] = src[i];
    }
}

void print(const int* const array){
    for(int i = 0 ; i < 13; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){

    foo();

    int a[13] = {1,2,3,4,5,6,7,8};
    int b[13] = {0};
    print(a);
    print(b);
    copy(b,a,13);
    print(a);
    print(b);
    return 0;
}