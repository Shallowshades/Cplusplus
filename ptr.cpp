#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

class person;
class weapon;

class weapon {
public:
    weapon(int cap = 6, int rest = 6) : m_iCapicity(cap), m_iRestCount(rest) {}
    ~weapon() = default;

    void shoot() {
        if (m_iRestCount > 0) m_iRestCount--, std::cout << "Shoot once..." << std::endl;
        else std::cout << "Error, No Fire!!!" << std::endl;
    }

    void reloading() { m_iRestCount = m_iCapicity; }
private:
    int m_iCapicity;
    int m_iRestCount;
};

class person {
public:
    person(const shared_ptr<weapon>& gun) : m_weapon(gun) {}
    ~person() = default;

    void shoot() {
        if (!m_weapon.expired()) m_weapon.lock()->shoot();
        else std::cout << "Error, Weapon not Exist!!!" << std::endl;
    }
private:
    weak_ptr<weapon> m_weapon;
};

int main() {

    shared_ptr<weapon> refile = make_shared<weapon>();
    weak_ptr<weapon> dummy = refile;
    std::cout << refile.use_count() << std::endl;
    person gazi(refile);
    std::cout << refile.use_count() << std::endl;

    //weak_ptr<weapon> dummy(refile);
    for (int i = 0; i < 7; ++i) {
        gazi.shoot();
        std::cout << refile.use_count() << std::endl;
    }

    refile.reset();
    std::cout << refile.use_count() << std::endl;

    try{
        dummy.lock()->shoot();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}