#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include"enums.h"


class Vehicle 
{
private:
    std::string vehicleId;
    std::string licensePlate;
    VehicleType type;
    int capacity;
    int occupiedSeats;
    std::string currentDriverId;
    std::string assignedRouteId;
    double fuelEfficiency;
    std::string fuelType;
    std::string vanPurpose;
    double vanDailyMileage;

public:
    // General Constructor
    Vehicle(std::string vId, std::string plate, VehicleType t, int cap, double eff, std::string fType);

    // Specialized VAN Constructor
    Vehicle(std::string vId, std::string plate, int cap, double eff, std::string fType,
        std::string purpose, double dMileage);

    // Getters
    std::string getVehicleId() const { return vehicleId; }
    std::string getLicensePlate() const { return licensePlate; }
    VehicleType getType() const { return type; }
    int getCapacity() const { return capacity; }
    int getOccupiedSeats() const { return occupiedSeats; }
    int getRemainingSeats() const { return std::max(0, capacity - occupiedSeats); }
    std::string getCurrentDriverId() const { return currentDriverId; }
    std::string getAssignedRouteId() const { return assignedRouteId; }
    double getFuelEfficiency() const { return fuelEfficiency; }
    std::string getFuelType() const { return fuelType; }
    std::string getVanPurpose() const { return vanPurpose; }
    double getVanDailyMileage() const { return vanDailyMileage; }
    bool isVAN() const { return type == VehicleType::VAN; }

    // Setters & Mutators
    void incrementOccupiedSeats();
    void decrementOccupiedSeats();
    void setOccupiedSeats(int s) { occupiedSeats = s; }
    void setDriver(std::string d) { currentDriverId = std::move(d); }
    void setAssignedRouteId(std::string r) { assignedRouteId = std::move(r); }
    void setLicensePlate(std::string p) { licensePlate = std::move(p); }
    void setType(VehicleType t_) { type = t_; }
    void setCapacity(int c) { capacity = c; }
    void setFuelEfficiency(double e) { fuelEfficiency = e; }
    void setFuelType(std::string f) { fuelType = std::move(f); }
    void setVanPurpose(std::string p) { vanPurpose = std::move(p); }
    void setVanDailyMileage(double m) { vanDailyMileage = m; }

    // Specialized Calculation & Print Routines
    double getVanEstimatedDailyFuelCost(double petrolPrice) const;
    void printVanDetails(double petrolPrice = 0.0) const;
};

#endif // VEHICLE_H