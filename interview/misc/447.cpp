#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int eucl_dist(const vector<int>& point1, const vector<int>& point2) {
    return (point1[0] - point2[0]) * (point1[0] - point2[0]) +
        (point1[1] - point2[1]) * (point1[1] - point2[1]);
}

int An2(int x) { return x * (x - 1); }

int numberOfBoomerangs(vector<vector<int>>& points) {
    int size = points.size();
    int ans = 0;
    for (int i = 0; i < size; ++i) {
        unordered_map<int, int> m;
        for (int j = 0; j < size; ++j) {
            if (i == j)
                continue;
            m[eucl_dist(points[i], points[j])]++;
        }
        for (auto elem : m) {
            if (elem.second > 1)
                ans += An2(elem.second);
        }
    }
    return ans;
}
int main() {
    int n; cin >> n;
    vector<vector<int>> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i) {
        vector<int> v;
        int x, y; cin >> x >> y;
        v.push_back(x), v.push_back(y);
        points.push_back(v);
    }
    std::cout << numberOfBoomerangs(points) << std::endl;
    return 0;
}
