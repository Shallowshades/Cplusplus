#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <initializer_list>

template <typename T>
class vector {
    friend std::ostream& operator<<(std::ostream& os, const vector<T>& v);
public:
    vector(int length = 0) : _array(nullptr), _length(length),_tail(0) {}
    vector(const vector& v) : _length(v._length),_tail(v._tail) {
        if(_array != nullptr) { free(_array); }
        alloc(v._length);
        v.move(_array);
    }
    vector(vector&& v):_length(v.length),_array(v._array),_tail(v._tail){
        v._length = 0;
        v._array = nullptr;
    }
    vector(std::initializer_list<T> list):_length(v.length),_tail(v._tail){
        alloc(list.size());
        for(std::initializer_list<T>::iterator it = list.begin();it != list.end(); list++){
            _array[_tail++] = *it;
        }
    }
    ~vector() {
        if(_array != nullptr) { free(_array); }
    }
    vector& operator=(const vector& v){
        if(_array != nullptr) { free(_array); }
        alloc(v._length);
        v.move(_array);
        _tail = v._tail;
    }

    int size()const {return _length;}
    bool empty()const {return _length == 0;}

    T& operator[] (int index){return _array[index];}
    T& operator[] (int index)const{return _array[index];}

    void push_back(const T& val){
        if(_capacity == _length){
            _capacity <<= 1;
            alloc(_capacity);
            move(_array);
        }
        _array[_tail++] = val;
    }

private:
    static void alloc(int length){ _array = (T*)calloc(length, sizeof(T));}
    static void move(int* dst){  memcpy(dst, _array, _length * sizeof(T)); }

    int* _array;
    int  _length;
    int  _capacity;
    int  _tail;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v){
    os << "[";
    for(int i =0;i<v._length - 1;i++) {os << v[i] << ", ";}
    os << _array[_length - 1];
    os <<"]";
    return os;
}

int main() {
    vector<int> v1;
    std::cout << v1.size() <<std::endl;

    return 0;
}