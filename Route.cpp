#include "Route.h"

using namespace std;

// Constructor Implementation using memory-efficient std::move
Route::Route(string rId, string name, vector<Stop> stps, double km)
    : routeId(move(rId)),
    routeName(move(name)),
    stops(move(stps)),
    approxKilometer(km) {
}

// Adds a stop record to the internal track vector
void Route::addStop(const Stop& s) {
    stops.push_back(s);
}

// Replaces the entire route stop layout safely
void Route::setStops(vector<Stop> s) {
    stops = move(s);
}

// Modifies the descriptive name of the route profile
void Route::setRouteName(string n) {
    routeName = move(n);
}