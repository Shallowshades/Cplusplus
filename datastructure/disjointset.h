/**
 * @file disjointset.cpp
 * @author your name (you@domain.com)
 * @brief 并查集
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>

void print(int s[], int n) {
    for(int i = 0; i < n; ++i) std::cout << s[i] << " ";
    std::cout << std::endl;
}

// 初始化并查集
void Init(int s[], int n) {
    for(int i = 0; i < n; ++i) s[i] = -1;
}

// 查找 原始版本
int Find(int s[], int x) {
    while(s[x] >= 0) x = s[x];
    return x;
}

// 查找 压缩路径版本
int Find_optimization(int s[], int x) {
    int root = x;
    while(s[root] >= 0) root = s[root];
    while(x != root) {  //将路径上的所有节点都挂到根节点上
        int tmp = s[x];
        s[x]    = root;
        x       = tmp;
    }
    return root;
}

// 并 原始版本
// 此时子节点所存储的是父节点，根节点存储的为-1
void Union(int s[], int root1, int root2) {
    if(root1 == root2) return;
    s[root2] = root1;
}

// 并 小树并大树 启发式合并
// 此时子节点所存储的是父节点，根节点存储的为-count，负的节点数
void Union_optimization(int s[], int root1, int root2) {
    if(root1 == root2) return;

    //存储的为负值
    if(s[root2] < s[root1]) std::swap(root1, root2);
    s[root1] += s[root2];
    s[root2] = root1;
}

/// 同时使用路径压缩和启发式合并之后，并查集的每个操作平均时间仅为α(n)，
/// 其中α(n)为阿克曼函数的反函数，其增长极其缓慢