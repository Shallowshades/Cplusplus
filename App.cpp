// App.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <queue>
#include <numeric>
#include <thread>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <deque>
#include <stack>
#include <cstring>

const int inf = 0x3f3f3f3f;

using namespace std;

class thread_pool {
public:
    thread_pool(int threads_num) : stop(false) {
        for (int i = 0; i < threads_num; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    function<void()> task;

                    {
                        unique_lock<mutex> lock(this->mtx);
                        this->cv.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty()) return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }

                    if (task)
                        task();
                    //std::cout << "Task completed one!\n";
                }
                });
        }
    }

    template<typename FUNC, typename... Args>
    void enqueue(FUNC&& func, Args&&... args) {
        unique_lock<mutex> lock(mtx);
        tasks.emplace([&]() { forward<FUNC>(func)(forward<Args>(args)...); });
        cv.notify_one();
    }

    ~thread_pool() {
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }

        cv.notify_all();
        for (auto& t : threads)
            t.join();
    }
protected:
private:
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop;
};

class MinStack {
public:
    MinStack() {

    }

    void push(int val) {
        nums.emplace_back(val);
        if (maintain.empty() || val <= maintain.back())
            maintain.emplace_back(val);
    }

    void pop() {
        if (nums.back() == maintain.back())
            maintain.pop_back();
        nums.pop_back();
    }

    int top() {
        return nums.back();
    }

    int getMin() {
        return maintain.back();
    }

private:
    vector<int> nums;
    vector<int> maintain;
};

void func() {
    std::cout << "func 1" << std::endl;
}

void func1(int num) {
    std::cout << "func 2 : " << num << "\n";
}

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val('\0'), left(nullptr), right(nullptr) {}
    TreeNode(char c, TreeNode* ptr1, TreeNode* ptr2) : val('\0'), left(ptr1), right(ptr2) {}
};

TreeNode* CreateBinaryTree(string postorder, string inorder) {
    if (postorder.empty()) return nullptr;
    TreeNode* node = new TreeNode();
    node->val = postorder.back();

    // find
    int pos = inorder.find(postorder.back());
    postorder.pop_back();

    // inorder group 
    string left(inorder.begin(), inorder.begin() + pos);
    string right(inorder.begin() + pos + 1, inorder.end());

    node->left = CreateBinaryTree(string(postorder.begin(), postorder.begin() + left.size()), left);
    node->right = CreateBinaryTree(string(postorder.end() - right.size(), postorder.end()), right);

    return node;

    /*
        string postorder = "CBEFDA";
        string inorder = "CBAEDF";
        TreeNode* root = CreateBinaryTree(postorder, inorder);
        string ans;
        queue<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode* cur = nodes.front(); nodes.pop();
            if (cur == nullptr) continue;
            ans.push_back(cur->val);
            nodes.push(cur->left);
            nodes.push(cur->right);
        }
        std::cout << ans << std::endl;
    */
}

int judge(vector<int>& nums, int val, int h) {
    int cnt = 0;
    for (int i = 0; i < nums.size(); ++i) {
        cnt += (nums[i] + val - 1) / val;
    }
    return cnt - h;

    /*
    string line;
    getline(cin, line);
    int h; cin >> h;
    stringstream ss(line);
    int num, ans = 0;
    vector<int> nums;
    while (ss >> num) {
        nums.emplace_back(num);
    }
    if (nums.size() <= h) {
        sort(nums.begin(), nums.end(), greater<int>());
        int l = 0, r = nums[0];
        while (l <= r) {
            int mid = (l + r) / 2;
            if (judge(nums, mid, h) > 0)
                l = mid + 1;
            else
                r = mid - 1;
        }
        ans = l; // [l, r]
    }
    std::cout << ans << std::endl;
    */
}

string BallGame() {
    vector<int> nums{ 4,5,6,7,0,1,2 };
    vector<int> target{ 6,4,0,1,2,5,7 };
    string ret;
    deque<int> basket;
    int k = 0;
    for (int i = 0; i < nums.size(); ++i) {
        basket.push_back(nums[i]);

        while (!basket.empty() && k < target.size()) {
            if (basket.front() == target[k]) {
                ret.push_back('L');
                basket.pop_front();
                ++k;
            }
            else if (basket.back() == target[k]) {
                ret.push_back('R');
                basket.pop_back();
                ++k;
            }
            else {
                break;
            }
        }
    }
    if (basket.empty() && k == target.size())
        return ret;
    else
        return "NO";
}

vector<string> FingerPlay() {
    struct player {
        string name;
        char check;
    };
    vector<player> players;
    vector<string> ret;

    string name;
    char check;
    player p;
    int cnt[3] = { 0 };
    while (cin >> name >> check) {
        p.name = name;
        p.check = check;
        players.emplace_back(p);
        cnt[check - 'A']++;
    }

    // 平局
    if (cnt[0] && cnt[1] && cnt[2]) ret.emplace_back("NULL");
    else {
        char check;
        if (cnt[0] && cnt[1]) check = 'A';
        else if (cnt[1] && cnt[2]) check = 'B';
        else check = 'C';

        for (int i = 0; i < players.size(); ++i) {
            if (players[i].check == check)
                ret.emplace_back(players[i].name);
        }
    }

    sort(ret.begin(), ret.end());

    return ret;
}

int JumpGripGame() {
    int n; cin >> n;
    vector<int> scores;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        scores.push_back(x);
    }
    int k; cin >> k;
    vector<int> dp(scores.size(), -inf);
    dp[0] = scores[0];
    for (int i = 1; i < scores.size(); ++i) {
        for (int j = i - k; j < i; ++j) {
            if (j < 0) j = 0;
            dp[i] = max(dp[i], dp[j] + scores[i]);
        }
    }

    int maxTotalScores = -inf;
    for (auto& num : dp) {
        maxTotalScores = max(maxTotalScores, num);
    }
    return maxTotalScores;
}

namespace AutoDrive {
    const int N = 2e3 + 10;
    const int dir[8] = { 1,0,0,1,-1,0,0,-1 };
    int maps[N][N];
    bool vis[N][N];
    struct node { int x, y, gas; };
    int m, n;
    bool success = false;    // 是否能到达终点
    int record = -1;     // 第一次到加油站

    int ans = inf;
    void dfs(int x, int y, int gas) {
        if (x == m - 1 && y == n - 1 && gas <= 100) {
            if (record == -1) // 未途径加油站
                ans = min(gas, ans);
            else
                ans = min(ans, record);
            success = true;
            return;
        }
        if (gas > 100) return;

        for (int i = 0; i < 4; ++i) {
            int _x = x + dir[2 * i];
            int _y = y + dir[2 * i + 1];
            if (_x >= 0 && _x < m && _y >= 0 && _y < n && !vis[_x][_y]) {
                if (maps[_x][_y] == 0) continue;
                else if (maps[_x][_y] == -1) {
                    // 判断是否为第一次途径加油站
                    if (record == -1) {
                        record = gas;
                        vis[_x][_y] = true;
                        dfs(_x, _y, 0);
                        vis[_x][_y] = false;
                        record = -1;
                    }
                    else {
                        vis[_x][_y] = true;
                        dfs(_x, _y, 0);
                        vis[_x][_y] = false;
                    }
                }
                else {
                    if (gas + maps[_x][_y] <= 100) {
                        vis[_x][_y] = true;
                        dfs(_x, _y, gas + maps[_x][_y]);
                        vis[_x][_y] = false;
                    }
                }
            }
        }
    }

    int AutoDrive() {
        cin >> m >> n;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> maps[i][j];
            }
        }
        dfs(0, 0, maps[0][0]);
        return success ? ans : -1;
    }
}

// 内联导入到父命名空间 唯一 否则会造成二义性
namespace Parent {
    namespace V1 { void foo() { std::cout << "foo v1.0" << std::endl; } }
    inline namespace V2 { void foo() { std::cout << "foo v2.0" << std::endl; } }
}

// 嵌套命名空间
namespace A::B::C {
    int foo() { return 5; }
}

//
void test() {

    std::cout << "std::numeric_limits<long long>::max() = " << std::numeric_limits<long long>::max() << std::endl;
    std::cout << "std::numeric_limits<long long>::min() = " << std::numeric_limits<long long>::min() << std::endl;
    std::cout << "std::numeric_limits<unsigned long long>::max() = " << std::numeric_limits<unsigned long long>::max() << std::endl;
    std::cout << "std::numeric_limits<unsigned long long>::min() = " << std::numeric_limits<unsigned long long>::min() << std::endl;
    //std::cout << AutoDrive::AutoDrive() << std::endl;

    char32_t utf32c = U'好';
    std::cout << utf32c << std::endl;

    Parent::foo();
}

// 参观园区
namespace ParkVisitPath {
    const int N = 1e3 + 10;
    int park[N][N], dp[N][N];
    void Solution() {
        int m, n; cin >> m >> n;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> park[i][j];
            }
        }
        //memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (park[i][j]) continue;
                if (!i && !j) continue;
                int num = 0;
                if (i - 1 >= 0) num += dp[i - 1][j];
                if (j - 1 >= 0) num += dp[i][j - 1];
                dp[i][j] = num;
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << dp[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << dp[m - 1][n - 1] << std::endl;
    }
}

namespace TransfromTime {
    // 思路远比代码重要
    inline namespace V1 {
        void Solution() {
            int m, n; cin >> m >> n;
            double maxTime = 0;
            for (int i = 0; i < m; ++i) {
                double x;  cin >> x;
                maxTime = max(maxTime, 1.0 * n / x + i);
                //std::cout << "maxTime = " << maxTime << std::endl;
            }
            std::cout << maxTime - m + 1 << std::endl;

        }
    }
}

namespace TailWordLength {
    inline namespace V1 {
        int Solution(string line) {
            int pos = line.find_last_of(' ');
            if (pos == string::npos) return line.size();
            else return line.size() - pos - 1;
        }
    }
}

namespace WoodValue {
    inline namespace V1 {
        vector<int> Solution(int n) {
            vector<int> ans;
            if (n < 4) {
                ans.push_back(n);
                return ans;
            }
            int maxVal = 0;
            for (int i = 2; i <= 25 && i <= n / 2; ++i) {
                int sum = 1;
                int len = n;
                vector<int> tmp;
                while (len > 0) {
                    if (len > i && len < 2 * i) {
                        sum *= len;
                        tmp.push_back(len);
                        len = 0;
                    }
                    else {
                        sum *= i;
                        len -= i;
                        tmp.push_back(i);
                    }
                }
                cout << " i = " << i << "; sum = " << sum << " --- ";
                for (auto& num : tmp) {
                    cout << num << " ";
                }
                cout << endl;
                if (sum > maxVal) {
                    maxVal = sum;
                    ans.swap(tmp);
                }

            }
            return ans;
        }
    }
}

namespace GoodValue {
    inline namespace V1 {
        int Solution() {
            const int N = 1e4 + 10;
            int wa, wb, wt, pa, pb, dp[N] = { 0 };
            cin >> wa >> wb >> wt >> pa >> pb;
            dp[wa + wb] = pa + pb;
            for (int i = wa + wb; i <= wt; ++i) {
                if (dp[i]) {
                    if (i + wa <= wt) dp[i + wa] = max(dp[i] + pa, dp[i + wa]);
                    if (i + wb <= wt) dp[i + wb] = max(dp[i] + pb, dp[i + wb]);
                }
            }

            return dp[wt];
        }
    }
}

namespace RecommendVariety {
    inline namespace V1 {
        void Solution() {
            int n, k; cin >> n >> k;
            vector<vector<int>> widgets(n);
            vector<deque<int>> lists;
            string line; getchar();
            while (getline(cin, line)) {
                stringstream ss(line);
                deque<int> list;
                int num;
                while (ss >> num) {
                    list.push_back(num);
                }
                lists.emplace_back(list);
            }

            for (int i = 0; i < lists.size(); ++i) {
                for (int j = 0; j < lists[i].size(); ++j) {
                    std::cout << lists[i][j] << " ";
                }
                std::cout << " " << std::endl;
            }

            bool empty = false;
            int i = 0, j = 0, cnt = 0;
            while (!empty) {
                j = 0;
                while (j < n) {
                    while (i < lists.size() && lists[i].empty()) ++i;
                    if (i == lists.size()) {
                        empty = true;
                        break;
                    }
                    widgets[j++].push_back(lists[i].front());
                    lists[i].pop_front();
                    if (++cnt == n) {
                        ++i;
                        cnt = 0;
                        i %= lists.size();
                    }
                }

                for (int i = 0; i < widgets.size(); ++i) {
                    for (int j = 0; j < widgets[i].size(); ++j) {
                        std::cout << widgets[i][j] << " ";
                    }
                    std::cout << " " << std::endl;
                }

            }

            for (int i = 0; i < widgets.size(); ++i) {
                for (int j = 0; j < k; ++j) {
                    std::cout << widgets[i][j] << " ";
                }
            }
            std::cout << " " << std::endl;
        }
    }
}

namespace Flights {
    namespace V1 {
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
            const int INF = 0x3f3f3f3f;
            vector<vector<int>> g(n, vector<int>(n, -1));
            for (int i = 0; i < flights.size(); ++i) {
                g[flights[i][0]][flights[i][1]] = flights[i][2];
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << g[i][j] << " ";
                }
                std::cout << " " << std::endl;
            }
            std::cout << "--------------------------" << std::endl;

            vector<int> dist(n, INF);
            dist[src] = 0;
            for (int limit = 0; limit <= k; ++limit) {
                vector<int> clone(dist);
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (g[i][j] != -1)
                            dist[j] = min(dist[j], clone[i] + g[i][j]);
                    }
                }

                for (int i = 0; i < dist.size(); ++i) std::cout << dist[i] << " "; std::cout << " " << std::endl;
            }

            return dist[dst] >= INF ? -1 : dist[dst];
        }
    }

    inline namespace V2 {
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
            const int INF = 0x3f3f3f3f;
            vector<vector<int>> g(n, vector<int>(n, -1));
            for (int i = 0; i < flights.size(); ++i) {
                g[flights[i][0]][flights[i][1]] = flights[i][2];
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << g[i][j] << " ";
                }
                std::cout << " " << std::endl;
            }
            std::cout << "--------------------------" << std::endl;

            vector<int> dist(n, INF);
            dist[src] = 0;
            using pii = pair<int, int>;
            queue<pii> q;
            q.push({ src, 0 });
            int ans = INF;
            while (!q.empty() && k >= 0) {
                int size = q.size();
                std::cout << "size = " << size << std::endl;
                for (int j = 0; j < size; ++j) {
                    pii cur = q.front(); q.pop();
                    for (int i = 0; i < n; ++i) {
                        if (g[cur.first][i] == -1) continue;
                        if (cur.second + g[cur.first][i] < dist[i]) {
                            dist[i] = cur.second + g[cur.first][i];
                            q.push({ i, dist[i] });
                        }

                        if (i == dst) {
                            ans = min(ans, dist[dst]);
                        }
                    }
                }
                for (int i = 0; i < dist.size(); ++i) std::cout << dist[i] << " "; std::cout << " " << std::endl;
                --k;
            }

            return ans >= INF ? -1 : ans;
        }
    }
};

namespace MaxSuccess {
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int src, int dst) {
        using pid = pair<int, double>;
        vector<vector<pid>> maps(n);
        for (int i = 0; i < edges.size(); ++i) {
            maps[edges[i][0]].push_back({ edges[i][1], succProb[i] });
            maps[edges[i][1]].push_back({ edges[i][0], succProb[i] });
        }
        vector<bool> vis(n, false);
        vector<double> success(n, -1.0);
        success[src] = 1.0;

        while (true) {
            int k = -1;
            for (int i = 0; i < n; ++i) {
                if (!vis[i] && (k == -1 || success[k] < success[i]))
                    k = i;
            }

            if (k == -1) break;
            vis[k] = true;

            for (int i = 0; i < maps[k].size(); ++i) {
                int to = maps[k][i].first;
                if (vis[to]) continue;
                success[to] = max(success[k] * maps[k][i].second, success[to]);
            }
        }

        return success[dst] <= 0.0 ? 0 : success[dst];
    }
}

namespace NumberSolution {
    void Solution() {
        int n; cin >> n;
        /* for (int i = 2; i < 1000; ++i) {
             if (2 * n % i == 0) {
                 int sum = 2 * n / i;
                 int x = (sum + 1 - i) / 2;
                 if (x <= 0) continue;
                 if ((x + x + i - 1) * i / 2 != n) continue;
                 for (int j = x; j < x + i; ++j) {
                     cout << j << " ";
                 }
                 cout << endl;
                 break;
             }
         }*/
        auto print = [&n](int l, int r) {
            cout << n << "=";
            for (int i = l; i <= r; ++i) {
                cout << i;
                if (i != r) cout << "+";
            }
            cout << endl;
            };
        int l = 1, sum = 0;
        int minLen = 0x3f3f3f3f, start = -1;
        for (int r = 1; r < n; ++r) {
            sum += r++;
            if (sum == n) {
                minLen = r - l;
                start = l;
            }
            else {
                while (sum > n && l < r) sum -= l++;
                if (sum == n && minLen > r - l)
                    minLen = r - l, start = l;
            }
            //cout << "l = " << l << " r = " << r << " sum = " << sum << endl;
        }

        if (start == -1) cout << -1 << endl;
        else print(start, start + minLen - 1);
        //cout << "min len = " << minLen << endl;
    }
}

namespace HotOrder {
    struct project {
        string name;
        int val;

        project(string _name, int _val) : name(_name), val(_val) {}
    };

    bool cmp(project a, project b) {
        if (a.val == b.val) return a.name < b.name;
        return a.val > b.val;
    }

    string& lower(string& str) {
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] = tolower(str[i]);
        }
        return str;
    }

    void Solution() {
        int n; cin >> n;
        int wv, sv, fv, iv, mv; cin >> wv >> sv >> fv >> iv >> mv;
        vector<project> projects;
        for (int i = 0; i < n; ++i) {
            string name;
            int watch, star, fork, issue, mr;
            cin >> name >> watch >> star >> fork >> issue >> mr;
            int val = watch * wv + star * sv + fork * fv + issue * iv + mr * mv;
            projects.push_back(project(lower(name), val));
        }
        sort(projects.begin(), projects.end(), cmp);
        for (int i = 0; i < projects.size(); ++i) {
            std::cout << projects[i].name << std::endl;
        }
    }
}

int main() {



    return 0;
}
