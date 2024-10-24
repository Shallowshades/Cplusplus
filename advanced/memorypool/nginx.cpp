/**
 *@file nginx.cpp
 * @author your name (you@domain.com)
 * @brief memory pool
 * @version 0.1
 * @date 2024-02-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>

using namespace std;

class memory_pool;
class small_block;
class big_block;

class small_block {
public:
    char* cur_usable_buffer;    // 指向该block的可用buffer的首地址
    char* buffer_end;           // 指向该block的buffer的尾地址
    small_block* next_block;    // 指向block链中的下一个small block
    size_t no_enough_times;     // 不足次数
};

class big_block {
public:
    char* big_buffer;       // big block buffer的首地址
    big_block* next_block;  // 链式结构， 指向下一个big block
};

//-------------------------------------
// | memory_pool | first small block |
//------------------------------------
class memory_pool {
public:
    size_t small_buffer_capacity;           // 单个small block的大小
    small_block* cur_usable_small_block;    // 分配小内存时，查找的起始地址
    big_block* big_block_start;             // big block的链首
    /// 柔性数组？？ 确保其在整个类的内存空间的末尾 不占用空间 但是有地址信息
    small_block small_block_start[0];       // small block的链首

    //API
public:
    static memory_pool* createPool(size_t capacity);
    static void destroyPool(memory_pool* pool);
    static char* createNewSmallBlock(memory_pool* pool, size_t size);
    static char* mallocBigBlock(memory_pool* pool, size_t size);
    static void* poolMalloc(memory_pool* pool, size_t size);
    static void freeBigBlock(memory_pool* pool, char* buffer_ptr);

};

memory_pool* memory_pool::createPool(size_t capacity) {
    // 第一个small block和memory pool 连在一起， 不需要单独free
    size_t total_size = sizeof(memory_pool) + sizeof(small_block) + capacity;
    void* tmp = malloc(total_size);
    //memset(tmp, 0, total_size);

    memory_pool* pool = (memory_pool*)tmp;
    printf("pool address : %p\n", pool);

    pool->small_buffer_capacity = capacity;
    pool->big_block_start = nullptr;
    pool->cur_usable_small_block = (small_block*)(pool->small_block_start);

    //
    small_block* sbp = (small_block*)(pool + 1);
    printf("first small block address:%p\n", sbp);

    // 初始化small_block对象
    sbp->cur_usable_buffer = (char*)(sbp + 1);
    printf("first small block buffer address:%p\n", sbp->cur_usable_buffer);
    sbp->buffer_end = sbp->cur_usable_buffer + capacity;
    sbp->next_block = nullptr;
    sbp->no_enough_times = 0;

    return pool;
}

void* memory_pool::poolMalloc(memory_pool* pool, size_t size) {
    if (size < pool->small_buffer_capacity) {
        small_block* tmp = pool->cur_usable_small_block;
        do {
            if (tmp->buffer_end - tmp->cur_usable_buffer > size) {
                char* res = tmp->cur_usable_buffer;
                tmp->cur_usable_buffer = tmp->cur_usable_buffer + size;
                return res;
            }
            tmp = tmp->next_block;
        } while (tmp);

        return createNewSmallBlock(pool, size);
    }
    return mallocBigBlock(pool, size);
}

char* memory_pool::createNewSmallBlock(memory_pool* pool, size_t size) {
    size_t malloc_size = sizeof(small_block) + pool->small_buffer_capacity;
    void* tmp = malloc(malloc_size);
    memset(tmp, 0, malloc_size);

    //init
    small_block* sbp = (small_block*)tmp;
    printf("new small block address:%p\n", sbp);
    sbp->cur_usable_buffer = (char*)(sbp + 1);
    printf("new small block buffer address:%p\n", sbp->cur_usable_buffer);
    sbp->buffer_end = (char*)tmp + malloc_size;
    sbp->next_block = nullptr;
    sbp->no_enough_times = 0;

    // 
    char* res = sbp->cur_usable_buffer;
    sbp->cur_usable_buffer = res + size;

    // find new start point
    // TODO: 感觉有问题， 有可能是我的问题
    small_block* p = pool->cur_usable_small_block;
    while (p->next_block) {
        if (p->no_enough_times > 4)
            pool->cur_usable_small_block = p->next_block;

        ++(p->no_enough_times);
        p = p->next_block;
    }

    p->next_block = sbp;

    if (pool->cur_usable_small_block == nullptr)
        pool->cur_usable_small_block = sbp;

    return res;
}

char* memory_pool::mallocBigBlock(memory_pool* pool, size_t size) {
    void* tmp = malloc(size);
    memset(tmp, 0, size);

    big_block* bbp = pool->big_block_start;
    int cnt = 0;
    while (bbp) {
        if (bbp->big_buffer == nullptr) {
            bbp->big_buffer = (char*)tmp;
            return bbp->big_buffer;
        }

        if (cnt > 3)
            break;

        bbp = bbp->next_block;
        ++cnt;
    }

    big_block* new_bbp = (big_block*)memory_pool::poolMalloc(pool, sizeof(big_block));
    new_bbp->big_buffer = (char*)tmp;
    new_bbp->next_block = pool->big_block_start;
    pool->big_block_start = new_bbp;

    return new_bbp->big_buffer;
}

void memory_pool::freeBigBlock(memory_pool* pool, char* buffer_ptr) {
    big_block* bbp = pool->big_block_start;
    while (bbp) {
        if (bbp->big_buffer == buffer_ptr) {
            free(bbp->big_buffer);
            bbp->big_buffer = nullptr;
            return;
        }
        bbp = bbp->next_block;
    }
}

void memory_pool::destroyPool(memory_pool* pool) {
    // free big block
    big_block* bbp = pool->big_block_start;
    while (bbp) {
        if (bbp->big_buffer) {
            printf("free big block address %p\n", bbp->big_buffer);
            free(bbp->big_buffer);
            bbp->big_buffer = nullptr;
        }
        bbp = bbp->next_block;
    }

    small_block* tmp = pool->small_block_start->next_block;
    while (tmp) {
        small_block* next = tmp->next_block;
        printf("free small block address %p\n", tmp);
        free(tmp);
        tmp = next;
    }

    /// 释放 pool + first small block ，对操作系统来说，他们是一个块
    free(pool);
}

int main() {
    memory_pool* pool = memory_pool::createPool(1024);
    //-分配小内存
    char* p1 = (char*)memory_pool::poolMalloc(pool, 2);
    fprintf(stdout, "little malloc1:%p\n", p1);
    char* p2 = (char*)memory_pool::poolMalloc(pool, 4);
    fprintf(stdout, "little malloc2:%p\n", p2);
    char* p3 = (char*)memory_pool::poolMalloc(pool, 8);
    fprintf(stdout, "little malloc3:%p\n", p3);
    char* p4 = (char*)memory_pool::poolMalloc(pool, 256);
    fprintf(stdout, "little malloc4:%p\n", p4);
    char* p5 = (char*)memory_pool::poolMalloc(pool, 512);
    fprintf(stdout, "little malloc5:%p\n", p5);

    //-测试分配不足开辟新的small block
    char* p6 = (char*)memory_pool::poolMalloc(pool, 512);
    fprintf(stdout, "little malloc6:%p\n", p6);

    //-测试分配大内存
    char* p7 = (char*)memory_pool::poolMalloc(pool, 2048);
    fprintf(stdout, "big malloc1:%p\n", p7);

    char* p8 = (char*)memory_pool::poolMalloc(pool, 4096);
    fprintf(stdout, "big malloc2:%p\n", p8);

    //-测试free大内存
    memory_pool::freeBigBlock(pool, p8);

    //-测试再次分配大内存（我这里测试结果和p8一样）
    char* p9 = (char*)memory_pool::poolMalloc(pool, 2048);
    fprintf(stdout, "big malloc3:%p\n", p9);

    //-销毁内存池
    memory_pool::destroyPool(pool);

    exit(EXIT_SUCCESS);
}