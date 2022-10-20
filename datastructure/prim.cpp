/**
 * @file prim.cpp
 * @author your name (you@domain.com)
 * @brief prim 最小生成树 适用于边稠密图
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <queue>
#include <vector>

using pii = std::pair<int, int>;

// c++2a auto
int prim(const std::vector<std::vector<pii>>& g, int start) {

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    std::vector<bool>                                             book(g.size(), false);
    int                                                           mincost = 0;
    q.push(std::make_pair(0, start));
    while(!q.empty()) {
        pii p = q.top();
        q.pop();
        start = p.second;
        if(book[start] == true) continue;
        mincost += p.first;
        book[start] = true;
        for(const pii& neighbor : g[start]) {
            int end = neighbor.second;
            if(!book[end]) q.push(neighbor);
        }
    }
    return mincost;
}

int main() {
    freopen("MST.txt", "r+", stdin);
    int n, m;
    std::cin >> n >> m;

    // g[x][i]存储的是pair<data,y>
    std::vector<std::vector<pii>> g(n + 1);
    for(int i = 0; i < m; ++i) {
        int x, y, data;
        std::cin >> x >> y >> data;
        g[x].push_back(std::make_pair(data, y));
        g[y].push_back(std::make_pair(data, x));
    }

    std::cout << prim(g, 1) << std::endl;
    return 0;
}