#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/random.hpp>

using namespace std;
using namespace boost;
using namespace boost::gregorian;

class credit_card;
bool operator < (const credit_card& cc1, const credit_card&& cc2);

class credit_card {

    friend bool operator < (const credit_card& cc1, const credit_card&& cc2);

public:
    credit_card(const char* name, int no);
    const string& bank_name() const;
    const int& bill_day_no() const;
    int calc_free_days(date consume_day = day_clock::local_day()) const;
private:
    string m_str_bank_name;
    int m_n_bill_day_no;
};

credit_card::credit_card(const char* name, int no)
    : m_str_bank_name(name),
    m_n_bill_day_no(no) {

}

inline const string& credit_card::bank_name() const {
    return m_str_bank_name;
}
inline const int& credit_card::bill_day_no() const {
    return m_n_bill_day_no;
}

int credit_card::calc_free_days(date consume_day) const {
    date bill_day(consume_day.year(), consume_day.month(), m_n_bill_day_no);

    if (consume_day > bill_day) {
        bill_day += months(1);
    }

    return (bill_day - consume_day).days() + 20;
}

bool operator < (const credit_card& cc1, const credit_card& cc2) {
    return cc1.calc_free_days() < cc2.calc_free_days();
}

auto credit_card_less = [](const credit_card& cc1, const credit_card& cc2) {
    return cc1.calc_free_days() < cc2.calc_free_days();
};

int main() {

    vector<credit_card> v;
    string str("A bank");
    date d = day_clock::local_day();
    mt19937 rn(time(0));
    for (int i = 0;i < 10;++i) {
        str[0] += 1;
        d += days(rn() % 365);
        credit_card a(str.c_str(), d.day().as_number());

    }

    credit_card tmp = max(v.front(), v.back());

    cout << "You should use " << tmp.bank_name()
        << ", free days = " << tmp.calc_free_days()
        << endl;

    return 0;
}


