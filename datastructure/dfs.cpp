#include <stdio.h>
#include <iostream>

const int N = 1e3 + 10;
const int dir[8] = { 1,0,0,1,-1,0,0,-1 };

struct point { int x, y, t; };
struct group { int x, y, z, t; };
bool vis[N][N];
int arr[N][N];

int bfs(int a[][N], int m, int n) {
    //for (int i = 0; i < N; ++i) {
    //	for (int j = 0; j < N; ++j) {
    //		vis[i][j] = false;
    //	}
    //}
    point queue[N];
    int font = 0, rear = 0;
    queue[rear++] = { 0,0,0 };
    while (font != rear) {
        point cur = queue[font++];
        if (cur.x == m - 1 && cur.y == n - 1) return cur.t;
        int x = cur.x, y = cur.y, ex, ey;
        for (int i = 0; i < 4; ++i) {
            ex = x + dir[2 * i];
            ey = y + dir[2 * i + 1];
            if (ex >= 0 && ex < m && ey >= 0 && ey < n && !vis[ex][ey] && !a[ex][ey]) {
                vis[ex][ey] = true;
                queue[rear++] = { ex,ey,cur.t + 1 };
            }
        }
    }
    return -1;
}

bool book[9][9][9];
int bfs_water(int a, int b, int c, int d) {
    group queue[N];
    int font = 0, rear = 0;
    //auto push = [&](const group& g) { queue[rear++] = g; };
    //auto pop = [&]() { ++font; };
    queue[rear++] = { a, b, c, 0 };
    book[a][b][c] = true;
    int index[] = { 0,1,0,2,1,0,1,2,2,0,2,1 };
    int cap[] = { 8,5,3 };
    while (font != rear) {
        group cur = queue[font++];
        int x = cur.x, y = cur.y, z = cur.z;
        if (x == d || y == d || z == d)
            return cur.t;

        //x -> y, z 8 5 3
        auto pour = [](int& x, int& y, int cap) -> bool {
            if (x && y < cap) {
                int empty = cap - y;
                if (empty >= x) {
                    y += x;
                    x = 0;
                }
                else {
                    x -= empty;
                    y = cap;
                }
                return true;
            }
            return false;
            };

        for (int i = 0; i < 6; ++i) {
            int wid[] = { x,y,z };
            if (pour(wid[index[2 * i]], wid[index[2 * i + 1]], cap[index[2 * i + 1]]) && !book[wid[0]][wid[1]][wid[2]]) {
                queue[rear++] = { wid[0],wid[1],wid[2], cur.t + 1 };
                book[wid[0]][wid[1]][wid[2]] = true;
                std::cout << cur.t + 1 << " : " << wid[0] << " " << wid[1] << " " << wid[2] << std::endl;
            }
        }
    }
    return -1;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void qsort(int a[], int begin, int end) {
    if (begin >= end) return;
    int l = begin, r = end, val = a[l];
    while (l < r) {
        while (l < r && a[r] >= val) --r;
        a[l] = a[r];
        while (l < r && a[l] <= val) ++l;
        a[r] = a[l];
    }
    a[l] = val;
    qsort(a, begin, l - 1);
    qsort(a, l + 1, end);
}
void ssort(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        int min = a[i], index = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < min) {
                min = a[j];
                index = j;
            }
        }
        swap(a[i], a[index]);
    }
}
void print(int a[], int n) {
    for (int i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << std::endl;
}
int main() {
    //freopen("input.txt", "r", stdin);
    int a[15] = { 12,1,54,5,2,1,5,4,5,45,4,2,1,5,4 };
    //qsort(a, 0, 14);
    //ssort(a, 14);
    //print(a, 14);
    /*int m, n; std::cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> arr[i][j];
        }
    }
    int ans = bfs(arr, m, n);
    if (ans == -1) std::cout << "no way!!";
    else std::cout << ans;*/

    int ans = bfs_water(8, 0, 0, 4);
    if (ans == -1) std::cout << "no way!!";
    else std::cout << ans;
    return 0;
}