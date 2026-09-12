#include "Person.h"
using namespace std;

// ─────────────────────────────────────────
// CONSTRUCTOR
// ─────────────────────────────────────────

Person::Person(string nm, string cn, string addr,
    string em, string ph, int ag,
    Gender gn, string pw)
    : name(move(nm)), cnic(move(cn)), address(move(addr)),
    email(move(em)), phone(move(ph)), age(ag),
    gender(gn), password(move(pw)) {
}

// ─────────────────────────────────────────
// GETTERS
// ─────────────────────────────────────────

string Person::getName()     const { return name; }
string Person::getCNIC()     const { return cnic; }
string Person::getAddress()  const { return address; }
string Person::getEmail()    const { return email; }
string Person::getPhone()    const { return phone; }
string Person::getPassword() const { return password; }
int    Person::getAge()      const { return age; }
Gender Person::getGender()   const { return gender; }

// ─────────────────────────────────────────
// SETTERS
// ─────────────────────────────────────────

void Person::setName(string n) { name = move(n); }
void Person::setCNIC(string c) { cnic = move(c); }
void Person::setAddress(string a) { address = move(a); }
void Person::setEmail(string e) { email = move(e); }
void Person::setPhone(string p) { phone = move(p); }
void Person::setAge(int a) { age = a; }
void Person::setGender(Gender g) { gender = g; }

// ─────────────────────────────────────────
// PASSWORD CHECK
// ─────────────────────────────────────────

bool Person::checkPassword(const string& pw) const 
{
    return password == pw;
}

