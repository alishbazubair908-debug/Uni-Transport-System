#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <utility>
#include "Structs.h"

// Simple data-only struct placed inside the header

class Route {
private:
    std::string routeId;
    std::string routeName;
    std::vector<Stop> stops;
    double approxKilometer;

public:
    // Constructor
    Route(std::string rId, std::string name, std::vector<Stop> stps, double km);

    // Getters (Kept inline inside header for maximum execution speed)
    std::string getRouteId() const { return routeId; }
    std::string getRouteName() const { return routeName; }
    const std::vector<Stop>& getStops() const { return stops; }
    double getApproxKilometer() const { return approxKilometer; }

    // Setters & Mutators (Heavy logic moved to .cpp)
    void addStop(const Stop& s);
    void setApproxKilometer(double k) { approxKilometer = k; }
    void setStops(std::vector<Stop> s);
    void setRouteName(std::string n);
};

#endif // ROUTE_H