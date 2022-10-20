#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class node {
public:
  int _x;
  node *_next;
  node(int x, node *next = nullptr) : _x(x), _next(nullptr) {}
};

int main() {
  srand((unsigned int)time(0));
  vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand() % 10);
  }
  node *head = new node(0);
  node *p = head;
  for (auto x : v) {
    ++head->_x;
    p->_next = new node(x);
    p = p->_next;
  }
  p->_next = head;

  //用map存储地址，每个节点的地址都是唯一的
  unordered_map<node *, bool> m;
  p = head->_next;
  while (p != nullptr) {
    if (m[p] == true) {
      cout << "Circle!!!\n";
      break;
    } else {
      cout << p->_x << endl;
      m[p] = true;
      p = p->_next;
    }
  }
  return 0;
}