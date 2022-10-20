#pragma once

#include <iostream>

using namespace std;

template<typename T> class node;
template<typename T> class linklist;

template<typename T> ostream& operator << (ostream& os, const node<T>& x);
template<typename T> ostream& operator << (ostream& os, const linklist<T>& x);

template <typename T>
class node {
public:
	node(const T& d, const node* const n)
		:_data(d), _next(n) { };
	node(const node& x){
		_data = x._data;
		_next = x._next;
		return *this;
	}

	~node() { _next = nullptr; }

	void get_data(const node& x) const { return x._data; }
	void get_next(const node& x) const { return x._next; }

	void set_data(const T& data) { _data = data; }
	void set_next(const node* const next) { _next = next; }

	bool find(const string& name) { return _data.name(name); }


private:
	T _data;
	node* _next;

	friend class linklist;
	friend ostream& operator << (ostream& os, const node<T>& x);

};

template<typename T> 
inline ostream& operator << (ostream& os, const node<T>& x) { return os << x._data; }

template<typename T>
class linklist {
public:
	linklist() :_length(0), _head(nullptr){}

	~linklist() { _head = nullptr; }

	node<T>* find_last_second(const linklist& x) {
		if (x._length < 2) return nullptr;
		node<T>* p = x;
		while (p->_next->_next != nullptr) p = p->_next;
		return p;
	}

	bool find_exist(const string& name) {
		node<T>* p = _head;
		while (_head != nullptr) {
			if (p.find(name)) return true;
		}
		return false;
	}
	
	void find(const string& name) {
		node<T>* p = _head;
		while (_head != nullptr) {
			if (node<T>.find(name)) cout << *p << "\n";
		}
	}

	void insert(const node<T>* x) {
		x._next = _head;
		_head->_next = x;
	}

	void display(){
		node<T>* p = _head;
		while(p!=nullptr){
			cout << *p << "\n";
			p = p->next;
		}
	}

private:
	int _length;
	node<T>* _head;
};