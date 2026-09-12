#include "Driver.h"
using namespace std;

// ─────────────────────────────────────────
// CONSTRUCTOR
// ─────────────────────────────────────────

Driver::Driver(string empId, string nm, string cn, string addr,
    string em, string ph, int ag, Gender gn, string pw,
    string desig, double sal, string hire, string lic)
    : Employee(move(empId), move(nm), move(cn), move(addr),
        move(em), move(ph), ag, gn, move(pw),
        move(desig), sal, move(hire)),
    licenseNumber(move(lic)),
    status(DriverStatus::FREE),
    assignedVehicleId("") {
}

// ─────────────────────────────────────────
// GETTERS
// ─────────────────────────────────────────

string       Driver::getRole()            const { return "Driver"; }
string       Driver::getLicenseNumber()   const { return licenseNumber; }
DriverStatus Driver::getStatus()          const { return status; }
string       Driver::getAssignedVehicle() const { return assignedVehicleId; }

// ─────────────────────────────────────────
// SETTERS
// ─────────────────────────────────────────

void Driver::setLicenseNumber(string l) { licenseNumber = move(l); }
void Driver::setStatus(DriverStatus s) { status = s; }
void Driver::setAssignedVehicle(string v) { assignedVehicleId = move(v); }

// ─────────────────────────────────────────
// STATIC ID GENERATOR
// ─────────────────────────────────────────

string Driver::generateEmployeeId()
{
    string id = "DRV-" + to_string(gCounters.driverNext++);
    gCounters.saveToFile();
    return id;
}