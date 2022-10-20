#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e3 + 10;

vector<int> G[N], topo;
int c[N];
int in[N]; // 存储每个结点的入度

bool topoSortQueue(int n) {
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (in[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.push_back(u);
    for (auto v : G[u]) {
      if (--in[v] == 0) {
        q.push(v);
      }
    }
  }
  if (topo.size() == n) {
    for (auto x : topo)
      cout << x << ' ';
    cout << endl;
    return true;
  } else {
    return false;
  }
}

bool dfs(int u) {
  c[u] = -1; //该点正在被深搜
  for (int v : G[u]) {
    if (c[v] == -1) //  你搜到了正在搜索的点，说明这是个环
      return false;
    else if (!c[v] && !dfs(v))
      return false;
  }

  //此时，从u点可到达的点都已搜过，并且入队
  //满足条件u在v之前，不会有v到u的路（有的话就是环了）（逆序放入）

  c[u] = 1; //该点已被搜过
  topo.push_back(u);
  return true;
}

bool toposort(int n) {
  topo.clear();
  memset(c, 0, sizeof(c));
  for (int i = 0; i < n; i++)
    if (!c[i] && !dfs(i))
      return false;
  reverse(topo.begin(), topo.end());
  return true;
}

int main() {
  freopen("topo.txt", "r+", stdin);
  int m, n, x, y;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    G[x].push_back(y);
    ++in[y];
  }
  if (topoSortQueue(n))
    cout << "DAG\n";
  else
    cout << "NOT DAG\n";

  if (toposort(n)) {
    for (auto num : topo) {
      cout << num << " ";
    }
    cout << endl;
  }
  return 0;
}