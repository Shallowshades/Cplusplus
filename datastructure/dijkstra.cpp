#include <iostream>

using namespace std;

const int N = 1e3 + 10;
const int inf = 0x3f3f3f3f;

int n, m;
int a[N][N];
bool vis[N];
int dist[N];

void print() {
    for (int i = 0; i < n; ++i) {
        cout << dist[i] << " ";
    }
    cout << endl;
}

void dijkstra() {
    fill(vis, vis + N, false);
    fill(dist, dist + N, inf);
    dist[0] = 0;
    for (int i = 0; i < n; ++i) {
        int k = -1;
        for (int j = 0; j < n;++j) {
            if (!vis[j] && (k == -1 || dist[k] > dist[j])) {
                k = j;
            }
        }
        vis[k] = true;
        for (int j = 1; j < n; ++j) {
            dist[j] = min(dist[j], dist[k] + a[k][j]);
        }
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        a[x][y] = a[y][x] = z;
    }

    dijkstra();
    print();
    return 0;
}