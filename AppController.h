#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "Student.h"
#include "Driver.h"
#include "Admin.h"
#include "DateUtils.h"
#include "PDFGenerator.h"
#include "ReportGenerator.h"
#include "ValidationUtil.h"
#include "CsvUtils.h"
#include "Structs.h"
#include "enums.h"
#include "StringUtils.h"
#include "Vehicle.h"
#include "Route.h"
#include "TransportPass.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <regex>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
using namespace std;

class AppController {
public:
    unordered_map<string, shared_ptr<Person>>  users;
    vector<PendingRegistration>                pendingRegistrations;
    vector<Vehicle>                            vehicles;
    vector<Route>                              routes;
    vector<TransportPass>                      passes;
    vector<Bill>                               bills;
    vector<PaymentRecord>                      paymentRecords;
    vector<PetrolLog>                          petrolLogs;
    vector<TripLog>                            tripLogs;
    unordered_map<string, queue<string>>       routeWaitlists;
    unordered_map<string, MonthlyCapital>      monthlyCapitals;
    double petrolPricePerLitre = 280.0;

    AppController() = default;

    // ── File I/O ──────────────────────────────────────────────────
    void saveUsersToFile();
    void loadUsersFromFile();
    void savePendingRegistrationsToFile();
    void loadPendingRegistrationsToFile();
    void saveVehiclesToFile();
    void loadVehiclesFromFile();
    void saveRoutesToFile();
    void loadRoutesFromFile();
    void savePassesToFile();
    void loadPassesFromFile();
    void saveBillsToFile();
    void loadBillsFromFile();
    void savePaymentsToFile();
    void loadPaymentsFromFile();
    void saveWaitlistsToFile();
    void loadWaitlistsFromFile();
    void saveTripLogsToFile();
    void loadTripLogsFromFile();
    void savePetrolLogsToFile();
    void loadPetrolLogsFromFile();
    void saveMonthlyCapitalToFile();
    void loadMonthlyCapitalFromFile();

    // ── System Pipelines ──────────────────────────────────────────
    void sweepExpiredPasses();
    bool registerUser(const shared_ptr<Person>& person);
    void addVehicle(const Vehicle& vehicle);
    bool removeVehicle(const string& vehicleId);
    void addRoute(const Route& route);
    bool assignVehicleToRoute(const string& vehicleId, const string& routeId);
    void assignDriverToVehicle(const string& driverId, const string& vehicleId);
    void unassignDriverFromVehicle(const string& driverId);
    bool isVehiclePlateInUse(const string& plate,
        const string& excludeVehicleId = "") const;

    // ── Pass Management ───────────────────────────────────────────
    void requestPass(const string& studentId,
        const string& routeId,
        const string& stopName);
    void requestPassChange(const string& studentId,
        const string& newRouteId,
        const string& newStopName);
    void financeClearPass(const string& passId);
    void cancelPass(const string& passId);
    void processRouteWaitlist(const string& routeId);
    void viewRouteWaitlist(const string& routeId);

    // ── Trip & Fuel ───────────────────────────────────────────────
    bool dispatchTrip(const string& vehicleId, TripDirection direction);
    void viewDailyTripSummary(const string& vehicleId)    const;
    void viewVehicleFuelCostToday(const string& vehicleId) const;
    void logPetrol(const PetrolLog& log);
    void viewAllVanDetails()                               const;

    // ── Finance ───────────────────────────────────────────────────
    void setMonthlyCapital(double amount);
    void viewMonthlyCapitalStatus() const;
    void updatePetrolPrice(double price);

    // ── Reports ───────────────────────────────────────────────────
    void generateCSVReport() const;   // replaces generateExcelReport
    void displaySystemStats();

    // ── Query helpers ─────────────────────────────────────────────
    int  getRemainingSeatsForRoute(const string& routeId)     const;
    bool isStopOnRoute(const string& routeId,
        const string& stopName)                const;
    int  getTodayTripCount(const string& vehicleId,
        TripDirection direction)           const;
    int  getEffectiveTripCount(const string& vehicleId,
        TripDirection direction)       const;
    int  getTodayTotalTrips(const string& vehicleId)          const;
    int  getTodayTotalEffectiveTrips(const string& vehicleId) const;
    void viewDriverAssignments()                              const;
};

#endif