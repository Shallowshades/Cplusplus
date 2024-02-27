#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int N = 1e2 + 10;

int m, t, ans;

struct herb_medicine {
    int t, val; // 时间 价值
    double f;   // 估值
}medicine[N];

bool operator < (herb_medicine a, herb_medicine b) { return  a.f > b.f; }

/// @brief 估值函数
/// @param idx 
/// @param t 
/// @return 
int func(int idx, int t) {
    int tot = 0;
    for (int i = 0; idx + i < m; ++i) {
        if (t >= medicine[idx + i].t) {
            t -= medicine[idx + i].t;
            tot += medicine[idx + i].val;
        }
        return (int)(tot + t * medicine[idx + i].f);
    }
    return tot;
}

void dfs(int idx, int time, int val) {
    ans = max(ans, val);
    if (idx > m) return;
    if (func(idx, time) + val > ans) // 不取当前，在估值的情况下还能高于当前收益
        dfs(idx + 1, time, val);
    if (medicine[idx].t <= time)    // 时间够， 取当前
        dfs(idx + 1, time - medicine[idx].t, val + medicine[idx].val);
}

int main() {

    cin >> t >> m;
    for (int i = 0; i < m; ++i) {
        cin >> medicine[i].t >> medicine[i].val;
        medicine[i].f = 1.0 * medicine[i].val / medicine[i].t;
    }
    sort(medicine, medicine + m);
    dfs(0, t, 0);
    cout << ans << endl;
    return 0;
}