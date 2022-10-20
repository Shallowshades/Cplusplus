#include <iostream>
#include <string>
#include <limits>
using namespace std;

class worker {
private:
    std::string fullname;
    long id;
public:
    worker() : fullname("no one"), id(0L) {};
    worker(const std::string& s, long n) : fullname(s), id(n) {};
    virtual ~worker() = 0; //pure virtual destructor
    virtual void set();
    virtual void show() const;
};

class waiter : public worker {
private:
    int panache;
public:
    waiter() : worker(), panache(0) {};
    waiter(const std::string& s, long n, int p = 0) : worker(s, n), panache(p) {};
    waiter(const worker& wk, int p = 0) :worker(wk), panache(p) {};
    void set();
    void show() const;
};

class singer : public worker {
protected:
    enum { other, alto, contralto, soprano, bass, baritone, tenor };
    enum { vtypes = 7 };
private:
	static const char* pv[vtypes]; //string equivs of voice types
    int voice;
public:
    singer() : worker(), voice(other) { };
    singer(const std::string& s, long n, int v = other) : worker(s, n), voice(v) {};
    singer(const worker& wk, int v = other) : worker(wk), voice(v) {};
    void set();
    void show() const;
};

//worker methods
//must omplement virtual destructor, even if pure
worker::~worker() {};

void worker::set() {
    cout << "Enter worker's name: ";
    getline(cin, fullname);
    cout << "Enter worker's ID: ";
    cin >> id;
    while (cin.get() != '\n') continue;
}

void worker::show() const {
    cout << "Name: " << fullname << "\n";
    cout << "Employee ID: " << id << "\n";
}

//waiter methoeds
void waiter::set() {
    worker::set();
    cout << "Enter waiter's panache rating: ";
    cin >> panache;
    while (cin.get() != '\n') continue;
}

void waiter::show() const {
    cout << "Category: waiter\n";
    worker::show();
    cout << "Panache rating: " << panache << "\n";
}

//singer methods
const char* singer::pv[] = { "other", "alto", "contralto", "soprano", "bass", "baritone", "tenor" };
void singer::set() {
    worker::set();
    cout << "Enter number for singer's vocal range:\n";
    int i;
    for (i = 0; i < vtypes; ++i) {
        cout << i << ": " << pv[i] << " ";
        if (i % 4 == 3) cout << "\n";
    }
    if (i % 4 != 0) cout << "\n";
    while (cin >> voice && (voice < 0 || voice >= vtypes))
        cout << "Please enter a value >= 0 and < " << vtypes << "\n";
    while (cin.get() != '\n') continue;
}

void singer::show() const {
    cout << "Category: singer\n";
    worker::show();
    cout << "Voice range: " << pv[voice] << "\n";
}

const int LIM = 4;

int main() {

    waiter bob("Bob Apple", 314L, 5);
    singer bev("Beverly Hills", 522L, 3);
    waiter w;
    singer s;

    worker* pw[LIM] = { &bob,&bev,&w,&s }; 
    //构造异质链表 用抽象类指针构造派生类对象链表
    for (int i = 2; i < LIM; ++i) pw[i]->set();

    for (int i = 0; i < LIM; ++i) {
        pw[i]->show();
        std::cout << "\n";
    }

    return 0;
}