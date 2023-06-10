#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <set>
#include <queue>
#include <thread>
#include <boost/optional.hpp>

using namespace std;

const int dir[8] = { 1,0,0,1,-1,0,0,-1 };
const int mov[4][2] = { -1,0,0,1,1,0,0,-1 };

class matrix;
ostream& operator<< (ostream& os, const matrix& m);
istream& operator>> (istream& is, matrix& m);

class matrix {
    friend ostream& operator<< (ostream& os, const matrix& m);
    friend istream& operator>> (istream& is, matrix& m);
public:
    explicit matrix() = default;
    matrix(const matrix& m);
    matrix(initializer_list<initializer_list<int>> list);
    const bool operator ==(const matrix& m) const;
    bool operator < (const matrix& m) const;
    const int evaluate() const;
    int a[3][3];
    static const matrix m_matGoal;
};

const matrix matrix::m_matGoal = {
    {1, 2, 3},
    {4, 0, 5},
    {6, 7, 8}
};

matrix::matrix(const matrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            a[i][j] = m.a[i][j];
        }
    }
}

matrix::matrix(initializer_list<initializer_list<int>> list) {
    int i = 0, j = 0;
    for (auto&& sublist : list) {
        for (auto&& item : sublist) {
            a[i][j] = item;
            if (++j / 3 > 0) {
                j %= 3;
                ++i;
            }
        }
    }
}

const bool matrix::operator==(const matrix& m) const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (a[i][j] != m.a[i][j])
                return false;
        }
    }
    return true;
}

bool matrix::operator<(const matrix& m) const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (a[i][j] != m.a[i][j])
                return a[i][j] < m.a[i][j];
        }
    }
    return false;
}

ostream& operator<< (ostream& os, const matrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            os << m.a[i][j];
        }
        os << endl;
    }
    return os;
}
istream& operator>> (istream& is, matrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            is >> m.a[i][j];
        }
    }
    return is;
}

const int matrix::evaluate() const {
    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (a[i][j] != matrix::m_matGoal.a[i][j])
                ++ret;
        }
    }
    return ret;
}

class status {
public:
    const bool operator < (const status& s) const { return t + m.evaluate() > s.t + s.m.evaluate(); }

    matrix m;   //当前状态
    int t;      //bushu
    vector<matrix> path;
};

void print(const status& s) {
    std::cout << "t = " << s.t << "\n\n";
    for (auto&& item : s.path) {
        std::cout << item << "\n\n";
    }
}

boost::optional<int> star(const status& start) {
    boost::optional<int> result;
    set<matrix> s;
    priority_queue<status> q;
    q.push(start);
    while (!q.empty()) {
        auto x = q.top(); q.pop();
        if (!x.m.evaluate()) {
            print(x);
            result = x.t;
            break;
        }

        int fx = 0, fy = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!x.m.a[i][j])
                    fx = i, fy = j;
            }
        }
        ++x.t;
        for (int i = 0; i < 4; ++i) {
            int xx = fx + mov[i][0];
            int yy = fy + mov[i][1];

            if (xx >= 0 && xx < 3 && yy >= 0 && yy < 3) {
                matrix nex(x.m);
                swap(x.m, nex);
                swap(x.m.a[fx][fy], x.m.a[xx][yy]);
                if (!s.count(x.m)) {
                    x.path.push_back(x.m);
                    s.insert(x.m);
                    q.push(x);
                    x.path.pop_back();
                }
                swap(x.m.a[fx][fy], x.m.a[xx][yy]);
                swap(x.m, nex);
            }
        }
    }
    return result;
}

int inversion(const matrix& m) {
    int cnt = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = i + 1; j < 9; ++j) {
            if (m.a[i / 3][i % 3] && m.a[j / 3][j % 3] && m.a[i / 3][i % 3] > m.a[j / 3][j % 3])
                ++cnt;
        }
    }
    return cnt;
}

int main() {

    status start;
    std::cin >> start.m;
    if ((inversion(start.m) & 1) != (inversion(matrix::m_matGoal) & 1))
        cout << "Don't have ansner!!\n";
    start.t = 0;
    if (star(start).value_or(-1) == -1) {
        std::cout << "Don't have ansner!!\n";
    }
}