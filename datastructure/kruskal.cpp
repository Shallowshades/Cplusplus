/**
 * @file MST.cpp
 * @author your name (you@domain.com)
 * @brief kruskal算法 最小生成树 适用于边稀疏图
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "disjointset.h"
#include <algorithm>
#include <iostream>

constexpr int N = 1e3 + 10;

struct edge {
    int x, y, data;

    bool operator<(const edge& e) const {
        if(this->data < e.data) return true;
        return false;
    }
};

int Kruskal(edge p[], int n, int m) {
    int s[N];
    Init(s, n);
    int cost = 0, cnt = 0;  // 最小花费 边数
    std::sort(p, p + m);
    for(int i = 0; i < n; ++i) {
        if(Find(s, p[i].x) != Find(s, p[i].y)) {
            cost += p[i].data;
            Union(s, p[i].x, p[i].y);
            ++cnt;
        }
        if(cnt == n - 1) return cost;
    }
    return -1;
}

int main() {

    freopen("MST.txt", "r+", stdin);

    int n, m;  //节点数 边数
    std::cin >> n >> m;

    edge p[N];
    for(int i = 0; i < m; ++i) std::cin >> p[i].x >> p[i].y >> p[i].data;

    std::cout << Kruskal(p, n, m) << std::endl;

    return 0;
}
