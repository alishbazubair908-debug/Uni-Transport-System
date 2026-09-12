#pragma once
#include<string>
#include <vector>
#include "enums.h"
#include"StringUtils.h"

using namespace std;

struct PendingRegistration 
{
    string name, cnic, address, email, phone;
    int age = 0;
    Gender gender = Gender::MALE;
    string rollNumber, department, semester;

    string to_string() const {
        return sanitizeCsv(name) + "," + cnic + "," + sanitizeCsv(address) + ","
            + email + "," + phone + ","
            + std::to_string(age) + "," + genderToString(gender) + ","
            + rollNumber + "," + sanitizeCsv(department) + "," + semester;
    }

    static PendingRegistration from_string(const string& line)
    {
        stringstream ss(line); string token; vector<string> tokens;
        while (getline(ss, token, ',')) tokens.push_back(token);
        if (tokens.size() < 10) return {};
        PendingRegistration r;
        r.name = tokens[0]; r.cnic = tokens[1]; r.address = tokens[2];
        r.email = tokens[3]; r.phone = tokens[4];
        try { r.age = stoi(tokens[5]); }
        catch (...) { r.age = 0; }
        r.gender = genderFromString(tokens[6]);
        r.rollNumber = tokens[7]; r.department = tokens[8]; r.semester = tokens[9];
        return r;
    }
};



struct TripLog 
{
    string tripId, vehicleId, routeId, date;
    TripDirection direction = TripDirection::ARRIVAL;
    double routeKm = 0.0, fuelUsedLiters = 0.0, fuelCostEstimate = 0.0;

    string to_string()const {
        ostringstream oss;
        oss << tripId << "," << vehicleId << "," << routeId << "," << date << ","
            << tripDirectionToString(direction) << "," << routeKm << "," << fuelUsedLiters << "," << fuelCostEstimate;
        return oss.str();
    }
    static TripLog from_string(const string& line) {
        stringstream ss(line); string token; vector<string>tokens;
        while (getline(ss, token, ','))tokens.push_back(token);
        if (tokens.size() < 8)return{};
        TripLog t;
        t.tripId = tokens[0]; t.vehicleId = tokens[1];
        t.routeId = tokens[2]; t.date = tokens[3];
        t.direction = tripDirectionFromString(tokens[4]);
        try {
            t.routeKm = stod(tokens[5]);
            t.fuelUsedLiters = stod(tokens[6]);
            t.fuelCostEstimate = stod(tokens[7]);
        }
        catch (...) {}
        return t;
    }
};



struct PetrolLog {
    string logId, vehicleId, date;
    double liters = 0.0, cost = 0.0;
    string driverId;
    string to_string()const {
        return logId + "," + vehicleId + "," + date + "," +
            std::to_string(liters) + "," + std::to_string(cost) + "," + driverId;
    }
    static PetrolLog from_string(const string& line) {
        stringstream ss(line); string token; vector<string>tokens;
        while (getline(ss, token, ','))tokens.push_back(token);
        if (tokens.size() < 6)return{};
        PetrolLog p;
        p.logId = tokens[0]; p.vehicleId = tokens[1]; p.date = tokens[2];
        p.driverId = tokens[5];
        try { p.liters = stod(tokens[3]); p.cost = stod(tokens[4]); }
        catch (...) {}
        return p;
    }
};



struct MonthlyCapital 
{
    string month;
    double totalCapital = 0.0, spentOnFuel = 0.0;
    double remaining()const
    { return totalCapital - spentOnFuel; 
    }
};

struct Stop 
{ 
    string stopId; 
    string stopName;
    string arrivalTime;
};


struct Bill 
{
    string billId, studentId;
    double amount = 0.0;
    string dueDate;
    bool   isPaid = false;
};
struct PaymentRecord 
{
    string paymentId, billId;
    double amountPaid = 0.0;
    string paymentDate, paymentMethod;
};
