#include <ostream>
using namespace std;

class node;
class List;

ostream& operator << (ostream& os, const node& n);
ostream& operator << (ostream& os, const List& L);

class node {
public:
    friend class List;
    friend ostream& operator << (ostream& os, const node& n);
    node() :_next(nullptr) {};
    node(const int& data, node* next) :_data(data), _next(next) {}
    node(const node& n) {
        _data = n._data;
        _next = n._next;
    }
    node operator = (const node& n) {
        _data = n._data;
        _next = n._next;
        return *this;
    }
    int get_data() const { return _data; }
    node* get_next() const { return _next; }
    void set_data(const int& data) { _data = data; }
    void set_next(node* const next) { _next = next; }
    ~node() {
        _next = nullptr;
    }

private:
    int _data;
    node* _next;
};


ostream& operator << (ostream& os, const node& n) { return os << n._data; }


class List {
public:
    friend ostream& operator << (ostream& os, const List& n);
    List() :_size(0) {
        _header = new node(0, nullptr);
        _tailer = _header;
    }
    List(const List& L) {
        _size = L._size;
        _header = L._header;
        node* p2 = L._header->_next;
        while (p2 != nullptr) {
            node* p = new node(*p2);
            _tailer->_next = p;
            _tailer = p;
            p2 = p2->_next;
        }
    }
    List operator = (const List& L) {
        _size = L._size;
        _header = L._header;
        node* p2 = L._header->_next;
        while (p2 != nullptr) {
            node* p = new node(*p2);
            _tailer->_next = p;
            _tailer = p;
            p2 = p2->_next;
        }
        return *this;
    }
    ~List() {
        node* ptr1 = _header;
        while (ptr1 != nullptr) {
            _header = ptr1->_next;
            delete ptr1;
            ptr1 = _header;
        }
        _tailer = nullptr;
    }
    unsigned int size() const { return _size; }
    node* get_header() const { return _header; }
    node* get_tailer() const { return _tailer; }

    int operator [] (int index) const {
        node* ptr = _header->_next;
        while (ptr != nullptr && index--) {
            ptr = ptr->_next;
        }
        if (ptr == nullptr) return -1;
        return ptr->_data;
    }

    void push_back(const int& data) {
        node* p = new node(data, nullptr);
        _tailer->_next = p;
        _tailer = p;
        ++_size;
    }

    void pop_back(const int& data) {
        node* p = _header;
        while (p->_next != _tailer) {
            p = p->_next;
        }
        --_size;
        delete _tailer;
        _tailer = p;
    }

private:
    node* _header;
    node* _tailer;
    unsigned int _size;
};

ostream& operator << (ostream& os, const List& L) {
    node* ptr = L.get_header()->get_next();
    while (ptr != nullptr) {
        os << *ptr << " ";
        ptr = ptr->get_next();
    }
    return os;
}