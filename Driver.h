#ifndef DRIVER_H
#define DRIVER_H

#include "Employee.h"
#include "enums.h"
#include "IdCounters.h"

class Driver : public Employee
{
private:
    string       licenseNumber;
    DriverStatus status;
    string       assignedVehicleId;

public:
    Driver() = default;

    Driver(string empId, string nm, string cn, string addr,
        string em, string ph, int ag, Gender gn, string pw,
        string desig, double sal, string hire, string lic);

    // Getters
    string       getRole()            const override;
    string       getLicenseNumber()   const;
    DriverStatus getStatus()          const;
    string       getAssignedVehicle() const;

    // Setters
    void setLicenseNumber(string l);
    void setStatus(DriverStatus s);
    void setAssignedVehicle(string v);

    // Auto ID generator
    static string generateEmployeeId();
};

#endif