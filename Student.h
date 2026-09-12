#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "IdCounters.h"

// Student inherits directly from Person — not Employee.
// Students are not paid staff, they are system users with passes.
class Student : public Person
{
private:
    string registrationNumber;
    string rollNumber;
    string department;
    string semester;
    bool   activePass;

public:
    Student() = default;

    Student(string regNum, string nm, string cn, string addr,
        string em, string ph, int ag, Gender gn, string pw,
        string roll, string dept, string sem);

    // Getters
    string getRole()               const override;
    string getSystemId()           const override;
    string getRegistrationNumber() const;
    string getRollNumber()         const;
    string getDepartment()         const;
    string getSemester()           const;
    bool   hasActivePass()         const;

    // Setters
    void setRollNumber(string r);
    void setDepartment(string d);
    void setSemester(string s);
    void setPassStatus(bool b);
    void setPhone(string p);
    void setAddress(string a);

    // Auto ID generator
    static string generateRegistrationNumber();
};

#endif