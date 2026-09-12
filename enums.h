#ifndef ENUMS_H
#define ENUMS_H
#include<string>
using namespace std;

// All system-wide enums defined here.
// Include this wherever an enum is needed.
enum class Gender { MALE, FEMALE, OTHER };

enum class AdminRole {
    SUPER_ADMIN,
    TRANSPORT_MANAGER,
    FINANCE_MANAGER
};


inline string genderToString(Gender g)
{
    switch (g)
    {
    case Gender::MALE:   return "MALE";
    case Gender::FEMALE: return "FEMALE";
    default:             return "OTHER";
    }
}
inline Gender genderFromString(const string& s)
{
    if (s == "FEMALE") return Gender::FEMALE;
    if (s == "OTHER")  return Gender::OTHER;
    return Gender::MALE;
}
// Utility functions for AdminRole
inline string adminRoleToString(AdminRole r) 
{
    switch (r) {
    case AdminRole::SUPER_ADMIN:        return "SUPER_ADMIN";
    case AdminRole::TRANSPORT_MANAGER:  return "TRANSPORT_MANAGER";
    case AdminRole::FINANCE_MANAGER:    return "FINANCE_MANAGER";
    default:                            return "UNKNOWN";
    }
}

inline AdminRole adminRoleFromString(const string& s)
{
    if (s == "TRANSPORT_MANAGER") return AdminRole::TRANSPORT_MANAGER;
    if (s == "FINANCE_MANAGER")   return AdminRole::FINANCE_MANAGER;
    return AdminRole::SUPER_ADMIN;
}
enum class DriverStatus { FREE, ON_ROUTE };
inline string driverStatusToString(DriverStatus s) {
    return (s == DriverStatus::ON_ROUTE) ? "ON_ROUTE" : "FREE";
}

enum class VehicleType { BUS, VAN };
inline string vehicleTypeToString(VehicleType t) {
    return (t == VehicleType::VAN) ? "VAN" : "BUS";
}
inline VehicleType vehicleTypeFromString(const string& s) {
    return (s == "VAN") ? VehicleType::VAN : VehicleType::BUS;
}

enum class PassStatus { PENDING_PAYMENT, ACTIVE, WAITLISTED, EXPIRED };
inline string passStatusToString(PassStatus s) {
    switch (s) {
    case PassStatus::PENDING_PAYMENT: return "PENDING_PAYMENT";
    case PassStatus::ACTIVE:          return "ACTIVE";
    case PassStatus::WAITLISTED:      return "WAITLISTED";
    case PassStatus::EXPIRED:         return "EXPIRED";
    default:                          return "EXPIRED";
    }
}
inline PassStatus passStatusFromString(const string& s) {
    if (s == "PENDING_PAYMENT") return PassStatus::PENDING_PAYMENT;
    if (s == "ACTIVE")          return PassStatus::ACTIVE;
    if (s == "WAITLISTED")      return PassStatus::WAITLISTED;
    return PassStatus::EXPIRED;
}

enum class TripDirection { ARRIVAL, DEPARTURE };
inline string tripDirectionToString(TripDirection d) {
    return (d == TripDirection::DEPARTURE) ? "DEPARTURE" : "ARRIVAL";
}
inline TripDirection tripDirectionFromString(const string& s) {
    return (s == "DEPARTURE") ? TripDirection::DEPARTURE : TripDirection::ARRIVAL;
}


#endif