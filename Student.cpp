#include "Student.h"
using namespace std;

// ─────────────────────────────────────────
// CONSTRUCTOR
// ─────────────────────────────────────────

Student::Student(string regNum, string nm, string cn, string addr,
    string em, string ph, int ag, Gender gn, string pw,
    string roll, string dept, string sem)
    : Person(move(nm), move(cn), move(addr),
        move(em), move(ph), ag, gn, move(pw)),
    registrationNumber(move(regNum)),
    rollNumber(move(roll)),
    department(move(dept)),
    semester(move(sem)),
    activePass(false) {
}

// ─────────────────────────────────────────
// GETTERS
// ─────────────────────────────────────────

string Student::getRole()               const { return "Student"; }
string Student::getSystemId()           const { return registrationNumber; }
string Student::getRegistrationNumber() const { return registrationNumber; }
string Student::getRollNumber()         const { return rollNumber; }
string Student::getDepartment()         const { return department; }
string Student::getSemester()           const { return semester; }
bool   Student::hasActivePass()         const { return activePass; }

// ─────────────────────────────────────────
// SETTERS
// ─────────────────────────────────────────

void Student::setRollNumber(string r) { rollNumber = move(r); }
void Student::setDepartment(string d) { department = move(d); }
void Student::setSemester(string s) { semester = move(s); }
void Student::setPassStatus(bool b) { activePass = b; }
void Student::setPhone(string p) { phone = move(p); }
void Student::setAddress(string a) { address = move(a); }

// ─────────────────────────────────────────
// STATIC ID GENERATOR
// ─────────────────────────────────────────

string Student::generateRegistrationNumber() {
    string id = "STU-" + to_string(gCounters.studentNext++);
    gCounters.saveToFile();
    return id;
}
