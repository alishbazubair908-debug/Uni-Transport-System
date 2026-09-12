#include "Vehicle.h"

using namespace std;

// General Constructor Implementation
Vehicle::Vehicle(string vId, string plate, VehicleType t, int cap, double eff, string fType)
    : vehicleId(move(vId)), licensePlate(move(plate)), type(t),
    capacity(cap), occupiedSeats(0), fuelEfficiency(eff), fuelType(move(fType)),
    vanDailyMileage(0.0) {
}

// Specialized VAN Constructor Implementation
Vehicle::Vehicle(string vId, string plate, int cap, double eff, string fType, string purpose, double dMileage)
    : vehicleId(move(vId)), licensePlate(move(plate)), type(VehicleType::VAN),
    capacity(cap), occupiedSeats(0), fuelEfficiency(eff), fuelType(move(fType)),
    vanPurpose(move(purpose)), vanDailyMileage(dMileage) {
}

void Vehicle::incrementOccupiedSeats() {
    if (occupiedSeats < capacity) {
        occupiedSeats++;
    }
}

void Vehicle::decrementOccupiedSeats() {
    if (occupiedSeats > 0) {
        occupiedSeats--;
    }
}

double Vehicle::getVanEstimatedDailyFuelCost(double petrolPrice) const {
    if (!isVAN() || fuelEfficiency <= 0.0) {
        return 0.0;
    }
    return (vanDailyMileage / fuelEfficiency) * petrolPrice;
}

void Vehicle::printVanDetails(double petrolPrice) const 
{
    if (!isVAN()) return;

    cout << "  [VAN Details]\n"
        << "    Purpose           : " << (vanPurpose.empty() ? "N/A" : vanPurpose) << "\n"
        << "    Daily Mileage     : " << vanDailyMileage << " km\n";

    if (petrolPrice > 0.0) {
        double fuelCost = getVanEstimatedDailyFuelCost(petrolPrice);
        cout << "    Est. Daily Fuel   : Rs " << fixed << setprecision(2) << fuelCost
            << " (" << fuelEfficiency << " km/L x " << petrolPrice << " Rs/L)\n";
    }
}