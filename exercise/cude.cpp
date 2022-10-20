#include <iostream>
#include <string>

using namespace std;

class cude;

ostream& operator<<(ostream&, const cude&);

class cude {

public:
    cude(const int& length = 0, const int& width = 0, const int& height = 0) : _length(length), _width(width), _height(height) {}

    void length(const int& len) { _length = len; }
    void width(const int& wid) { _width = wid; }
    void height(const int& hei) { _height = hei; }

    int length() const { return _length; }
    int width() const { return _width; }
    int heigth() const { return _height; }

    int area() const { return 2 * (_length * _width + _length * _height + _width * _height); }
    int volume() const { return _length * _width * _height; }

    bool equal(const cude& x) const { return _length == x._length && _width == x._width && _height == x._height; }

private:
    int             _length, _width, _height;
    friend ostream& operator<<(ostream&, const cude&);
};

inline ostream& operator<<(ostream& os, const cude& s) { return os << s._length << " " << s._width << " " << s._height; }

inline bool equal(const cude& a, const cude& b) { return a.length() == b.length() && a.width() == b.width() && a.heigth() == b.heigth(); }

int main() {

    cude c1(10, 10, 10);
    cude c2(20, 5, 10);

    cout << c1.area() << "\n";
    cout << c2.area() << "\n";

    cout << c1.volume() << "\n";
    cout << c2.volume() << "\n";

    cout << boolalpha << equal(c1, c2) << "\n";
    cout << boolalpha << c1.equal(c2) << "\n";

    cout << c1 << "\n";
    cout << c2 << "\n";

    return 0;
}