#pragma once

#include<iostream>
#include <string>
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
#include"ValidationUtil.h"
#include "enums.h"
#include "Admin.h"
#include "AppController.h"

using namespace std;

inline string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

inline string getRobustInput(const string& prompt) {
    cout << prompt << flush;
    string line;
    if (!getline(cin, line)) {
        cin.clear();
        static int corruptionCheck = 0;
        if (++corruptionCheck > 10) {
            cerr << "\n[Fatal Error] Input pipeline corrupted. Terminating.\n";
            exit(1);
        }
        return "";
    }
    return trim(line);
}

inline string sanitizeCsv(string s) {
    for (char& c : s) if (c == ',') c = ';';
    return s;
}

inline string cleanNumericString(string s) {
    string res = "";
    bool decimalFound = false;
    for (char c : s) {
        if (isdigit(static_cast<unsigned char>(c))) {
            res += c;
        }
        else if (c == '.' && !decimalFound) {
            res += c;
            decimalFound = true;
        }
    }
    return res;
}


// HELPERS

bool hasAdminWithRole(const AppController& ctrl, AdminRole role) 
{
    for (const auto& kv : ctrl.users) 
    {
        if (kv.second->getRole() == "Admin")
        {
            auto a = std::dynamic_pointer_cast<Admin>(kv.second);
            if (a && a->getAdminRole() == role) return true;
        }
    }
    return false;
}

bool hasRole(const AppController& ctrl, const string& role) {
    for (const auto& kv : ctrl.users) if (kv.second->getRole() == role) return true;
    return false;
}

// ============================================================================
// INPUT HELPERS
// ============================================================================
string inputName(const string& label)
{
    while (true) {
        string v = getRobustInput(label);
        if (ValidationUtil::isValidName(v)) return sanitizeCsv(v);
        cout << "[Error] Name must contain letters only (spaces, hyphens, dots allowed).\n";
    }
}
string inputEmail(const string& label)
{
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidEmail(v)) return v; cout << "[Error] Invalid email.\n"; }
}
string inputPassword(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidPassword(v)) return v; cout << "[Error] 8+ characters.\n"; }
}
string inputCNIC(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidCNIC(v)) return v; cout << "[Error] Format: XXXXX-XXXXXXX-X\n"; }
}
string inputPhone(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidPhone(v)) return v; cout << "[Error] Format: 03XX-XXXXXXX or +923XXXXXXXXX\n"; }
}
int inputAge(const string& label) {
    while (true) {
        string v = getRobustInput(label); v = cleanNumericString(v);
        try { int a = stoi(v); if (ValidationUtil::isValidAge(a)) return a; }
        catch (...) {}
        cout << "[Error] Age 16-25 required for students.\n";
    }
}
int inputAgeEmployee(const string& label) {
    while (true) {
        string v = getRobustInput(label); v = cleanNumericString(v);
        try { int a = stoi(v); if (ValidationUtil::isValidAgeEmployee(a)) return a; }
        catch (...) {}
        cout << "[Error] Age 25-80 required for this role.\n";
    }
}
Gender inputGender(const string& label) {
    while (true) {
        string v = getRobustInput(label + " (1=Male, 2=Female, 3=Other): ");
        if (v == "1") return Gender::MALE;
        if (v == "2") return Gender::FEMALE;
        if (v == "3") return Gender::OTHER;
        cout << "[Error] Enter 1, 2, or 3.\n";
    }
}
string inputAddress(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidAddress(v)) return sanitizeCsv(v); cout << "[Error] Min 5 chars.\n"; }
}
string inputDesignation(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidDesignation(v)) return sanitizeCsv(v); cout << "[Error] 1-60 chars.\n"; }
}
double inputSalary(const string& label) {
    while (true) {
        string v = getRobustInput(label + " (Rs 15,000-500,000): ");
        v = cleanNumericString(v);
        try { double s = stod(v); if (ValidationUtil::isValidSalary(s)) return s; }
        catch (...) {}
        cout << "[Error] Salary must be between Rs 15,000 and Rs 500,000.\n";
    }
}
string inputHireDate(const string& label) {
    while (true) { string v = getRobustInput(label + " (YYYY-MM-DD): "); if (ValidationUtil::isValidHireDate(v)) return v; cout << "[Error] Format: YYYY-MM-DD.\n"; }
}
string inputLicense(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidLicense(v)) return v; cout << "[Error] 6+ alphanumeric.\n"; }
}
string inputRollNumber(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidRollNumber(v)) return v; cout << "[Error] Min 5 chars.\n"; }
}
string inputSemester(const string& label) {
    while (true) {
        string v = getRobustInput(label + " (1-8): ");
        v = cleanNumericString(v);
        if (ValidationUtil::isValidSemester(v)) return v;
        cout << "[Error] Semester must be between 1 and 8.\n";
    }
}
string inputDepartment(const string& label) {
    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidDepartment(v)) return sanitizeCsv(v); cout << "[Error] Letters only.\n"; }
}
string inputVanPurpose() {
    while (true) {
        string v = getRobustInput("VAN Purpose / Use Case (5-120 chars): ");
        if (ValidationUtil::isValidVanPurpose(v)) return sanitizeCsv(v);
        cout << "[Error] Purpose must be 5-120 characters.\n";
    }
}
double inputVanDailyMileage() {
    while (true) {
        string v = getRobustInput("Daily Mileage within University (1-6 km): ");
        v = cleanNumericString(v);
        try { double d = stod(v); if (ValidationUtil::isValidVanDailyKm(d)) return d; }
        catch (...) {}
        cout << "[Error] Must be 1-6 km.\n";
    }
}

string inputStopId(const string& label) {
    while (true) {
        string v = getRobustInput(label);
        if (ValidationUtil::isValidStopId(v)) return v;
        cout << "[Error] Stop ID must be at least 2 characters long and must contain both "
            << "letters and digits (no spaces, hyphens, or special characters, e.g., S01, ST2).\n";
    }
}

string inputRouteId(const string& label) {
    while (true) {
        string v = getRobustInput(label);
        if (ValidationUtil::isValidRouteId(v)) return v;
        cout << "[Error] Route ID must be alphanumeric only, minimum 2 characters (e.g. R1 or RT01).\n";
    }
}
string inputCoordinates(const string& label) {
    while (true) {
        string v = getRobustInput(label +
            " (lat,lon e.g. 31.5204,74.3587 OR descriptive name >= 5 chars, no commas): ");
        if (ValidationUtil::isValidCoordinates(v)) return sanitizeCsv(v);
        cout << "[Error] Enter lat,lon (e.g. 31.52,74.35) or a location description "
            << "of at least 5 characters without commas.\n";
    }
}