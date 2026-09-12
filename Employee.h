#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person 
{
protected:
    string employeeID;
    string designation;
    string hireDate;
    double salary;

public:
    Employee() = default;

    Employee(string empId, string nm, string cn, string addr,
        string em, string ph, int ag, Gender gn, string pw,
        string desig, double sal, string hire);

    // Getters
    string getEmployeeID()  const;
    string getDesignation() const;
    double getSalary()      const;
    string getHireDate()    const;

    // Override from Person
    string getSystemId() const override;

    // Setters
    void setDesignation(string d);
    void setSalary(double s);
    void setHireDate(string h);
};

#endif