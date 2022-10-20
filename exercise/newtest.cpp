//案例 - 员工分组
//案例描述
//公司今天招聘了10个员工(ABCDEFGHIJ) ，10名员工进入公司之后，需要指派员工在那个部门工作
//员工信息有 : 姓名工资组成; 部门分为:策划、美术、研发
//随机给10名员工分配部门和工资
//通过multimap进行信 息的插入key(部门编号) value(员工)
//分部门显示员工信息
//实现步骤
//1.创建10名员工，放到vector中
//2.遍历vector容器，取出每个员工，进行随机分组
//3.分组后，将员工部门编号作为key, 具体员工作为value, 放入到multimap容器中
//4.分部门显示员工信息

#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

constexpr auto planer = 1;
constexpr auto artist = 2;
constexpr auto research = 3;

class worker {
public:
	worker(const string& name, const int& salary) :_name(name), _salary(salary) {}
	worker() :_name("worker_x"), _salary(0) {}
	friend ostream& operator << (ostream& os, const worker& w);
private:
	string _name;
	int _salary;
};
ostream& operator << (ostream& os, const worker& w) { return os << w._name << "\t" << w._salary; }

void create_workers(vector<worker>& v) {
	string name_seed = "ABCDEFGHIJ";
	for (int i = 0; i < 10; ++i) v.push_back(worker(string("worker_") + name_seed[i], rand() % 10000 + 5000));
}

void group_workers(const vector<worker>& v, multimap<int, worker>& m) {
	srand((unsigned int)time(0));
	for (int i = 0; i < v.size(); ++i) m.insert(make_pair(rand() % 3 + 1, v[i]));
}

//void show_grouped_workers(const multimap<int, worker>& m) {
//	int count = 0;
//	map<int, worker>::const_iterator pos = m.end();
//	
//	cout << "planer department\n";
//	count = m.count(planer);
//	pos = m.find(planer);
//	for (int i = 0; i < count; ++i, ++pos) cout << pos->first << "\t" << pos->second << endl;
//
//	cout << "artist department\n";
//	count = m.count(artist);
//	pos = m.find(artist);
//	for (int i = 0; i < count; ++i, ++pos) cout << pos->first << "\t" << pos->second << endl;
//
//	cout << "research department\n";
//	count = m.count(research);
//	pos = m.find(research);
//	for (int i = 0; i < count; ++i, ++pos) cout << pos->first << "\t" << pos->second << endl;
//
//}

void show_grouped_workers(const multimap<int, worker>& m) {
	int count = 0;
	map<int, worker>::const_iterator pos = m.end();

	cout << "planer department\n";
	count = m.count(planer);
	pos = m.find(planer);
	for (int i = 0; i < count; ++i) cout << pos->first << "\t" << pos++->second << endl;

	cout << "artist department\n";
	count = m.count(artist);
	pos = m.find(artist);
	for (int i = 0; i < count; ++i) cout << pos->first << "\t" << pos++->second << endl;

	cout << "research department\n";
	count = m.count(research);
	pos = m.find(research);
	for (int i = 0; i < count; ++i) cout << pos->first << "\t" << pos++->second << endl;

}

int main() {

	//create workers
	vector<worker> v;
	create_workers(v);

	//group workers
	multimap<int, worker> m;
	group_workers(v, m);

	cout << "show grouped workers\n";
	for (multimap<int, worker>::iterator it = m.begin(); it != m.end(); ++it) cout << it->first << "\t" << it->second << endl;

	//show grouped workers
	show_grouped_workers(m);

	cout << "show all workers\n";
	for (int i = 0; i < v.size(); ++i) cout << v[i] << endl;

	cout << "show grouped workers\n";
	for (multimap<int, worker>::iterator it = m.begin(); it != m.end(); ++it) cout << it->first << "\t" << it->second << endl;

	return 0;
}