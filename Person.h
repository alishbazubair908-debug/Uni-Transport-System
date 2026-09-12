#ifndef PERSON_H
#define PERSON_H
#include"enums.h"
#include <string>
using namespace std;


class Person {
protected:
    string name;
    string cnic;
    string address;
    string email;
    string phone;
    int    age;
    Gender gender;
    string password;

public:
    Person() = default;

    Person(string nm, string cn, string addr,
        string em, string ph, int ag,
        Gender gn, string pw);

    virtual ~Person() = default;

    // Pure virtual — subclass must implement
    virtual string getRole()     const = 0;
    virtual string getSystemId() const = 0;

    // Getters
    string getName()     const;
    string getCNIC()     const;
    string getAddress()  const;
    string getEmail()    const;
    string getPhone()    const;
    string getPassword() const;
    int    getAge()      const;
    Gender getGender()   const;

    // Setters
    void setName(string n);
    void setCNIC(string c);
    void setAddress(string a);
    void setEmail(string e);
    void setPhone(string p);
    void setAge(int a);
    void setGender(Gender g);

    // Password check
    bool checkPassword(const string& pw) const;

};


#endif