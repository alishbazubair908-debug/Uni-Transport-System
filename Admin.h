#ifndef ADMIN_H
#define ADMIN_H

#include "Employee.h"
#include "enums.h"
#include "IdCounters.h"

class Admin : public Employee 
{
private:
    AdminRole adminRole;

public:
    Admin() = default;

    Admin(string empId, string nm, string cn, string addr,
        string em, string ph, int ag, Gender gn, string pw,
        string desig, double sal, string hire, AdminRole role);

    // Getters
    string    getRole()      const override;
    AdminRole getAdminRole() const;

    // Setter
    void setAdminRole(AdminRole r);

    // Permission checks
    bool canManageVehicles() const;
    bool canManageFinance()  const;
    bool canManageUsers()    const;
    bool isSuperAdmin()      const;

    // Auto ID generator
    static string generateEmployeeId();
};

#endif