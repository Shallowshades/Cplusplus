//3案例描述
//有5名选手：选手ABCDE，10个评委分别对每一名选手打分，
//去除最高分，去除评委中最低分，取平均分。
//
//实现步骤
//创建五名选手，放到vector中
//遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
//sort算法对deque容器中分数排序，去除最高和最低分
//deque容器遍历一遍，累加总分

#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

class person {
public:
	person() :name("选手x"), score(-1) {}
	person(const string& n, const int& s) :name(n), score(s) {}
	string name;
	int score;
};

void create_person(vector<person>& v) {
	string name_seed = "ABCDE";
	for (int i = 0; i < 5; ++i) {
		v.push_back(person(string("选手") + name_seed[i], 0));
	}
}

void set_score(vector<person>& v) {
	for (vector<person>::iterator it = v.begin(); it != v.end(); ++it) {
		//随机打分
		deque<int> d;
		for (int i = 0; i < 10; ++i) {
			int score = rand() % 41 + 60; //60`100
			d.push_back(score);
		}
		//for (int i = 0; i < d.size(); ++i) cout << d[i] << " "; cout << "\n";
		//排序 去除最高和最低分
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		//获取平均值
		int sum = 0;
		for (int i = 0; i < d.size(); ++i) sum += d[i];
		int avg = sum / d.size();
		it->score = avg;
	}
}

void show_player_score(const vector<person>& v) {
	cout << "\n*****选手成绩总览*****\n";
for (int i = 0;i < v.size(); ++i) {
		cout<< "姓名：" << v[i].name << "\t分数：" << v[i].score << endl;
	} 
}

int main() {
	//随机数种子
	srand((unsigned int)time(0));
	
	vector<person> v;
	create_person(v);
	show_player_score(v);

	set_score(v);
	show_player_score(v);

	return 0;
}