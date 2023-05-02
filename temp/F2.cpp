#include <iostream>
#include <vector>

using namespace std;

/*
北京轻而易举笔试题 F 一、层板等分衣柜
描述：
给定一个高度为 2000mm 的柜子空间，以及 n 个层板距离柜子底部高度，满足移动层板位置
使得层板等分衣柜的空间。计算所有移动层板的顺序。
层板号自下向上依次排列，1，2..n。层板需要考虑空间位置，不能跨层板移动。
示例 1
输入：n = 3，zs = 50，60，1000 //3 50 60 1000
输出：
3 2 1
示例 2
输入：n = 4，zs = 50，600，700，1000 //4 50 600 700 1000
输出：
1，4，3，2
4，1，3，2
4，3，1，2
4，3，2，1
提示 1：1 <= n <= 10
提示 2：输出结果需要按小到大排
*/

const int N = 12;
bool book[N];

void dfs(double* const a, const int& n, vector<int>& v, vector<vector<int>>& s, const double average) {
    for (int i = 0; i < n; ++i) {
        if (!book[i] && (i + 1) * average < a[i + 1]) {
            v.push_back(i + 1);
            if (v.size() == n) {
                s.push_back(v);
                v.pop_back();
                return;
            }
            book[i] = true;
            double tmp = a[i];
            a[i] = (i + 1) * average;
            dfs(a, n, v, s, average);
            book[i] = false;
            v.pop_back();
            a[i] = tmp;
        }
    }
}

int main() {

    int n = 0;
    double average, a[N];
    cin >> n;
    average = 2000.0 / n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    a[n] = 2001;

    vector<int> v;
    vector<vector<int>> s;

    fill(book, book + n, false);

    dfs(a, n, v, s, average);

    for (auto& vec : s) {
        for (int i = 0; i < vec.size(); i++) {
            if (i == 0) {
                cout << vec[i];
            }
            else {
                cout << ", " << vec[i];
            }
        }
        cout << endl;
    }

    return 0;
}