#include "Employee.h"
using namespace std;

// ─────────────────────────────────────────
// CONSTRUCTOR
// ─────────────────────────────────────────

Employee::Employee(string empId, string nm, string cn, string addr,
    string em, string ph, int ag, Gender gn, string pw,
    string desig, double sal, string hire)
    : Person(move(nm), move(cn), move(addr),
        move(em), move(ph), ag, gn, move(pw)),
    employeeID(move(empId)), designation(move(desig)),
    hireDate(move(hire)), salary(sal) {
}

// ─────────────────────────────────────────
// GETTERS
// ─────────────────────────────────────────

string Employee::getEmployeeID()  const { return employeeID; }
string Employee::getDesignation() const { return designation; }
double Employee::getSalary()      const { return salary; }
string Employee::getHireDate()    const { return hireDate; }
string Employee::getSystemId()    const { return employeeID; }

// ─────────────────────────────────────────
// SETTERS
// ─────────────────────────────────────────

void Employee::setDesignation(string d) { designation = move(d); }
void Employee::setSalary(double s) { salary = s; }
void Employee::setHireDate(string h) { hireDate = move(h); }