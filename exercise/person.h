#pragma once

#include <iostream>
#include <string>

using namespace std;

class person;

ostream& operator << (ostream& os, const person& x);

class person {
    
public:
    person(const string& n = "", const int& a = 0, const string& p = "", const string& addr = "")
        :_name(n), _age(a), _phonenum(p), _address(addr) {}

    person(const person& x) {
        _name = x._name;
        _age = x._age;
        _phonenum = x._phonenum;
        _address = x._address;
    }

    void set_name(person& x, const string& s) { x._name = s; }
    void set_age(person& x, const int& y) { x._age = y; }
    void set_phonenum(person& x, const string& s) { x._phonenum = s; }
    void set_address(person& x, const string& s) { x._address = s; }

    string get_name(const person& x) const { return x._name; }
    string get_phonenum(const person& x) const { return x._phonenum; }
    string get_address(const person& x) const { return x._address; }
    int get_age(const person& x) const { return  x._age; }

    bool name       (const string& name)       const { return name == _name; }
    bool age        (const int& age)           const { return age == _age; }
    bool phonenum   (const string& phonenum)   const { return phonenum == _phonenum; }
    bool address    (const string& address)    const { return address == _address; }

private:
    string _name;
    string _phonenum;
    string _address;
    int _age;

    friend ostream& operator << (ostream& os, const person& x);
};

inline ostream& operator << (ostream& os, const person& x)
{
    return os << x._name << " " << x._age << "\n" << x._phonenum << "\n" << x._address << "\n";
}
