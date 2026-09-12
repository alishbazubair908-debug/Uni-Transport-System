#include "Admin.h"
using namespace std;

// ─────────────────────────────────────────
// CONSTRUCTOR
// ─────────────────────────────────────────

Admin::Admin(string empId, string nm, string cn, string addr,
    string em, string ph, int ag, Gender gn, string pw,
    string desig, double sal, string hire, AdminRole role)
    : Employee(move(empId), move(nm), move(cn), move(addr),
        move(em), move(ph), ag, gn, move(pw),
        move(desig), sal, move(hire)),
    adminRole(role) {
}

// ─────────────────────────────────────────
// GETTERS
// ─────────────────────────────────────────

string    Admin::getRole()      const { return "Admin"; }
AdminRole Admin::getAdminRole() const { return adminRole; }

// ─────────────────────────────────────────
// SETTER
// ─────────────────────────────────────────

void Admin::setAdminRole(AdminRole r) { adminRole = r; }

// ─────────────────────────────────────────
// PERMISSION CHECKS
// Each role has specific domain access.
// ─────────────────────────────────────────

bool Admin::canManageVehicles() const {
    return adminRole == AdminRole::SUPER_ADMIN ||
        adminRole == AdminRole::TRANSPORT_MANAGER;
}

bool Admin::canManageFinance() const {
    return adminRole == AdminRole::SUPER_ADMIN ||
        adminRole == AdminRole::FINANCE_MANAGER;
}

bool Admin::canManageUsers() const {
    return adminRole == AdminRole::SUPER_ADMIN;
}

bool Admin::isSuperAdmin() const {
    return adminRole == AdminRole::SUPER_ADMIN;
}

// ─────────────────────────────────────────
// STATIC ID GENERATOR
// Uses global gCounters — increments and saves to file
// so IDs never duplicate across sessions.
// ─────────────────────────────────────────

string Admin::generateEmployeeId() 
{
    string id = "EMP-" + to_string(gCounters.adminNext++);
    gCounters.saveToFile();
    return id;
}