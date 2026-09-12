#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
//#include <string>
//#include <vector>
//#include <memory>
//#include <queue>    
//#include <unordered_map>
//#include <sstream>
//#include <fstream>
//#include <regex>
//#include <chrono>
//#include <iomanip>
//#include <algorithm>
//#include <stdexcept>
//#include <ctime>
//#include <cctype>
//#include <cstdlib>
//#include <cstdio>
//#include <cstdint>
//
#include "Student.h"
#include "Driver.h"
#include "Admin.h"
#include"DateUtils.h"
#include"PDFGenerator.h"
#include"ReportGenerator.h"
#include"ValidationUtil.h"
#include "Csvutils.h"
#include"Structs.h"

#include "AppController.h"




using namespace std;

// ============================================================================
// 1. STATE & CONSTANT STRUCTURES
// ============================================================================

//enum class VehicleType { BUS, VAN };
//inline string vehicleTypeToString(VehicleType t) {
//    return (t == VehicleType::VAN) ? "VAN" : "BUS";
//}
//inline VehicleType vehicleTypeFromString(const string& s) {
//    return (s == "VAN") ? VehicleType::VAN : VehicleType::BUS;
//}
//
//enum class PassStatus { PENDING_PAYMENT, ACTIVE, WAITLISTED, EXPIRED };
//inline string passStatusToString(PassStatus s) {
//    switch (s) {
//    case PassStatus::PENDING_PAYMENT: return "PENDING_PAYMENT";
//    case PassStatus::ACTIVE:          return "ACTIVE";
//    case PassStatus::WAITLISTED:      return "WAITLISTED";
//    case PassStatus::EXPIRED:         return "EXPIRED";
//    default:                          return "EXPIRED";
//    }
//}
//inline PassStatus passStatusFromString(const string& s) {
//    if (s == "PENDING_PAYMENT") return PassStatus::PENDING_PAYMENT;
//    if (s == "ACTIVE")          return PassStatus::ACTIVE;
//    if (s == "WAITLISTED")      return PassStatus::WAITLISTED;
//    return PassStatus::EXPIRED;
//}
//
//enum class DriverStatus { FREE, ON_ROUTE };
//inline string driverStatusToString(DriverStatus s) {
//    return (s == DriverStatus::ON_ROUTE) ? "ON_ROUTE" : "FREE";
//}
//
//enum class TripDirection { ARRIVAL, DEPARTURE };
//inline string tripDirectionToString(TripDirection d) {
//    return (d == TripDirection::DEPARTURE) ? "DEPARTURE" : "ARRIVAL";
//}
//inline TripDirection tripDirectionFromString(const string& s) {
//    return (s == "DEPARTURE") ? TripDirection::DEPARTURE : TripDirection::ARRIVAL;
//}
//
//enum class AdminRole {
//    SUPER_ADMIN,
//    TRANSPORT_MANAGER,
//    FINANCE_MANAGER
//};
//
//inline string adminRoleToString(AdminRole r) {
//    switch (r) {
//    case AdminRole::SUPER_ADMIN:        return "SUPER_ADMIN";
//    case AdminRole::TRANSPORT_MANAGER:  return "TRANSPORT_MANAGER";
//    case AdminRole::FINANCE_MANAGER:    return "FINANCE_MANAGER";
//    default:                            return "SUPER_ADMIN";
//    }
//}
//inline AdminRole adminRoleFromString(const string& s) {
//    if (s == "TRANSPORT_MANAGER") return AdminRole::TRANSPORT_MANAGER;
//    if (s == "FINANCE_MANAGER")   return AdminRole::FINANCE_MANAGER;
//    return AdminRole::SUPER_ADMIN;
//}

//enum class Gender { MALE, FEMALE, OTHER };
//inline string genderToString(Gender g) 
//{
//    switch (g) {
//    case Gender::MALE:   return "MALE";
//    case Gender::FEMALE: return "FEMALE";
//    default:             return "OTHER";
//    }
//}
//inline Gender genderFromString(const string& s) {
//    if (s == "FEMALE") return Gender::FEMALE;
//    if (s == "OTHER")  return Gender::OTHER;
//    return Gender::MALE;
//}

// ============================================================================
// 2. STANDALONE UTILITIES
// ============================================================================

//namespace DateUtil {
//    inline tm safe_localtime(const time_t& timer) {
//        tm* tmp = localtime(&timer);
//        return tmp ? *tmp : tm{};
//    }
//    inline string getCurrentDate() {
//        auto now = chrono::system_clock::now();
//        auto t = chrono::system_clock::to_time_t(now);
//        tm lt = safe_localtime(t);
//        stringstream ss;
//        ss << put_time(&lt, "%Y-%m-%d");
//        return ss.str();
//    }
//    inline string getCurrentYearMonth() {
//        auto now = chrono::system_clock::now();
//        auto t = chrono::system_clock::to_time_t(now);
//        tm lt = safe_localtime(t);
//        stringstream ss;
//        ss << put_time(&lt, "%Y-%m");
//        return ss.str();
//    }
//    inline string calculateExpiryDate(int activeDays) {
//        auto now = chrono::system_clock::now();
//        auto expiry = now + chrono::hours(24 * activeDays);
//        auto t = chrono::system_clock::to_time_t(expiry);
//        tm lt = safe_localtime(t);
//        stringstream ss;
//        ss << put_time(&lt, "%Y-%m-%d");
//        return ss.str();
//    }
//    inline int timeToMinutes(const string& timeStr) {
//        const regex pattern(R"(^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$)");
//        if (!regex_match(timeStr, pattern)) return -1;
//        stringstream ss(timeStr);
//        string hrs, mins;
//        getline(ss, hrs, ':');
//        getline(ss, mins);
//        try { return stoi(hrs) * 60 + stoi(mins); }
//        catch (...) { return -1; }
//    }
//}

//namespace ValidationUtil {
//    inline bool isValidEmail(const string& email) {
//        const regex p(R"(^([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9.-]+)\.([a-zA-Z]{2,})$)");
//        return regex_match(email, p);
//    }
//    inline bool isValidVehiclePlate(const string& plate) {
//        const regex p(R"(^[A-Z]{3}-\d{4}$)");
//        return regex_match(plate, p);
//    }
//    inline bool isValidPassword(const string& pw) { return pw.length() >= 8; }
//
//    inline bool isValidName(const string& name) {
//        if (name.empty()) return false;
//        bool hasLetter = false;
//        for (char c : name) {
//            if (isalpha(static_cast<unsigned char>(c))) { hasLetter = true; continue; }
//            if (c == ' ' || c == '.' || c == '-')      continue;
//            return false;
//        }
//        return hasLetter;
//    }
//
//    inline bool isValidCNIC(const string& cnic) {
//        const regex p(R"(^\d{5}-\d{7}-\d{1}$)");
//        return regex_match(cnic, p);
//    }
//    inline bool isValidPhone(const string& phone) {
//        const regex p(R"(^(03\d{2}-\d{7}|\+923\d{9})$)");
//        return regex_match(phone, p);
//    }
//    inline bool isValidAge(int age) { return age >= 16 && age <= 25; }
//    inline bool isValidAgeEmployee(int age) { return age >= 25 && age <= 80; }
//    inline bool isValidSalary(double salary) { return salary >= 15000.0 && salary <= 500000.0; }
//    inline bool isValidLicense(const string& lic) {
//        if (lic.size() < 6) return false;
//        for (char c : lic)
//            if (!isalnum(static_cast<unsigned char>(c)) && c != '-') return false;
//        return true;
//    }
//    inline bool isValidRollNumber(const string& roll) { return roll.size() >= 5; }
//    inline bool isValidSemester(const string& sem) {
//        try { int s = stoi(sem); return s >= 1 && s <= 8; }
//        catch (...) { return false; }
//    }
//    inline bool isValidDepartment(const string& dept) { return isValidName(dept); }
//    inline bool isValidAddress(const string& addr) { return addr.size() >= 5; }
//    inline bool isValidHireDate(const string& date) {
//        const regex p(R"(^\d{4}-\d{2}-\d{2}$)");
//        return regex_match(date, p);
//    }
//    inline bool isValidDesignation(const string& d) { return !d.empty() && d.size() <= 60; }
//    inline bool isValidVanDailyKm(double km) { return km >= 1.0 && km <= 6.0; }
//    inline bool isValidVanPurpose(const string& p) { return !p.empty() && p.size() >= 5 && p.size() <= 120; }
//
//    // STRICT BOTH: Stop ID must be at least 2 characters long and 
//     // must contain a mixture of both letters and digits.
//    inline bool isValidStopId(const string& id) {
//        if (id.length() < 2) return false; // Minimum length of 2
//
//        bool hasLetter = false;
//        bool hasDigit = false;
//
//        for (char c : id) {
//            if (isalpha(static_cast<unsigned char>(c))) {
//                hasLetter = true;
//            }
//            else if (isdigit(static_cast<unsigned char>(c))) {
//                hasDigit = true;
//            }
//            else {
//                return false; // Rejects spaces, hyphens, and other special characters
//            }
//        }
//        return hasLetter && hasDigit; // Must contain at least one letter AND one digit
//    }
//
//    inline bool isValidRouteId(const string& id) {
//        if (id.empty() || id.size() < 2) return false;
//        for (char c : id)
//            if (!isalnum(static_cast<unsigned char>(c))) return false;
//        return true;
//    }
//
//    inline bool isValidCoordinates(const string& coord) {
//        if (coord.size() < 3) return false;
//        const regex strict(R"(^-?\d{1,3}(\.\d+)?,-?\d{1,3}(\.\d+)?$)");
//        if (regex_match(coord, strict)) return true;
//        if (coord.size() >= 5) {
//            for (char c : coord) if (c == ',') return false;
//            return true;
//        }
//        return false;
//    }
//}

//namespace PDFGenerator {
//    inline void generatePassPDF(const string& passId, const string& studentId,
//        const string& routeId, const string& expiry,
//        const string& semester = "", const string& department = "",
//        const string& vanInfo = "") {
//        string filename = "pass_" + passId + ".pdf";
//        ofstream file(filename);
//        if (file.is_open()) {
//            file << "%PDF-1.4 (Mock Pass Document)\n=========================================\n";
//            file << "       UNIVERSITY TRANSPORT PASS         \n=========================================\n";
//            file << "  Pass ID    : " << passId << "\n  Student ID : " << studentId << "\n";
//            if (!semester.empty())   file << "  Semester   : " << semester << "\n";
//            if (!department.empty()) file << "  Department : " << department << "\n";
//            file << "  Route ID   : " << routeId << "\n  Expiry Date: " << expiry
//                << "\n  Status     : ACTIVE\n";
//            if (!vanInfo.empty())    file << "  VAN Info   : " << vanInfo << "\n";
//            file << "=========================================\n";
//        }
//    }
//}

//namespace ReportGenerator {
//    inline void generateFinancialReport(double totalRevenue, double totalFuelCosts) {
//        cout << "\n=========================================\n"
//            << "         FINANCIAL SUMMARY REPORT        \n"
//            << "=========================================\n";
//        cout << "  Gross Revenue Earned : Rs " << fixed << setprecision(2) << totalRevenue << "\n";
//        cout << "  Total Fuel Expenses  : Rs " << totalFuelCosts << "\n";
//        cout << "  Net Operating Margin : Rs " << (totalRevenue - totalFuelCosts) << "\n"
//            << "=========================================\n";
//    }
//}

//namespace XlsxUtil {
//    static string xmlEsc(const string& s) {
//        string o; o.reserve(s.size());
//        for (char c : s) {
//            if (c == '&') o += "&amp;"; else if (c == '<') o += "&lt;";
//            else if (c == '>') o += "&gt;"; else if (c == '"') o += "&quot;"; else o += c;
//        }
//        return o;
//    }
//    static string col(int c) {
//        string r; c++;
//        while (c > 0) { c--; r = char('A' + c % 26) + r; c /= 26; }
//        return r;
//    }
//    static string ref(int c, int r) { return col(c) + to_string(r); }
//    static string fmtDbl(double v) {
//        bool neg = (v < 0.0); if (neg) v = -v;
//        long long cents = (long long)(v * 100.0 + 0.5);
//        string f = to_string(cents % 100); if (f.size() < 2) f = "0" + f;
//        return (neg ? "-" : "") + to_string(cents / 100) + "." + f;
//    }
//    static string nc(int c, int r, double v, int s = 0) {
//        return "<c r=\"" + ref(c, r) + "\" s=\"" + to_string(s) + "\"><v>" + fmtDbl(v) + "</v></c>";
//    }
//    static string ic(int c, int r, int v, int s = 0) {
//        return "<c r=\"" + ref(c, r) + "\" s=\"" + to_string(s) + "\"><v>" + to_string(v) + "</v></c>";
//    }
//    static string isc(int c, int r, const string& val, int s = 0) {
//        return "<c r=\"" + ref(c, r) + "\" t=\"inlineStr\" s=\"" + to_string(s)
//            + "\"><is><t>" + xmlEsc(val) + "</t></is></c>";
//    }
//    static string dblStr(double v, int prec = 2) {
//        ostringstream o; o << fixed << setprecision(prec) << v;
//        return o.str();
//    }
//}
//
//namespace ZipWriter {
//    static uint32_t crcTab[256];
//    static bool     crcReady = false;
//    static void initCrc() {
//        if (crcReady) return;
//        for (uint32_t i = 0; i < 256; i++) {
//            uint32_t c = i;
//            for (int j = 0; j < 8; j++) c = (c & 1) ? (0xEDB88320u ^ (c >> 1)) : (c >> 1);
//            crcTab[i] = c;
//        }
//        crcReady = true;
//    }
//    static uint32_t crc32(const string& d) {
//        initCrc(); uint32_t c = 0xFFFFFFFFu;
//        for (unsigned char b : d) c = crcTab[(c ^ b) & 0xFF] ^ (c >> 8);
//        return c ^ 0xFFFFFFFFu;
//    }
//    static void u16(ofstream& f, uint16_t v) { f.put(v & 0xFF); f.put((v >> 8) & 0xFF); }
//    static void u32(ofstream& f, uint32_t v) {
//        f.put(v & 0xFF); f.put((v >> 8) & 0xFF); f.put((v >> 16) & 0xFF); f.put((v >> 24) & 0xFF);
//    }
//    static bool write(const string& path, const vector<pair<string, string>>& entries) {
//        ofstream f(path, ios::binary);
//        if (!f) return false;
//        struct CD { string name; uint32_t crc, sz, off; };
//        vector<CD> dir;
//        for (const auto& entry : entries)
//        {
//            const string& name = entry.first;
//            const string& data = entry.second;
//            uint32_t c = crc32(data), sz = (uint32_t)data.size(), off = (uint32_t)f.tellp();
//            u32(f, 0x04034B50); u16(f, 20); u16(f, 0); u16(f, 0); u16(f, 0); u16(f, 0);
//            u32(f, c); u32(f, sz); u32(f, sz);
//            u16(f, (uint16_t)name.size()); u16(f, 0);
//            f.write(name.data(), (streamsize)name.size());
//            f.write(data.data(), (streamsize)sz);
//            dir.push_back({ name,c,sz,off });
//        }
//        uint32_t cdOff = (uint32_t)f.tellp();
//        for (auto& e : dir) {
//            u32(f, 0x02014B50); u16(f, 20); u16(f, 20); u16(f, 0); u16(f, 0); u16(f, 0); u16(f, 0);
//            u32(f, e.crc); u32(f, e.sz); u32(f, e.sz);
//            u16(f, (uint16_t)e.name.size()); u16(f, 0); u16(f, 0); u16(f, 0); u16(f, 0);
//            u32(f, 0); u32(f, e.off);
//            f.write(e.name.data(), (streamsize)e.name.size());
//        }
//        uint32_t cdSz = (uint32_t)f.tellp() - cdOff;
//        u32(f, 0x06054B50); u16(f, 0); u16(f, 0);
//        u16(f, (uint16_t)dir.size()); u16(f, (uint16_t)dir.size());
//        u32(f, cdSz); u32(f, cdOff); u16(f, 0);
//        return true;
//    }
//}

//inline string trim(const string& str) {
//    size_t first = str.find_first_not_of(" \t\r\n");
//    if (first == string::npos) return "";
//    size_t last = str.find_last_not_of(" \t\r\n");
//    return str.substr(first, (last - first + 1));
//}
//
//inline string getRobustInput(const string& prompt) {
//    cout << prompt << flush;
//    string line;
//    if (!getline(cin, line)) {
//        cin.clear();
//        static int corruptionCheck = 0;
//        if (++corruptionCheck > 10) {
//            cerr << "\n[Fatal Error] Input pipeline corrupted. Terminating.\n";
//            exit(1);
//        }
//        return "";
//    }
//    return trim(line);
//}
//
//inline string sanitizeCsv(string s) {
//    for (char& c : s) if (c == ',') c = ';';
//    return s;
//}
//
//inline string cleanNumericString(string s) {
//    string res = "";
//    bool decimalFound = false;
//    for (char c : s) {
//        if (isdigit(static_cast<unsigned char>(c))) {
//            res += c;
//        }
//        else if (c == '.' && !decimalFound) {
//            res += c;
//            decimalFound = true;
//        }
//    }
//    return res;
//}

// ============================================================================
// PERSISTENT ID COUNTERS
// ============================================================================
//struct IdCounters {
//    int adminNext = 2001;
//    int driverNext = 2001;
//    int studentNext = 1001;
//    int tripNext = 5001;
//    int billNext = 2001;
//    int payNext = 3001;
//
//    void saveToFile() const {
//        ofstream f("id_counters.txt");
//        if (!f) return;
//        f << adminNext << "\n" << driverNext << "\n" << studentNext << "\n"
//            << tripNext << "\n" << billNext << "\n" << payNext << "\n";
//    }
//    void loadFromFile() {
//        ifstream f("id_counters.txt");
//        if (!f) return;
//        f >> adminNext >> driverNext >> studentNext >> tripNext >> billNext >> payNext;
//    }
//};
//static IdCounters gCounters;

// ============================================================================
// 3. POLYMORPHIC PERSON / EMPLOYEE HIERARCHY
// ============================================================================

//class Person {
//protected:
//    string name, cnic, address, email, phone, password;
//    int    age = 0;
//    Gender gender = Gender::MALE;
//public:
//    Person() = default;
//    Person(string nm, string cn, string addr, string em, string ph, int ag, Gender gn, string pw)
//        :name(move(nm)), cnic(move(cn)), address(move(addr)),
//        email(move(em)), phone(move(ph)), age(ag), gender(gn), password(move(pw)) {
//    }
//    virtual ~Person() = default;
//    virtual string getRole()     const = 0;
//    virtual string getSystemId() const = 0;
//    string getName()    const { return name; }
//    string getCNIC()    const { return cnic; }
//    string getAddress() const { return address; }
//    string getEmail()   const { return email; }
//    string getPhone()   const { return phone; }
//    int    getAge()     const { return age; }
//    Gender getGender()  const { return gender; }
//    string getPassword()const { return password; }
//    bool   checkPassword(const string& pw)const { return password == pw; }
//    void setName(string n) { name = move(n); }
//    void setCNIC(string c) { cnic = move(c); }
//    void setAddress(string a) { address = move(a); }
//    void setEmail(string e) { email = move(e); }
//    void setPhone(string p) { phone = move(p); }
//    void setAge(int a) { age = a; }
//    void setGender(Gender g) { gender = g; }
//};

//class Employee : public Person {
//protected:
//    string employeeID, designation, hireDate;
//    double salary = 0.0;
//public:
//    Employee() = default;
//    Employee(string empId, string nm, string cn, string addr, string em, string ph,
//        int ag, Gender gn, string pw, string desig, double sal, string hire)
//        :Person(move(nm), move(cn), move(addr), move(em), move(ph), ag, gn, move(pw)),
//        employeeID(move(empId)), designation(move(desig)), hireDate(move(hire)), salary(sal) {
//    }
//    string getEmployeeID()  const { return employeeID; }
//    string getDesignation() const { return designation; }
//    double getSalary()      const { return salary; }
//    string getHireDate()    const { return hireDate; }
//    string getSystemId()    const override { return employeeID; }
//    void setDesignation(string d) { designation = move(d); }
//    void setSalary(double s) { salary = s; }
//    void setHireDate(string h) { hireDate = move(h); }
//};

//class Admin : public Employee {
//private:
//    AdminRole adminRole;
//public:
//    Admin() = default;
//    Admin(string empId, string nm, string cn, string addr, string em, string ph,
//        int ag, Gender gn, string pw, string desig, double sal, string hire, AdminRole role)
//        :Employee(move(empId), move(nm), move(cn), move(addr), move(em), ph,
//            ag, gn, move(pw), move(desig), sal, move(hire)), adminRole(role) {
//    }
//    string    getRole()         const override { return "Admin"; }
//    AdminRole getAdminRole()    const { return adminRole; }
//    void      setAdminRole(AdminRole r) { adminRole = r; }
//    bool canManageVehicles()const { return adminRole == AdminRole::SUPER_ADMIN || adminRole == AdminRole::TRANSPORT_MANAGER; }
//    bool canManageFinance() const { return adminRole == AdminRole::SUPER_ADMIN || adminRole == AdminRole::FINANCE_MANAGER; }
//    bool canManageUsers()   const { return adminRole == AdminRole::SUPER_ADMIN; }
//    bool isSuperAdmin()     const { return adminRole == AdminRole::SUPER_ADMIN; }
//
//    static string generateEmployeeId() {
//        string id = "EMP-" + to_string(gCounters.adminNext++);
//        gCounters.saveToFile();
//        return id;
//    }
//};

//class Driver : public Employee {
//private:
//    string licenseNumber;
//    DriverStatus status = DriverStatus::FREE;
//    string assignedVehicleId;
//public:
//    Driver() = default;
//    Driver(string empId, string nm, string cn, string addr, string em, string ph,
//        int ag, Gender gn, string pw, string desig, double sal, string hire, string lic)
//        :Employee(move(empId), move(nm), move(cn), move(addr), move(em), ph,
//            ag, gn, move(pw), move(desig), sal, move(hire)), licenseNumber(move(lic)) {
//    }
//    string       getRole()            const override { return "Driver"; }
//    string       getLicenseNumber()   const { return licenseNumber; }
//    DriverStatus getStatus()          const { return status; }
//    string       getAssignedVehicle() const { return assignedVehicleId; }
//    void setLicenseNumber(string l) { licenseNumber = move(l); }
//    void setStatus(DriverStatus s) { status = s; }
//    void setAssignedVehicle(string v) { assignedVehicleId = move(v); }
//
//    static string generateEmployeeId() {
//        string id = "DRV-" + to_string(gCounters.driverNext++);
//        gCounters.saveToFile();
//        return id;
//    }
//};
//
//class Student : public Person {
//private:
//    string registrationNumber, rollNumber, department, semester;
//    bool   activePass = false;
//public:
//    Student() = default;
//    Student(string regNum, string nm, string cn, string addr, string em, string ph,
//        int ag, Gender gn, string pw, string roll, string dept, string sem)
//        :Person(move(nm), move(cn), move(addr), move(em), move(ph), ag, gn, move(pw)),
//        registrationNumber(move(regNum)), rollNumber(move(roll)),
//        department(move(dept)), semester(move(sem)) {
//    }
//    string getRole()               const override { return "Student"; }
//    string getSystemId()           const override { return registrationNumber; }
//    string getRegistrationNumber() const { return registrationNumber; }
//    string getRollNumber()         const { return rollNumber; }
//    string getDepartment()         const { return department; }
//    string getSemester()           const { return semester; }
//    bool   hasActivePass()         const { return activePass; }
//    void setRollNumber(string r) { rollNumber = move(r); }
//    void setDepartment(string d) { department = move(d); }
//    void setSemester(string s) { semester = move(s); }
//    void setPassStatus(bool b) { activePass = b; }
//    void setPhone(string p) { phone = move(p); }
//    void setAddress(string a) { address = move(a); }
//
//    static string generateRegistrationNumber() {
//        string id = "STU-" + to_string(gCounters.studentNext++);
//        gCounters.saveToFile();
//        return id;
//    }
//};

// ============================================================================
// PENDING REGISTRATION STRUCT
// ============================================================================

//struct PendingRegistration {
//    string name, cnic, addr
//        ess, email, phone;
//    int age = 0;
//    Gender gender = Gender::MALE;
//    string rollNumber, department, semester;
//
//    string to_string() const {
//        return sanitizeCsv(name) + "," + cnic + "," + sanitizeCsv(address) + ","
//            + email + "," + phone + ","
//            + std::to_string(age) + "," + genderToString(gender) + ","
//            + rollNumber + "," + sanitizeCsv(department) + "," + semester;
//    }
//
//    static PendingRegistration from_string(const string& line) {
//        stringstream ss(line); string token; vector<string> tokens;
//        while (getline(ss, token, ',')) tokens.push_back(token);
//        if (tokens.size() < 10) return {};
//        PendingRegistration r;
//        r.name = tokens[0]; r.cnic = tokens[1]; r.address = tokens[2];
//        r.email = tokens[3]; r.phone = tokens[4];
//        try { r.age = stoi(tokens[5]); }
//        catch (...) { r.age = 0; }
//        r.gender = genderFromString(tokens[6]);
//        r.rollNumber = tokens[7]; r.department = tokens[8]; r.semester = tokens[9];
//        return r;
//    }
//};

// ============================================================================
// 4. VEHICLE & ROUTE MODULE
// ============================================================================

//struct TripLog {
//    string tripId, vehicleId, routeId, date;
//    TripDirection direction = TripDirection::ARRIVAL;
//    double routeKm = 0.0, fuelUsedLiters = 0.0, fuelCostEstimate = 0.0;
//
//    string to_string()const {
//        ostringstream oss;
//        oss << tripId << "," << vehicleId << "," << routeId << "," << date << ","
//            << tripDirectionToString(direction) << "," << routeKm << "," << fuelUsedLiters << "," << fuelCostEstimate;
//        return oss.str();
//    }
//    static TripLog from_string(const string& line) {
//        stringstream ss(line); string token; vector<string>tokens;
//        while (getline(ss, token, ','))tokens.push_back(token);
//        if (tokens.size() < 8)return{};
//        TripLog t;
//        t.tripId = tokens[0]; t.vehicleId = tokens[1];
//        t.routeId = tokens[2]; t.date = tokens[3];
//        t.direction = tripDirectionFromString(tokens[4]);
//        try {
//            t.routeKm = stod(tokens[5]);
//            t.fuelUsedLiters = stod(tokens[6]);
//            t.fuelCostEstimate = stod(tokens[7]);
//        }
//        catch (...) {}
//        return t;
//    }
//};

//class Vehicle {
//private:
//    string vehicleId, licensePlate;
//    VehicleType type;
//    int    capacity, occupiedSeats;
//    string currentDriverId, assignedRouteId;
//    double fuelEfficiency;
//    string fuelType;
//    string vanPurpose;
//    double vanDailyMileage = 0.0;
//
//public:
//    Vehicle(string vId, string plate, VehicleType t, int cap, double eff, string fType)
//        :vehicleId(move(vId)), licensePlate(move(plate)), type(t),
//        capacity(cap), occupiedSeats(0), fuelEfficiency(eff), fuelType(move(fType)) {
//    }
//    Vehicle(string vId, string plate, int cap, double eff, string fType,
//        string purpose, double dMileage)
//        :vehicleId(move(vId)), licensePlate(move(plate)), type(VehicleType::VAN),
//        capacity(cap), occupiedSeats(0), fuelEfficiency(eff), fuelType(move(fType)),
//        vanPurpose(move(purpose)), vanDailyMileage(dMileage) {
//    }
//
//    string      getVehicleId()      const { return vehicleId; }
//    string      getLicensePlate()   const { return licensePlate; }
//    VehicleType getType()           const { return type; }
//    int         getCapacity()       const { return capacity; }
//    int         getOccupiedSeats()  const { return occupiedSeats; }
//
//    // FIX 3: Clamp getRemainingSeats() to 0 so capacity edits that reduce capacity
//    //         below current occupiedSeats never produce a negative "available seats"
//    //         value visible on the student interface or used in seat-allocation logic.
//    int         getRemainingSeats() const { return max(0, capacity - occupiedSeats); }
//
//    void        incrementOccupiedSeats() { if (occupiedSeats < capacity) occupiedSeats++; }
//    void        decrementOccupiedSeats() { if (occupiedSeats > 0) occupiedSeats--; }
//    void        setOccupiedSeats(int s) { occupiedSeats = s; }
//    string      getCurrentDriverId()const { return currentDriverId; }
//    void        setDriver(string d) { currentDriverId = move(d); }
//    string      getAssignedRouteId()const { return assignedRouteId; }
//    void        setAssignedRouteId(string r) { assignedRouteId = move(r); }
//    double      getFuelEfficiency() const { return fuelEfficiency; }
//    string      getFuelType()       const { return fuelType; }
//    void setLicensePlate(string p) { licensePlate = move(p); }
//    void setType(VehicleType t_) { type = t_; }
//    void setCapacity(int c) { capacity = c; }
//    void setFuelEfficiency(double e) { fuelEfficiency = e; }
//    void setFuelType(string f) { fuelType = move(f); }
//
//    string getVanPurpose()      const { return vanPurpose; }
//    double getVanDailyMileage() const { return vanDailyMileage; }
//    void setVanPurpose(string p) { vanPurpose = move(p); }
//    void setVanDailyMileage(double m) { vanDailyMileage = m; }
//    bool isVAN()const { return type == VehicleType::VAN; }
//
//    double getVanEstimatedDailyFuelCost(double petrolPrice) const {
//        if (!isVAN() || fuelEfficiency <= 0.0) return 0.0;
//        return (vanDailyMileage / fuelEfficiency) * petrolPrice;
//    }
//
//    void printVanDetails(double petrolPrice = 0.0) const {
//        if (!isVAN()) return;
//        cout << "  [VAN Details]\n"
//            << "    Purpose           : " << (vanPurpose.empty() ? "N/A" : vanPurpose) << "\n"
//            << "    Daily Mileage     : " << vanDailyMileage << " km\n";
//        if (petrolPrice > 0.0) {
//            double fuelCost = getVanEstimatedDailyFuelCost(petrolPrice);
//            cout << "    Est. Daily Fuel   : Rs " << fixed << setprecision(2) << fuelCost
//                << " (" << fuelEfficiency << " km/L x " << petrolPrice << " Rs/L)\n";
//        }
//    }
//};

//struct PetrolLog {
//    string logId, vehicleId, date;
//    double liters = 0.0, cost = 0.0;
//    string driverId;
//    string to_string()const {
//        return logId + "," + vehicleId + "," + date + "," +
//            std::to_string(liters) + "," + std::to_string(cost) + "," + driverId;
//    }
//    static PetrolLog from_string(const string& line) {
//        stringstream ss(line); string token; vector<string>tokens;
//        while (getline(ss, token, ','))tokens.push_back(token);
//        if (tokens.size() < 6)return{};
//        PetrolLog p;
//        p.logId = tokens[0]; p.vehicleId = tokens[1]; p.date = tokens[2];
//        p.driverId = tokens[5];
//        try { p.liters = stod(tokens[3]); p.cost = stod(tokens[4]); }
//        catch (...) {}
//        return p;
//    }
//};

//struct MonthlyCapital {
//    string month;
//    double totalCapital = 0.0, spentOnFuel = 0.0;
//    double remaining()const { return totalCapital - spentOnFuel; }
//};
//
//struct Stop { string stopId, stopName, coordinates, arrivalTime; };

//class Route {
//private:
//    string routeId, routeName;
//    vector<Stop> stops;
//    double approxKilometer;
//public:
//    Route(string rId, string name, vector<Stop> stps, double km)
//        :routeId(move(rId)), routeName(move(name)), stops(move(stps)), approxKilometer(km) {
//    }
//    string              getRouteId()        const { return routeId; }
//    string              getRouteName()      const { return routeName; }
//    const vector<Stop>& getStops()          const { return stops; }
//    void                addStop(const Stop& s) { stops.push_back(s); }
//    double              getApproxKilometer()const { return approxKilometer; }
//    void                setApproxKilometer(double k) { approxKilometer = k; }
//    void                setStops(vector<Stop> s) { stops = move(s); }
//    void                setRouteName(string n) { routeName = move(n); }
//};

// ============================================================================
// 5. REGISTRATION & BILLING MODULE
// ============================================================================

//class TransportPass {
//private:
//    string passId, studentId, routeId, chosenStopName, issueDate, expiryDate;
//    PassStatus status;
//public:
//    TransportPass(string pId, string sId, string rId, string stopName)
//        :passId(move(pId)), studentId(move(sId)), routeId(move(rId)),
//        chosenStopName(move(stopName)), status(PassStatus::PENDING_PAYMENT) {
//    }
//    TransportPass(string pId, string sId, string rId, string stopName,
//        string iDate, string eDate, PassStatus stat)
//        :passId(move(pId)), studentId(move(sId)), routeId(move(rId)),
//        chosenStopName(move(stopName)), issueDate(move(iDate)),
//        expiryDate(move(eDate)), status(stat) {
//    }
//
//    string     getPassId()    const { return passId; }
//    string     getStudentId() const { return studentId; }
//    string     getRouteId()   const { return routeId; }
//    string     getChosenStop()const { return chosenStopName; }
//    PassStatus getStatus()    const { return status; }
//    string     getExpiryDate()const { return expiryDate; }
//    string     getIssueDate() const { return issueDate; }
//    void       setStatus(PassStatus s) { status = s; }
//    void activate(const string& iDate, const string& eDate) {
//        status = PassStatus::ACTIVE; issueDate = iDate; expiryDate = eDate;
//    }
//};

//struct Bill {
//    string billId, studentId;
//    double amount = 0.0;
//    string dueDate;
//    bool   isPaid = false;
//};
//struct PaymentRecord {
//    string paymentId, billId;
//    double amountPaid = 0.0;
//    string paymentDate, paymentMethod;
//};

// ============================================================================
// 6. CENTRAL APP CONTROLLER
// ============================================================================

//class AppController
//{
//public:
//    unordered_map<string, shared_ptr<Person>>  users;
//    vector<PendingRegistration>               pendingRegistrations;
//    vector<Vehicle>                           vehicles;
//    vector<Route>                             routes;
//    vector<TransportPass>                     passes;
//    vector<Bill>                              bills;
//    vector<PaymentRecord>                     paymentRecords;
//    vector<PetrolLog>                         petrolLogs;
//    vector<TripLog>                           tripLogs;
//    unordered_map<string, queue<string>>       routeWaitlists;
//    unordered_map<string, MonthlyCapital>      monthlyCapitals;
//    double petrolPricePerLitre = 280.0;
//
//    AppController() = default;
//
//private:
//    struct SheetDef { string name; string rId; string target; };
//
//    static string buildContentTypes(const vector<SheetDef>& sheets) {
//        ostringstream o;
//        o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
//            << "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
//            << "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
//            << "<Default Extension=\"xml\"  ContentType=\"application/xml\"/>"
//            << "<Override PartName=\"/xl/workbook.xml\""
//            << " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>";
//        for (const auto& s : sheets)
//            o << "<Override PartName=\"/xl/worksheets/" << s.target << "\""
//            << " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>";
//        o << "<Override PartName=\"/xl/styles.xml\""
//            << " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>"
//            << "</Types>";
//        return o.str();
//    }
//
//    static string buildWorkbookXml(const vector<SheetDef>& sheets) {
//        ostringstream o;
//        o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
//            << "<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
//            << " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
//            << "<bookViews><workbookView xWindow=\"0\" yWindow=\"0\""
//            << " windowWidth=\"18140\" windowHeight=\"8192\"/></bookViews>"
//            << "<sheets>";
//        int sheetId = 1;
//        for (const auto& s : sheets)
//            o << "<sheet name=\"" << XlsxUtil::xmlEsc(s.name)
//            << "\" sheetId=\"" << sheetId++ << "\" r:id=\"" << s.rId << "\"/>";
//        o << "</sheets></workbook>";
//        return o.str();
//    }
//
//    static string buildWorkbookRels(const vector<SheetDef>& sheets) {
//        ostringstream o;
//        o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
//            << "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">";
//        for (const auto& s : sheets)
//            o << "<Relationship Id=\"" << s.rId << "\""
//            << " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\""
//            << " Target=\"worksheets/" << s.target << "\"/>";
//        o << "<Relationship Id=\"rIdStyles\""
//            << " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\""
//            << " Target=\"styles.xml\"/>"
//            << "</Relationships>";
//        return o.str();
//    }
//
//public:
//    // ------------------------------------------------------------------
//    // FILE I/O
//    // ------------------------------------------------------------------
//    void saveUsersToFile() {
//        ofstream file("users_database.txt");
//        if (!file.is_open())return;
//        for (const auto& kv : users) {
//            const auto& p = kv.second;
//            file << p->getRole() << "," << p->getSystemId() << ","
//                << sanitizeCsv(p->getName()) << ","
//                << p->getCNIC() << "," << sanitizeCsv(p->getAddress()) << ","
//                << p->getEmail() << "," << p->getPhone() << ","
//                << p->getAge() << "," << genderToString(p->getGender()) << ","
//                << p->getPassword();
//            if (p->getRole() == "Admin") {
//                auto a = dynamic_pointer_cast<Admin>(p);
//                if (a) file << "," << sanitizeCsv(a->getDesignation()) << "," << a->getSalary()
//                    << "," << a->getHireDate() << "," << adminRoleToString(a->getAdminRole());
//            }
//            else if (p->getRole() == "Driver") {
//                auto d = dynamic_pointer_cast<Driver>(p);
//                if (d) file << "," << sanitizeCsv(d->getDesignation()) << "," << d->getSalary()
//                    << "," << d->getHireDate() << "," << d->getLicenseNumber()
//                    << "," << (d->getStatus() == DriverStatus::ON_ROUTE ? "1" : "0")
//                    << "," << d->getAssignedVehicle();
//            }
//            else if (p->getRole() == "Student") {
//                auto s = dynamic_pointer_cast<Student>(p);
//                if (s) file << "," << s->getRollNumber() << ","
//                    << sanitizeCsv(s->getDepartment()) << ","
//                    << s->getSemester() << "," << (s->hasActivePass() ? "1" : "0");
//            }
//            file << "\n";
//        }
//    }
//    // Checks if a license plate is already registered.
//    // If excludeVehicleId is provided, it ignores that specific vehicle (vital for editing).
//    bool isVehiclePlateInUse(const string& plate, const string& excludeVehicleId = "") const {
//        for (const auto& v : vehicles) {
//            if (v.getVehicleId() != excludeVehicleId && v.getLicensePlate() == plate) {
//                return true;
//            }
//        }
//        return false;
//    }
//    void loadUsersFromFile() {
//        cout << "[Boot] Reading 'users_database.txt'...\n";
//        ifstream file("users_database.txt");
//        if (!file.is_open()) { cout << "[Boot] No user DB found. Fresh start.\n"; return; }
//        string line; int loaded = 0;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); vector<string>t; string tok;
//            while (getline(ss, tok, ','))t.push_back(tok);
//            if (t.size() < 10)continue;
//            string role = t[0], sysId = t[1], nm = t[2], cn = t[3], addr = t[4],
//                em = t[5], ph = t[6], pw = t[9];
//            int ag = 0; try { ag = stoi(t[7]); }
//            catch (...) {}
//            Gender gn = genderFromString(t[8]);
//            shared_ptr<Person> p;
//            if (role == "Admin" && t.size() >= 14) {
//                double sal = 0; try { sal = stod(t[11]); }
//                catch (...) {}
//                AdminRole ar = adminRoleFromString(t[13]);
//                p = make_shared<Admin>(sysId, nm, cn, addr, em, ph, ag, gn, pw, t[10], sal, t[12], ar);
//            }
//            else if (role == "Driver" && t.size() >= 16) {
//                double sal = 0; try { sal = stod(t[11]); }
//                catch (...) {}
//                string av = (t.size() > 15) ? t[15] : "";
//                auto d = make_shared<Driver>(sysId, nm, cn, addr, em, ph, ag, gn, pw, t[10], sal, t[12], t[13]);
//                d->setStatus(t[14] == "1" ? DriverStatus::ON_ROUTE : DriverStatus::FREE);
//                d->setAssignedVehicle(av);
//                p = d;
//            }
//            else if (role == "Student" && t.size() >= 14) {
//                auto s = make_shared<Student>(sysId, nm, cn, addr, em, ph, ag, gn, pw, t[10], t[11], t[12]);
//                if (t[13] == "1") s->setPassStatus(true);
//                p = s;
//            }
//            if (p) { users[sysId] = p; loaded++; }
//        }
//        cout << "[Boot] Loaded " << loaded << " accounts.\n";
//    }
//
//    void savePendingRegistrationsToFile() {
//        ofstream file("pending_registrations.txt");
//        if (!file.is_open()) return;
//        for (const auto& r : pendingRegistrations)
//            file << r.to_string() << "\n";
//    }
//
//    void loadPendingRegistrationsToFile() {
//        ifstream file("pending_registrations.txt");
//        if (!file.is_open()) return;
//        pendingRegistrations.clear();
//        string line;
//        while (getline(file, line))
//            if (!line.empty())
//                pendingRegistrations.push_back(PendingRegistration::from_string(line));
//    }
//
//    void saveVehiclesToFile() {
//        ofstream file("vehicles_database.txt");
//        if (!file.is_open())return;
//        for (const auto& v : vehicles) {
//            file << v.getVehicleId() << "," << v.getLicensePlate() << ","
//                << vehicleTypeToString(v.getType()) << "," << v.getCapacity() << ","
//                << v.getOccupiedSeats() << "," << v.getCurrentDriverId() << ","
//                << v.getAssignedRouteId() << "," << v.getFuelEfficiency() << ","
//                << v.getFuelType();
//            if (v.isVAN()) {
//                string purp = v.getVanPurpose();
//                for (char& c : purp) if (c == ',') c = ';';
//                file << "," << purp << "," << v.getVanDailyMileage();
//            }
//            file << "\n";
//        }
//    }
//
//    void loadVehiclesFromFile() {
//        ifstream file("vehicles_database.txt");
//        if (!file.is_open())return;
//        vehicles.clear();
//        string line; int lineNum = 0;
//        while (getline(file, line)) {
//            ++lineNum;
//            if (line.empty())continue;
//            stringstream ss(line);
//            string vId, plate, typeStr, capStr, occStr, driverId, routeId, effStr, fType;
//            getline(ss, vId, ','); getline(ss, plate, ','); getline(ss, typeStr, ',');
//            getline(ss, capStr, ','); getline(ss, occStr, ','); getline(ss, driverId, ',');
//            getline(ss, routeId, ','); getline(ss, effStr, ','); getline(ss, fType, ',');
//            try {
//                int    cap = stoi(capStr), occ = stoi(occStr);
//                double eff = stod(effStr);
//                VehicleType vt = vehicleTypeFromString(typeStr);
//                if (vt == VehicleType::VAN) {
//                    string purp, dMileageStr;
//                    getline(ss, purp, ','); getline(ss, dMileageStr, ',');
//                    double dMileage = 0;
//                    try { dMileage = stod(dMileageStr); }
//                    catch (...) { cerr << "[Warn] VAN mileage malformed on line " << lineNum << "\n"; }
//                    Vehicle v(vId, plate, cap, eff, fType, purp, dMileage);
//                    v.setOccupiedSeats(occ); v.setDriver(driverId); v.setAssignedRouteId(routeId);
//                    vehicles.push_back(v);
//                }
//                else {
//                    Vehicle v(vId, plate, vt, cap, eff, fType);
//                    v.setOccupiedSeats(occ); v.setDriver(driverId); v.setAssignedRouteId(routeId);
//                    vehicles.push_back(v);
//                }
//            }
//            catch (...) {
//                cerr << "[Warn] Skipped malformed vehicle record on line " << lineNum << ": " << vId << "\n";
//            }
//        }
//    }
//
//    void saveRoutesToFile() {
//        ofstream file("routes_database.txt"); if (!file.is_open())return;
//        for (const auto& r : routes) {
//            file << "ROUTE," << r.getRouteId() << "," << r.getRouteName() << ","
//                << r.getApproxKilometer() << "\n";
//            for (const auto& s : r.getStops())
//                file << "STOP," << r.getRouteId() << "," << s.stopId << ","
//                << s.stopName << "," << s.coordinates << "," << s.arrivalTime << "\n";
//        }
//    }
//    void loadRoutesFromFile() {
//        ifstream file("routes_database.txt"); if (!file.is_open())return;
//        routes.clear(); string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string tag; getline(ss, tag, ',');
//            if (tag == "ROUTE") {
//                string rId, rName, kmStr, dummyResched;
//                getline(ss, rId, ','); getline(ss, rName, ',');
//                getline(ss, kmStr, ','); getline(ss, dummyResched, ',');
//                try {
//                    Route r(rId, rName, {}, stod(kmStr));
//                    routes.push_back(r);
//                }
//                catch (...) {}
//            }
//            else if (tag == "STOP") {
//                string rId, sId, sName, coord, arrTime;
//                getline(ss, rId, ','); getline(ss, sId, ','); getline(ss, sName, ',');
//                getline(ss, coord, ','); getline(ss, arrTime, ',');
//                auto rIt = find_if(routes.begin(), routes.end(),
//                    [&](const Route& r) {return r.getRouteId() == rId; });
//                if (rIt != routes.end()) rIt->addStop({ sId,sName,coord,arrTime });
//            }
//        }
//    }
//    void savePassesToFile() {
//        ofstream file("passes_database.txt"); if (!file.is_open())return;
//        for (const auto& p : passes)
//            file << p.getPassId() << "," << p.getStudentId() << "," << p.getRouteId() << ","
//            << p.getChosenStop() << "," << p.getIssueDate() << "," << p.getExpiryDate() << ","
//            << passStatusToString(p.getStatus()) << "\n";
//    }
//    void loadPassesFromFile() {
//        ifstream file("passes_database.txt"); if (!file.is_open())return;
//        passes.clear(); string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string pId, sId, rId, stop, iDate, eDate, statusStr;
//            getline(ss, pId, ','); getline(ss, sId, ','); getline(ss, rId, ',');
//            getline(ss, stop, ','); getline(ss, iDate, ','); getline(ss, eDate, ',');
//            getline(ss, statusStr, ',');
//            passes.push_back(TransportPass(pId, sId, rId, stop, iDate, eDate,
//                passStatusFromString(statusStr)));
//        }
//    }
//    void saveBillsToFile() {
//        ofstream file("bills_database.txt"); if (!file.is_open())return;
//        for (const auto& b : bills)
//            file << b.billId << "," << b.studentId << "," << b.amount << ","
//            << b.dueDate << "," << (b.isPaid ? "1" : "0") << "\n";
//    }
//    void loadBillsFromFile() {
//        ifstream file("bills_database.txt"); if (!file.is_open())return;
//        bills.clear(); string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string bId, sId, amtStr, due, paidStr;
//            getline(ss, bId, ','); getline(ss, sId, ','); getline(ss, amtStr, ',');
//            getline(ss, due, ','); getline(ss, paidStr, ',');
//            try {
//                Bill b; b.billId = bId; b.studentId = sId; b.amount = stod(amtStr);
//                b.dueDate = due; b.isPaid = (paidStr == "1"); bills.push_back(b);
//            }
//            catch (...) {}
//        }
//    }
//    void savePaymentsToFile() {
//        ofstream file("payments_database.txt"); if (!file.is_open())return;
//        for (const auto& pr : paymentRecords)
//            file << pr.paymentId << "," << pr.billId << "," << pr.amountPaid << ","
//            << pr.paymentDate << "," << pr.paymentMethod << "\n";
//    }
//    void loadPaymentsFromFile() {
//        ifstream file("payments_database.txt"); if (!file.is_open())return;
//        paymentRecords.clear(); string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string pId, bId, amtStr, date, method;
//            getline(ss, pId, ','); getline(ss, bId, ','); getline(ss, amtStr, ',');
//            getline(ss, date, ','); getline(ss, method, ',');
//            try {
//                PaymentRecord pr; pr.paymentId = pId; pr.billId = bId;
//                pr.amountPaid = stod(amtStr); pr.paymentDate = date;
//                pr.paymentMethod = method; paymentRecords.push_back(pr);
//            }
//            catch (...) {}
//        }
//    }
//    void saveWaitlistsToFile() {
//        ofstream file("waitlists_database.txt"); if (!file.is_open())return;
//        for (const auto& kv : routeWaitlists) {
//            auto tmpQ = kv.second;
//            while (!tmpQ.empty()) {
//                file << kv.first << "," << tmpQ.front() << "\n"; tmpQ.pop();
//            }
//        }
//    }
//    void loadWaitlistsFromFile() {
//        ifstream file("waitlists_database.txt"); if (!file.is_open())return;
//        routeWaitlists.clear(); string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string routeId, studentId;
//            if (getline(ss, routeId, ',') && getline(ss, studentId))
//                routeWaitlists[trim(routeId)].push(trim(studentId));
//        }
//    }
//    void saveTripLogsToFile() {
//        ofstream file("trip_logs.txt"); if (!file.is_open())return;
//        for (const auto& t : tripLogs) file << t.to_string() << "\n";
//    }
//    void loadTripLogsFromFile() {
//        ifstream file("trip_logs.txt"); if (!file.is_open())return;
//        tripLogs.clear(); string line;
//        while (getline(file, line))
//            if (!line.empty()) tripLogs.push_back(TripLog::from_string(line));
//    }
//    void savePetrolLogsToFile() {
//        ofstream file("petrol_logs_archive.txt"); if (!file.is_open())return;
//        for (const auto& p : petrolLogs) file << p.to_string() << "\n";
//    }
//    void loadPetrolLogsFromFile() {
//        ifstream file("petrol_logs_archive.txt"); if (!file.is_open())return;
//        petrolLogs.clear(); string line;
//        while (getline(file, line))
//            if (!line.empty()) petrolLogs.push_back(PetrolLog::from_string(line));
//    }
//    void saveMonthlyCapitalToFile() {
//        ofstream file("monthly_capital.txt"); if (!file.is_open())return;
//        for (const auto& kv : monthlyCapitals) {
//            const auto& mc = kv.second;
//            file << mc.month << "," << fixed << setprecision(2)
//                << mc.totalCapital << "," << mc.spentOnFuel << "\n";
//        }
//        file << "PETROL_PRICE," << petrolPricePerLitre << "\n";
//    }
//    void loadMonthlyCapitalFromFile() {
//        ifstream file("monthly_capital.txt"); if (!file.is_open())return;
//        string line;
//        while (getline(file, line)) {
//            if (line.empty())continue;
//            stringstream ss(line); string t1, t2, t3;
//            getline(ss, t1, ','); getline(ss, t2, ','); getline(ss, t3, ',');
//            if (t1 == "PETROL_PRICE") {
//                try { petrolPricePerLitre = stod(t2); }
//                catch (...) {}
//                continue;
//            }
//            try {
//                MonthlyCapital mc; mc.month = t1;
//                mc.totalCapital = stod(t2); mc.spentOnFuel = stod(t3);
//                monthlyCapitals[mc.month] = mc;
//            }
//            catch (...) {}
//        }
//    }
//
//    // ------------------------------------------------------------------
//    // SYSTEM PIPELINES
//    // ------------------------------------------------------------------
//
//    void sweepExpiredPasses() {
//        string today = DateUtil::getCurrentDate(); bool changed = false;
//        for (auto& p : passes) {
//            if (p.getStatus() == PassStatus::ACTIVE && p.getExpiryDate() < today) {
//                p.setStatus(PassStatus::EXPIRED); changed = true;
//                auto uIt = users.find(p.getStudentId());
//                if (uIt != users.end() && uIt->second->getRole() == "Student") {
//                    auto sp = dynamic_pointer_cast<Student>(uIt->second);
//                    if (sp) sp->setPassStatus(false);
//                }
//                string routeId = p.getRouteId(); bool seatFreed = false;
//                for (auto& v : vehicles) {
//                    if (v.getAssignedRouteId() == routeId && v.getOccupiedSeats() > 0) {
//                        v.decrementOccupiedSeats();
//                        cout << "[Sweep] Pass " << p.getPassId()
//                            << " expired. Seat freed on " << v.getVehicleId() << ".\n";
//                        seatFreed = true; break;
//                    }
//                }
//                if (!seatFreed)
//                    cout << "[Sweep] Pass " << p.getPassId() << " expired (no seat freed).\n";
//                processRouteWaitlist(routeId);
//            }
//        }
//        if (changed) { saveUsersToFile(); saveVehiclesToFile(); savePassesToFile(); }
//    }
//
//    bool registerUser(const shared_ptr<Person>& person) {
//        if (!ValidationUtil::isValidName(person->getName())) {
//            cout << "[Error] Name must contain letters only (spaces, hyphens, dots allowed).\n";
//            return false;
//        }
//        if (!ValidationUtil::isValidEmail(person->getEmail())) { cout << "[Error] Invalid email format.\n"; return false; }
//        if (!ValidationUtil::isValidPassword(person->getPassword())) { cout << "[Error] Password must be 8+ characters.\n"; return false; }
//        if (!ValidationUtil::isValidCNIC(person->getCNIC())) { cout << "[Error] Invalid CNIC. Use: XXXXX-XXXXXXX-X\n"; return false; }
//        if (!ValidationUtil::isValidPhone(person->getPhone())) { cout << "[Error] Invalid phone. Use: 03XX-XXXXXXX or +923XXXXXXXXX\n"; return false; }
//        if (!ValidationUtil::isValidAddress(person->getAddress())) { cout << "[Error] Address must be 5+ chars.\n"; return false; }
//        if (users.find(person->getSystemId()) != users.end()) {
//            cout << "[Error] System ID '" << person->getSystemId() << "' already in use.\n"; return false;
//        }
//        for (const auto& kv : users)
//            if (kv.second->getCNIC() == person->getCNIC()) {
//                cout << "[Error] CNIC already registered.\n"; return false;
//            }
//        if (person->getRole() == "Admin") {
//            auto a = dynamic_pointer_cast<Admin>(person);
//            if (a) {
//                for (const auto& kv : users) if (kv.second->getRole() == "Admin") {
//                    auto ea = dynamic_pointer_cast<Admin>(kv.second);
//                    if (ea && ea->getAdminRole() == a->getAdminRole() &&
//                        a->getAdminRole() != AdminRole::SUPER_ADMIN) {
//                        cout << "[Error] Only one " << adminRoleToString(a->getAdminRole()) << " allowed.\n";
//                        return false;
//                    }
//                }
//            }
//        }
//        if (auto emp = dynamic_pointer_cast<Employee>(person)) {
//            if (!ValidationUtil::isValidDesignation(emp->getDesignation())) { cout << "[Error] Designation must be 1-60 chars.\n"; return false; }
//            if (!ValidationUtil::isValidSalary(emp->getSalary())) { cout << "[Error] Salary must be Rs 15,000-500,000.\n"; return false; }
//            if (!ValidationUtil::isValidHireDate(emp->getHireDate())) { cout << "[Error] Hire date must be YYYY-MM-DD.\n"; return false; }
//        }
//        if (person->getRole() == "Driver") {
//            auto d = dynamic_pointer_cast<Driver>(person);
//            if (d && !ValidationUtil::isValidLicense(d->getLicenseNumber())) {
//                cout << "[Error] License must be 6+ alphanumeric chars.\n"; return false;
//            }
//        }
//        if (person->getRole() == "Student") {
//            auto s = dynamic_pointer_cast<Student>(person);
//            if (s) {
//                if (!ValidationUtil::isValidRollNumber(s->getRollNumber())) { cout << "[Error] Roll number must be 5+ chars.\n"; return false; }
//                if (!ValidationUtil::isValidSemester(s->getSemester())) { cout << "[Error] Semester must be 1-8.\n"; return false; }
//                if (!ValidationUtil::isValidDepartment(s->getDepartment())) { cout << "[Error] Department must contain letters only.\n"; return false; }
//            }
//        }
//        users[person->getSystemId()] = person; saveUsersToFile();
//        cout << "[System] Account created. System ID: " << person->getSystemId() << "\n";
//        return true;
//    }
//
//    void addVehicle(const Vehicle& vehicle) {
//        if (!ValidationUtil::isValidVehiclePlate(vehicle.getLicensePlate())) {
//            cout << "[Error] Invalid plate format. Use ABC-1234.\n"; return;
//        }
//        vehicles.push_back(vehicle);
//        saveVehiclesToFile();
//        cout << "[System] Vehicle registered: " << vehicle.getVehicleId() << "\n";
//        if (vehicle.isVAN()) vehicle.printVanDetails(petrolPricePerLitre);
//    }
//
//    bool removeVehicle(const string& vehicleId) {
//        auto vIt = find_if(vehicles.begin(), vehicles.end(),
//            [&](const Vehicle& v) {return v.getVehicleId() == vehicleId; });
//        if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return false; }
//        shared_ptr<Driver> coupled = nullptr;
//        for (const auto& kv : users) if (kv.second->getRole() == "Driver") {
//            auto d = dynamic_pointer_cast<Driver>(kv.second);
//            if (d && d->getAssignedVehicle() == vehicleId) { coupled = d; break; }
//        }
//        if (coupled && coupled->getStatus() == DriverStatus::ON_ROUTE) {
//            cout << "[Blocked] Vehicle " << vehicleId << " cannot be removed   driver is ON_ROUTE.\n";
//            return false;
//        }
//        if (coupled) {
//            coupled->setAssignedVehicle(""); saveUsersToFile();
//            cout << "[System] Driver " << coupled->getSystemId() << " uncoupled from " << vehicleId << ".\n";
//        }
//        vehicles.erase(vIt);
//        saveVehiclesToFile();
//        cout << "[System] Vehicle " << vehicleId << " removed.\n";
//        return true;
//    }
//
//    void addRoute(const Route& route) {
//        routes.push_back(route); saveRoutesToFile();
//        cout << "[System] Route registered: " << route.getRouteName() << "\n";
//    }
//
//    bool assignVehicleToRoute(const string& vehicleId, const string& routeId) {
//        auto vIt = find_if(vehicles.begin(), vehicles.end(),
//            [&](const Vehicle& v) {return v.getVehicleId() == vehicleId; });
//        if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return false; }
//        if (getEffectiveTripCount(vehicleId, TripDirection::ARRIVAL) >= 1) {
//            cout << "[Blocked] Vehicle already did ARRIVAL trip today.\n";
//            return false;
//        }
//        if (getEffectiveTripCount(vehicleId, TripDirection::DEPARTURE) >= 1) {
//            cout << "[Blocked] Vehicle already did DEPARTURE trip today.\n";
//            return false;
//        }
//        if (vIt->isVAN()) {
//            cout << "[Blocked] VANs are campus-only vehicles and cannot be assigned to\n"
//                << "          student routes. Use a BUS for route assignments.\n";
//            return false;
//        }
//        auto rIt = find_if(routes.begin(), routes.end(),
//            [&](const Route& r) { return r.getRouteId() == routeId; });
//        if (rIt == routes.end()) { cout << "[Error] Route not found.\n"; return false; }
//        if (!vIt->getAssignedRouteId().empty() && vIt->getAssignedRouteId() != routeId) {
//            cout << "[Blocked] Vehicle " << vehicleId << " is already assigned to Route "
//                << vIt->getAssignedRouteId() << ".\n"
//                << "          Unassign it first (option 16).\n";
//            return false;
//        }
//        if (vIt->getAssignedRouteId() == routeId) {
//            cout << "[Info] Vehicle " << vehicleId << " is already on Route " << routeId << ".\n";
//            return true;
//        }
//        vIt->setAssignedRouteId(routeId); saveVehiclesToFile();
//        return true;
//    }
//
//    void assignDriverToVehicle(const string& driverId, const string& vehicleId) {
//        auto dIt = users.find(driverId);
//        if (dIt == users.end() || dIt->second->getRole() != "Driver") {
//            cout << "[Error] Driver " << driverId << " not found.\n"; return;
//        }
//        auto driver = dynamic_pointer_cast<Driver>(dIt->second);
//        if (!driver) return;
//        auto vIt = find_if(vehicles.begin(), vehicles.end(),
//            [&](const Vehicle& v) {return v.getVehicleId() == vehicleId; });
//        if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return; }
//        if (!vIt->getCurrentDriverId().empty()) {
//            cout << "[Error] Vehicle already has driver: " << vIt->getCurrentDriverId() << "\n"; return;
//        }
//        if (!driver->getAssignedVehicle().empty()) {
//            cout << "[Error] Driver already assigned to: " << driver->getAssignedVehicle() << "\n"; return;
//        }
//        vIt->setDriver(driverId); driver->setAssignedVehicle(vehicleId);
//        saveUsersToFile(); saveVehiclesToFile();
//        cout << "[System] Coupled Driver " << driverId << " with Vehicle " << vehicleId << ".\n";
//    }
//
//    void unassignDriverFromVehicle(const string& driverId) {
//        auto dIt = users.find(driverId);
//        if (dIt == users.end() || dIt->second->getRole() != "Driver") {
//            cout << "[Error] Driver not found.\n"; return;
//        }
//        auto driver = dynamic_pointer_cast<Driver>(dIt->second);
//        if (!driver || driver->getAssignedVehicle().empty()) {
//            cout << "[Error] Driver has no vehicle assigned.\n"; return;
//        }
//        if (driver->getStatus() == DriverStatus::ON_ROUTE) {
//            cout << "[Blocked] Cannot unassign driver while ON_ROUTE.\n"; return;
//        }
//        string vId = driver->getAssignedVehicle();
//        for (auto& v : vehicles) if (v.getVehicleId() == vId) { v.setDriver(""); break; }
//        driver->setAssignedVehicle("");
//        saveUsersToFile(); saveVehiclesToFile();
//        cout << "[System] Driver " << driverId << " uncoupled from vehicle " << vId << ".\n";
//    }
//
//    int getRemainingSeatsForRoute(const string& routeId)const {
//        int total = 0; bool found = false;
//        for (const auto& v : vehicles)
//            if (v.getAssignedRouteId() == routeId) { total += v.getRemainingSeats(); found = true; }
//        return found ? total : 0;
//    }
//
//    bool isStopOnRoute(const string& routeId, const string& stopName)const {
//        for (const auto& r : routes) if (r.getRouteId() == routeId)
//            for (const auto& s : r.getStops()) if (s.stopName == stopName) return true;
//        return false;
//    }
//
//    int getTodayTripCount(const string& vehicleId, TripDirection direction)const {
//        string today = DateUtil::getCurrentDate(); int count = 0;
//        for (const auto& t : tripLogs)
//            if (t.vehicleId == vehicleId && t.date == today && t.direction == direction) count++;
//        return count;
//    }
//
//    int getEffectiveTripCount(const string& vehicleId, TripDirection direction) const {
//        return getTodayTripCount(vehicleId, direction);
//    }
//
//    int getTodayTotalEffectiveTrips(const string& vehicleId) const {
//        return getTodayTotalTrips(vehicleId);
//    }
//
//    int getTodayTotalTrips(const string& vehicleId)const {
//        string today = DateUtil::getCurrentDate(); int count = 0;
//        for (const auto& t : tripLogs)
//            if (t.vehicleId == vehicleId && t.date == today) count++;
//        return count;
//    }
//
//    bool dispatchTrip(const string& vehicleId, TripDirection direction) {
//        auto vIt = find_if(vehicles.begin(), vehicles.end(),
//            [&](const Vehicle& v) {return v.getVehicleId() == vehicleId; });
//        if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return false; }
//        if (getEffectiveTripCount(vehicleId, TripDirection::ARRIVAL) >= 1) {
//            cout << "[Blocked] Vehicle already did ARRIVAL trip today.\n";
//            return false;
//        }
//        if (getEffectiveTripCount(vehicleId, TripDirection::DEPARTURE) >= 1) {
//            cout << "[Blocked] Vehicle already did DEPARTURE trip today.\n";
//            return false;
//        }
//        if (vIt->isVAN()) {
//            cout << "[Blocked] VANs are campus-only vehicles and cannot be assigned to\n"
//                << "          student routes. Use a BUS for route assignments.\n";
//            return false;
//        }
//        auto rIt = find_if(routes.begin(), routes.end(),
//            [&](const Route& r) { return r.getRouteId() == vehicleId; });
//        if (rIt == routes.end()) { cout << "[Error] Route not found.\n"; return false; }
        
        // Check if the vehicle is assigned to the route
//        if (vIt->getAssignedRouteId() != vehicleId) {
//            cout << "[Error] Vehicle " << vehicleId << " is not assigned to the route.\n";
//            return false;
//        }
//
//        double routeKm = rIt->getApproxKilometer();
//        double litres = routeKm / vIt->getFuelEfficiency();
//        double fuelCost = litres * petrolPricePerLitre;
//
//        TripLog tl;
//        tl.tripId = "TRIP-" + to_string(gCounters.tripNext++);
//        gCounters.saveToFile();
//        tl.vehicleId = vehicleId;
//        tl.routeId = vehicleId;
//        tl.date = DateUtil::getCurrentDate();
//        tl.direction = direction;
//        tl.routeKm = routeKm;
//        tl.fuelUsedLiters = litres;
//        tl.fuelCostEstimate = fuelCost;
//        tripLogs.push_back(tl);
//        saveTripLogsToFile();
//
//        string month = DateUtil::getCurrentYearMonth();
//        if (monthlyCapitals.find(month) != monthlyCapitals.end()) {
//            auto& mc = monthlyCapitals[month];
//            if (mc.remaining() < fuelCost)
//                cout << "[Finance Alert] WARNING: Insufficient capital! Rs "
//                << fixed << setprecision(2) << mc.remaining()
//                << " remaining vs Rs " << fuelCost << "   Overdraft.\n";
//            mc.spentOnFuel += fuelCost;
//            saveMonthlyCapitalToFile();
//            cout << "[Finance] Rs " << fixed << setprecision(2) << fuelCost
//                << " deducted. Remaining: Rs " << mc.remaining() << "\n";
//        }
//        else {
//            cout << "[Finance Warning] No capital set for " << month
//                << ". Cost Rs " << fixed << setprecision(2) << fuelCost << " not deducted.\n";
//        }
//
//        cout << "[Trip] " << tripDirectionToString(direction)
//            << " logged | Vehicle: " << vehicleId
//            << " | " << (vIt->isVAN() ? "Campus" : "Route: " + routeId)
//            << " | " << routeKm << " km"
//            << " | Fuel: " << fixed << setprecision(2) << litres
//            << " L | Cost: Rs " << fuelCost << "\n";
//        return true;
//    }
//
//    void viewDailyTripSummary(const string& vehicleId)const {
//        string today = DateUtil::getCurrentDate();
//        cout << "\n--- TRIP SUMMARY: " << vehicleId << " (" << today << ") ---\n";
//        double totalKm = 0, totalL = 0, totalCost = 0; bool any = false;
//        for (const auto& t : tripLogs) {
//            if (t.vehicleId == vehicleId && t.date == today) {
//                cout << "  " << t.tripId << " | " << tripDirectionToString(t.direction)
//                    << " | " << t.routeId << " | " << t.routeKm << " km | "
//                    << fixed << setprecision(2) << t.fuelUsedLiters
//                    << " L | Rs " << t.fuelCostEstimate << "\n";
//                totalKm += t.routeKm; totalL += t.fuelUsedLiters;
//                totalCost += t.fuelCostEstimate; any = true;
//            }
//        }
//        if (!any) { cout << "  No trips today.\n"; return; }
//        cout << "  Total Km: " << totalKm << " | Fuel: " << totalL
//            << " L | Cost: Rs " << totalCost << "\n";
//    }
//
//    void setMonthlyCapital(double amount) {
//        if (amount <= 0.0 || amount > 500000.0) {
//            cout << "[Error] Capital must be a positive value up to Rs 500,000.\n"; return;
//        }
//        string month = DateUtil::getCurrentYearMonth();
//        if (monthlyCapitals.find(month) != monthlyCapitals.end()) {
//            cout << "[Warning] Capital for " << month << " already set to Rs "
//                << fixed << setprecision(2) << monthlyCapitals[month].totalCapital << ".\n";
//            string confirm = getRobustInput("  Override? (y/n): ");
//            if (confirm != "y" && confirm != "Y") { cout << "[Cancelled]\n"; return; }
//            double spent = monthlyCapitals[month].spentOnFuel;
//            monthlyCapitals[month] = { month, amount, spent };
//        }
//        else {
//            monthlyCapitals[month] = { month, amount, 0.0 };
//        }
//        saveMonthlyCapitalToFile();
//        cout << "[Finance] Capital for " << month << " set to Rs "
//            << fixed << setprecision(2) << amount << "\n";
//    }
//
//    void viewMonthlyCapitalStatus()const {
//        string month = DateUtil::getCurrentYearMonth();
//        const auto it = monthlyCapitals.find(month);
//        if (it == monthlyCapitals.end()) {
//            cout << "[Finance] No capital set for " << month << ".\n"; return;
//        }
//        const auto& mc = it->second;
//        cout << "\n=========================================\n"
//            << "   MONTHLY CAPITAL STATUS (" << month << ")\n"
//            << "=========================================\n"
//            << "  Allocated : Rs " << fixed << setprecision(2) << mc.totalCapital << "\n"
//            << "  Fuel Spent: Rs " << mc.spentOnFuel << "\n"
//            << "  Remaining : Rs " << mc.remaining() << "\n"
//            << "  Petrol/L  : Rs " << petrolPricePerLitre << "\n"
//            << "=========================================\n";
//    }
//
//    void updatePetrolPrice(double price) {
//        if (price < 50.0 || price > 1000.0) {
//            cout << "[Error] Petrol price must be Rs 50-1000/L.\n"; return;
//        }
//        petrolPricePerLitre = price; saveMonthlyCapitalToFile();
//        cout << "[Finance] Petrol price updated to Rs "
//            << fixed << setprecision(2) << price << "/L.\n";
//    }
//
//    void viewVehicleFuelCostToday(const string& vehicleId)const {
//        string today = DateUtil::getCurrentDate();
//        double totalL = 0, totalCost = 0; int trips = 0;
//        for (const auto& t : tripLogs)
//            if (t.vehicleId == vehicleId && t.date == today) {
//                totalL += t.fuelUsedLiters; totalCost += t.fuelCostEstimate; trips++;
//            }
//        double eff = 0;
//        for (const auto& v : vehicles)
//            if (v.getVehicleId() == vehicleId) { eff = v.getFuelEfficiency(); break; }
//        cout << "\n--- FUEL COST: " << vehicleId << " (" << today << ") ---\n"
//            << "  Trips: " << trips << " | Efficiency: " << eff << " km/L"
//            << " | Petrol: Rs " << fixed << setprecision(2) << petrolPricePerLitre << "/L\n"
//            << "  Total Fuel: " << totalL << " L | Total Cost: Rs " << totalCost << "\n";
//    }
//
//    void requestPass(const string& studentId, const string& routeId, const string& stopName) {
//        sweepExpiredPasses();
//        bool routeExists = any_of(routes.begin(), routes.end(),
//            [&](const Route& r) { return r.getRouteId() == routeId; });
//        if (!routeExists) { cout << "[Error] Route '" << routeId << "' does not exist.\n"; return; }
//        if (!isStopOnRoute(routeId, stopName)) {
//            cout << "[Error] Stop '" << stopName << "' not on route " << routeId << ".\n"; return;
//        }
//        const Vehicle* assignedVan = nullptr;
//        for (const auto& v : vehicles)
//            if (v.isVAN() && v.getAssignedRouteId() == routeId
//                && v.getCapacity() > 0 && v.getVanDailyMileage() > 0.0) {
//                assignedVan = &v; break;
//            }
//        bool routeHasVan = (assignedVan != nullptr);
//        if (routeHasVan) {
//            auto uIt = users.find(studentId);
//            if (uIt != users.end() && uIt->second->getRole() == "Student") {
//                auto sp = dynamic_pointer_cast<Student>(uIt->second);
//                if (sp) {
//                    int sem = 0;
//                    try { sem = stoi(sp->getSemester()); }
//                    catch (...) {}
//                    if (sem > 8) {
//                        cout << "[Blocked] VAN routes are restricted to students in Semester 1-8.\n"
//                            << "          Your semester: " << sp->getSemester() << "\n";
//                        return;
//                    }
//                }
//            }
//        }
//        bool hasLivePass = false;
//        for (const auto& p : passes)
//            if (p.getStudentId() == studentId &&
//                (p.getStatus() == PassStatus::PENDING_PAYMENT ||
//                    p.getStatus() == PassStatus::ACTIVE ||
//                    p.getStatus() == PassStatus::WAITLISTED)) {
//                hasLivePass = true; break;
//            }
//        if (hasLivePass) {
//            cout << "[Blocked] You already have an active, pending, or waitlisted pass.\n"
//                << "          Use 'Apply for Pass Change' (option 3) to switch routes.\n";
//            return;
//        }
//        auto uIt = users.find(studentId);
//        if (uIt != users.end() && uIt->second->getRole() == "Student") {
//            auto sp = dynamic_pointer_cast<Student>(uIt->second);
//            if (sp) sp->setPassStatus(false);
//        }
//        string passId = "PASS-" + to_string(gCounters.billNext);
//        string billId = "BILL-" + to_string(gCounters.billNext++);
//        gCounters.saveToFile();
//        double billAmount = 200.0;
//        string surchargeNote = "";
//        if (routeHasVan && assignedVan != nullptr) {
//            double estDailyFuel = assignedVan->getVanEstimatedDailyFuelCost(petrolPricePerLitre);
//            int cap = assignedVan->getCapacity();
//            double surcharge = static_cast<double>(
//                static_cast<int>((estDailyFuel * 20.0) / cap + 0.5));
//            billAmount += surcharge;
//            ostringstream sn;
//            sn << fixed << setprecision(2)
//                << " (Base Rs 200.00 + VAN fuel surcharge Rs " << surcharge
//                << " = Rs " << billAmount << ")";
//            surchargeNote = sn.str();
//        }
//        passes.emplace_back(passId, studentId, routeId, stopName);
//        bills.push_back({ billId, studentId, billAmount, "2026-06-30", false });
//        savePassesToFile(); saveBillsToFile();
//        cout << "[System] Pass request submitted. Invoice " << billId
//            << " for Rs " << fixed << setprecision(2) << billAmount
//            << " generated." << surchargeNote
//            << "\nPay at Finance Console to activate.\n";
//    }
//
//    // -----------------------------------------------------------------------
//    // FIX 2: Pass Change   no double-charging for already-paid (WAITLISTED) passes.
//    //
//    // A student who is WAITLISTED has already paid (financeClearPass cleared their
//    // bill before putting them on the waitlist).  When they switch routes we must
//    // NOT issue a new bill.  Instead we:
//    //   (a) cancel the old pass / free the waitlist slot as before, and
//    //   (b) create a new pass that is immediately set to PENDING_PAYMENT but mark
//    //       the corresponding bill as already paid (isPaid=true) so the Finance
//    //       Manager can promote it without asking for a second payment.
//    //
//    // For ACTIVE passes the same logic applies   the student already paid.
//    // A fresh bill (isPaid=false) is only appropriate when the student had only a
//    // PENDING_PAYMENT pass (they never actually paid).
//
//    void requestPassChange(const string& studentId, const string& newRouteId,
//        const string& newStopName) {
//        sweepExpiredPasses();
//        TransportPass* livePass = nullptr;
//        for (auto& p : passes)
//            if (p.getStudentId() == studentId &&
//                (p.getStatus() == PassStatus::ACTIVE ||
//                    p.getStatus() == PassStatus::WAITLISTED)) {
//                livePass = &p; break;
//            }
//        if (!livePass) {
//            cout << "[Info] No active/waitlisted pass found. Submitting fresh request.\n";
//            requestPass(studentId, newRouteId, newStopName);
//            return;
//        }
//        if (livePass->getRouteId() == newRouteId) {
//            cout << "[Info] You are already assigned to route " << newRouteId << ".\n"; return;
//        }
//        cout << "[Change Request] This will cancel your current pass on route "
//            << livePass->getRouteId() << " and request a new one on route "
//            << newRouteId << ".\n";
//        int seatsAvailable = getRemainingSeatsForRoute(newRouteId);
//        if (seatsAvailable == 0)
//            cout << "[Info] New route " << newRouteId << " has no seats   you will be waitlisted.\n";
//        else
//            cout << "[Info] New route " << newRouteId << " has " << seatsAvailable << " seat(s).\n";
//        string confirm = getRobustInput("Confirm route change? (y/n): ");
//        if (confirm != "y" && confirm != "Y") { cout << "[Cancelled]\n"; return; }
//
//        // Remember the old status BEFORE cancelling so we can decide billing below.
//        PassStatus oldStatus = livePass->getStatus();
//        string oldRouteId = livePass->getRouteId();
//
//        if (oldStatus == PassStatus::ACTIVE) {
//            for (auto& v : vehicles)
//                if (v.getAssignedRouteId() == oldRouteId && v.getOccupiedSeats() > 0) {
//                    v.decrementOccupiedSeats();
//                    cout << "[Change] Seat freed on " << v.getVehicleId()
//                        << " (old route " << oldRouteId << ").\n";
//                    break;
//                }
//        }
//        else {
//            // WAITLISTED   remove from waitlist queue
//            auto wIt = routeWaitlists.find(oldRouteId);
//            if (wIt != routeWaitlists.end()) {
//                queue<string> newQ; auto tmpQ = wIt->second;
//                while (!tmpQ.empty()) {
//                    if (tmpQ.front() != studentId) newQ.push(tmpQ.front());
//                    tmpQ.pop();
//                }
//                wIt->second = newQ;
//            }
//        }
//        livePass->setStatus(PassStatus::EXPIRED);
//        auto uIt = users.find(studentId);
//        if (uIt != users.end() && uIt->second->getRole() == "Student") {
//            auto sp = dynamic_pointer_cast<Student>(uIt->second);
//            if (sp) sp->setPassStatus(false);
//        }
//        saveVehiclesToFile(); savePassesToFile(); saveUsersToFile(); saveWaitlistsToFile();
//        cout << "[Change] Old pass cancelled. Opening old route's waitlist...\n";
//        processRouteWaitlist(oldRouteId);
//
//        // ---- Route/stop validation before we touch billing ----
//        bool routeExists = any_of(routes.begin(), routes.end(),
//            [&](const Route& r) { return r.getRouteId() == newRouteId; });
//        if (!routeExists) { cout << "[Error] Route '" << newRouteId << "' does not exist.\n"; return; }
//        if (!isStopOnRoute(newRouteId, newStopName)) {
//            cout << "[Error] Stop '" << newStopName << "' not on route " << newRouteId << ".\n"; return;
//        }
//
//        // FIX 2: Because the student has already paid (ACTIVE or WAITLISTED means
//        // financeClearPass was called), we create the new pass + bill but
//        // immediately mark the bill as paid and record the transfer as a
//        // zero-cost credit so the Finance Manager only needs to confirm the
//        // activation   no new charge is collected.
//        string passId = "PASS-" + to_string(gCounters.billNext);
//        string billId = "BILL-" + to_string(gCounters.billNext++);
//        gCounters.saveToFile();
//
//        passes.emplace_back(passId, studentId, newRouteId, newStopName);
//        // Mark bill paid=true   student already paid for their previous pass.
//        bills.push_back({ billId, studentId, 0.0, "2026-06-30", true });
//
//        // Record a Rs 0 transfer so the payment ledger stays coherent.
//        string payId = "PAY-" + to_string(gCounters.payNext++);
//        gCounters.saveToFile();
//        paymentRecords.push_back({ payId, billId, 0.0,
//            DateUtil::getCurrentDate(), "Route Transfer (pre-paid)" });
//
//        savePassesToFile(); saveBillsToFile(); savePaymentsToFile();
//        cout << "[System] Route change recorded. No additional charge   previous payment"
//            << " transferred.\n"
//            << "         New pass " << passId << " is pending Finance activation"
//            << " (Pass ID: " << passId << ").\n"
//            << "         Present Pass ID to Finance Manager to activate seat on "
//            << newRouteId << ".\n";
//    }
//    void financeClearPass(const string& passId) {
//        auto pIt = find_if(passes.begin(), passes.end(),
//            [&](const TransportPass& p) {return p.getPassId() == passId; });
//        if (pIt == passes.end()) { cout << "[Error] Pass not found.\n"; return; }
//        if (pIt->getStatus() != PassStatus::PENDING_PAYMENT) {
//            cout << "[Error] Pass is not pending payment (status: "
//                << passStatusToString(pIt->getStatus()) << ").\n"; return;
//        }
//
//        // Extract the unique numeric suffix from the Pass ID (e.g., "2001" from "PASS-2001")
//        string passSuffix = "";
//        size_t dashPos = passId.find('-');
//        if (dashPos != string::npos) {
//            passSuffix = passId.substr(dashPos + 1);
//        }
//        string targetBillId = "BILL-" + passSuffix;
//
//        // Match the exact corresponding bill for this specific pass
//        auto bIt = find_if(bills.begin(), bills.end(), [&](const Bill& b) {
//            return b.billId == targetBillId && b.studentId == pIt->getStudentId();
//            });
//
//        if (bIt == bills.end()) {
//            cout << "[Error] Corresponding bill (" << targetBillId << ") not found. Pass activation denied.\n";
//            return;
//        }
//
//        // Process payment if the matched bill is not already paid
//        if (!bIt->isPaid) {
//            bIt->isPaid = true;
//            string payId = "PAY-" + to_string(gCounters.payNext++);
//            gCounters.saveToFile();
//            paymentRecords.push_back({ payId, bIt->billId, bIt->amountPaid,
//                DateUtil::getCurrentDate(), "University Cashier" });
//        }
//
//        string targetRoute = pIt->getRouteId();
//        Vehicle* targetVehicle = nullptr;
//        for (auto& v : vehicles)
//            if (v.getAssignedRouteId() == targetRoute && v.getOccupiedSeats() > 0) {
//                targetVehicle = &v; break;
//            }
//        if (targetVehicle) {
//            targetVehicle->incrementOccupiedSeats();
//            pIt->activate(DateUtil::getCurrentDate(), DateUtil::calculateExpiryDate(180));
//            string sSem = "", sDept = "", vanInfo = "";
//            auto uIt = users.find(pIt->getStudentId());
//            if (uIt != users.end() && uIt->second->getRole() == "Student") {
//                auto sp = dynamic_pointer_cast<Student>(uIt->second);
//                if (sp) {
//                    sp->setPassStatus(true);
//                    sSem = sp->getSemester(); sDept = sp->getDepartment();
//                }
//            }
//            if (targetVehicle->isVAN()) {
//                ostringstream vi;
//                vi << "VAN " << targetVehicle->getVehicleId()
//                    << " | Daily Mileage: " << targetVehicle->getVanDailyMileage() << " km";
//                vanInfo = vi.str();
//                cout << "[VAN] Student assigned to VAN. Daily mileage: "
//                    << targetVehicle->getVanDailyMileage() << " km"
//                    << " | Est. fuel cost/trip: Rs "
//                    << fixed << setprecision(2)
//                    << targetVehicle->getVanEstimatedDailyFuelCost(petrolPricePerLitre) << "\n";
//            }
//            cout << "[System] Payment cleared! Seat reserved on "
//                << targetVehicle->getVehicleId() << ". Pass " << passId << " ACTIVE.\n";
//            PDFGenerator::generatePassPDF(pIt->getPassId(), pIt->getStudentId(),
//                pIt->getRouteId(), pIt->getExpiryDate(), sSem, sDept, vanInfo);
//        }
//        else {
//            pIt->setStatus(PassStatus::WAITLISTED);
//            routeWaitlists[targetRoute].push(pIt->getStudentId());
//            cout << "[System] Payment cleared. Route " << targetRoute
//                << " is full   Student waitlisted.\n";
//        }
//        saveUsersToFile(); saveVehiclesToFile(); savePassesToFile();
//        saveBillsToFile(); savePaymentsToFile(); saveWaitlistsToFile();
//    }
//    void cancelPass(const string& passId) {
//        auto pIt = find_if(passes.begin(), passes.end(),
//            [&](const TransportPass& p) {return p.getPassId() == passId; });
//        if (pIt == passes.end()) { cout << "[Error] Pass not found.\n"; return; }
//        if (pIt->getStatus() != PassStatus::ACTIVE && pIt->getStatus() != PassStatus::WAITLISTED) {
//            cout << "[Error] Only ACTIVE or WAITLISTED passes can be cancelled.\n"; return;
//        }
//        string routeId = pIt->getRouteId();
//        if (pIt->getStatus() == PassStatus::ACTIVE) {
//            for (auto& v : vehicles)
//                if (v.getAssignedRouteId() == routeId && v.getOccupiedSeats() > 0) {
//                    v.decrementOccupiedSeats();
//                    cout << "[Cancel] Seat freed on " << v.getVehicleId() << ".\n"; break;
//                }
//        }
//        else {
//            auto wIt = routeWaitlists.find(routeId);
//            if (wIt != routeWaitlists.end()) {
//                queue<string> newQ; auto tmpQ = wIt->second;
//                while (!tmpQ.empty()) {
//                    if (tmpQ.front() != pIt->getStudentId()) newQ.push(tmpQ.front());
//                    tmpQ.pop();
//                }
//                wIt->second = newQ;
//            }
//        }
//        pIt->setStatus(PassStatus::EXPIRED);
//        auto uIt = users.find(pIt->getStudentId());
//        if (uIt != users.end() && uIt->second->getRole() == "Student") {
//            auto sp = dynamic_pointer_cast<Student>(uIt->second);
//            if (sp) sp->setPassStatus(false);
//        }
//        cout << "[System] Pass " << passId << " cancelled and marked EXPIRED.\n";
//        savePassesToFile(); saveVehiclesToFile(); saveUsersToFile(); saveWaitlistsToFile();
//        processRouteWaitlist(routeId);
//    }
//};
//
//// ============================================================================
//// HELPERS
//// ============================================================================
//bool hasAdminWithRole(const AppController& ctrl, AdminRole role) {
//    for (const auto& kv : ctrl.users) if (kv.second->getRole() == "Admin") {
//        auto a = dynamic_pointer_cast<Admin>(kv.second);
//        if (a && a->getAdminRole() == role) return true;
//    }
//    return false;
//}
//bool hasRole(const AppController& ctrl, const string& role) {
//    for (const auto& kv : ctrl.users) if (kv.second->getRole() == role) return true;
//    return false;
//}
//
//
//// ============================================================================
//// INPUT HELPERS
//// ============================================================================
//string inputName(const string& label) {
//    while (true) {
//        string v = getRobustInput(label);
//        if (ValidationUtil::isValidName(v)) return sanitizeCsv(v);
//        cout << "[Error] Name must contain letters only (spaces, hyphens, dots allowed).\n";
//    }
//}
//string inputEmail(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidEmail(v)) return v; cout << "[Error] Invalid email.\n"; }
//}
//string inputPassword(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidPassword(v)) return v; cout << "[Error] 8+ characters.\n"; }
//}
//string inputCNIC(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidCNIC(v)) return v; cout << "[Error] Format: XXXXX-XXXXXXX-X\n"; }
//}
//string inputPhone(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidPhone(v)) return v; cout << "[Error] Format: 03XX-XXXXXXX or +923XXXXXXXXX\n"; }
//}
//int inputAge(const string& label) {
//    while (true) {
//        string v = getRobustInput(label); v = cleanNumericString(v);
//        try { int a = stoi(v); if (ValidationUtil::isValidAge(a)) return a; }
//        catch (...) {}
//        cout << "[Error] Age 16-25 required for students.\n";
//    }
//}
//int inputAgeEmployee(const string& label) {
//    while (true) {
//        string v = getRobustInput(label); v = cleanNumericString(v);
//        try { int a = stoi(v); if (ValidationUtil::isValidAgeEmployee(a)) return a; }
//        catch (...) {}
//        cout << "[Error] Age 25-80 required for this role.\n";
//    }
//}
//Gender inputGender(const string& label) {
//    while (true) {
//        string v = getRobustInput(label + " (1=Male, 2=Female, 3=Other): ");
//        if (v == "1") return Gender::MALE;
//        if (v == "2") return Gender::FEMALE;
//        if (v == "3") return Gender::OTHER;
//        cout << "[Error] Enter 1, 2, or 3.\n";
//    }
//}
//string inputAddress(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidAddress(v)) return sanitizeCsv(v); cout << "[Error] Min 5 chars.\n"; }
//}
//string inputDesignation(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidDesignation(v)) return sanitizeCsv(v); cout << "[Error] 1-60 chars.\n"; }
//}
//double inputSalary(const string& label) {
//    while (true) {
//        string v = getRobustInput(label + " (Rs 15,000-500,000): ");
//        v = cleanNumericString(v);
//        try { double s = stod(v); if (ValidationUtil::isValidSalary(s)) return s; }
//        catch (...) {}
//        cout << "[Error] Salary must be between Rs 15,000 and Rs 500,000.\n";
//    }
//}
//string inputHireDate(const string& label) {
//    while (true) { string v = getRobustInput(label + " (YYYY-MM-DD): "); if (ValidationUtil::isValidHireDate(v)) return v; cout << "[Error] Format: YYYY-MM-DD.\n"; }
//}
//string inputLicense(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidLicense(v)) return v; cout << "[Error] 6+ alphanumeric.\n"; }
//}
//string inputRollNumber(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidRollNumber(v)) return v; cout << "[Error] Min 5 chars.\n"; }
//}
//string inputSemester(const string& label) {
//    while (true) {
//        string v = getRobustInput(label + " (1-8): ");
//        v = cleanNumericString(v);
//        if (ValidationUtil::isValidSemester(v)) return v;
//        cout << "[Error] Semester must be between 1 and 8.\n";
//    }
//}
//string inputDepartment(const string& label) {
//    while (true) { string v = getRobustInput(label); if (ValidationUtil::isValidDepartment(v)) return sanitizeCsv(v); cout << "[Error] Letters only.\n"; }
//}
//string inputVanPurpose() {
//    while (true) {
//        string v = getRobustInput("VAN Purpose / Use Case (5-120 chars): ");
//        if (ValidationUtil::isValidVanPurpose(v)) return sanitizeCsv(v);
//        cout << "[Error] Purpose must be 5-120 characters.\n";
//    }
//}
//double inputVanDailyMileage() {
//    while (true) {
//        string v = getRobustInput("Daily Mileage within University (1-6 km): ");
//        v = cleanNumericString(v);
//        try { double d = stod(v); if (ValidationUtil::isValidVanDailyKm(d)) return d; }
//        catch (...) {}
//        cout << "[Error] Must be 1-6 km.\n";
//    }
//}
//
//string inputStopId(const string& label) {
//    while (true) {
//        string v = getRobustInput(label);
//        if (ValidationUtil::isValidStopId(v)) return v;
//        cout << "[Error] Stop ID must be at least 2 characters long and must contain both "
//            << "letters and digits (no spaces, hyphens, or special characters, e.g., S01, ST2).\n";
//    }
//}
//
//string inputRouteId(const string& label) {
//    while (true) {
//        string v = getRobustInput(label);
//        if (ValidationUtil::isValidRouteId(v)) return v;
//        cout << "[Error] Route ID must be alphanumeric only, minimum 2 characters (e.g. R1 or RT01).\n";
//    }
//}
//string inputCoordinates(const string& label) {
//    while (true) {
//        string v = getRobustInput(label +
//            " (lat,lon e.g. 31.5204,74.3587 OR descriptive name >= 5 chars, no commas): ");
//        if (ValidationUtil::isValidCoordinates(v)) return sanitizeCsv(v);
//        cout << "[Error] Enter lat,lon (e.g. 31.52,74.35) or a location description "
//            << "of at least 5 characters without commas.\n";
//    }
//}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    gCounters.loadFromFile();

    AppController controller;
    controller.loadUsersFromFile();
    controller.loadPendingRegistrationsToFile();
    controller.loadVehiclesFromFile();
    controller.loadRoutesFromFile();
    controller.loadPassesFromFile();
    controller.loadBillsFromFile();
    controller.loadPaymentsFromFile();
    controller.loadWaitlistsFromFile();
    controller.loadMonthlyCapitalFromFile();
    controller.loadTripLogsFromFile();
    controller.loadPetrolLogsFromFile();
    controller.sweepExpiredPasses();

    if (!hasAdminWithRole(controller, AdminRole::SUPER_ADMIN)) {
        cout << "\n==================================================\n"
            << "   FIRST-TIME SYSTEM INITIALIZATION & SETUP       \n"
            << "==================================================\n"
            << " No Super Admin detected. Configure the primary account:\n\n";
        string nm = inputName("Full Name: ");
        string cn = inputCNIC("CNIC (XXXXX-XXXXXXX-X): ");
        string addr = inputAddress("Address (min 5 chars): ");
        string em = inputEmail("Email: ");
        string ph = inputPhone("Phone (03XX-XXXXXXX): ");
        int    ag = inputAgeEmployee("Age (25-80): ");
        string pw = inputPassword("Password (8+ chars): ");
        string desig = inputDesignation("Designation (e.g. Head of Transport): ");
        double sal = inputSalary("Salary");
        string hire = inputHireDate("Hire Date (like 2020-09-09) ");
        string empId = Admin::generateEmployeeId();
        auto firstAdmin = make_shared<Admin>(empId, nm, cn, addr, em, ph, ag, Gender::MALE,
            pw, desig, sal, hire, AdminRole::SUPER_ADMIN);
        if (controller.registerUser(firstAdmin))
            cout << "[Init] Super Admin created! Your System ID is: " << empId << "\n";
        else { cout << "[Init Error] Setup failed. Exiting.\n"; return 1; }
        cout << "==================================================\n\n";
    }

    cout << "\n--------------------------------------------------\n"
        << "  University Transport Management System Running  \n"
        << "--------------------------------------------------\n";

    while (true) {
        cout << "\n===== SYSTEM LOGIN PORTAL =====\n"
            << "1. Super Admin Console\n"
            << "2. Transport Manager Console\n"
            << "3. Finance Manager Console\n"
            << "4. Student Console\n"
            << "5. Driver Console\n"
            << "6. Student Sign-Up (Request Access)\n"
            << "7. Check Student Registration Status (CNIC Lookup)\n"
            << "8. Shutdown System\n";
        string mainChoiceStr = getRobustInput("Select: ");
        int mainChoice = -1;
        try { mainChoice = stoi(mainChoiceStr); }
        catch (...) {}

        if (mainChoice == 8) { cout << "[Shutdown] Goodbye.\n"; break; }
        if (mainChoice < 1 || mainChoice > 8) { cout << "[Error] Invalid selection.\n"; continue; }

        if (mainChoice == 7) { // STUDENT STATUS
            string targetCnic = inputCNIC("Enter CNIC to check status (XXXXX-XXXXXXX-X): ");
            bool found = false;
            for (const auto& kv : controller.users) {
                if (kv.second->getCNIC() == targetCnic && kv.second->getRole() == "Student") {
                    cout << "\n=========================================\n"
                        << "   REGISTRATION STATUS: APPROVED         \n"
                        << "=========================================\n"
                        << "  Name         : " << kv.second->getName() << "\n"
                        << "  Assigned ID  : " << kv.second->getSystemId() << "\n"
                        << "  Note         : Contact admin if you need a password reset.\n"
                        << "=========================================\n"
                        << "You can now log into the Student Console.\n";
                    found = true; break;
                }
            }
            if (!found) {
                for (const auto& r : controller.pendingRegistrations) {
                    if (r.cnic == targetCnic) {
                        cout << "\n=========================================\n"
                            << "   REGISTRATION STATUS: PENDING          \n"
                            << "=========================================\n"
                            << "  Name         : " << r.name << "\n"
                            << "  Roll Number  : " << r.rollNumber << "\n"
                            << "  Status       : Waiting for Admin Approval\n"
                            << "=========================================\n"
                            << "Please check back later.\n";
                        found = true; break;
                    }
                }
            }
            if (!found)
                cout << "[System] No registration found for CNIC: " << targetCnic << "\n";
            continue;
        }

        if (mainChoice == 6) { // REGISTRATION REQUEST 
            cout << "\n--- SUBMIT STUDENT REGISTRATION REQUEST ---\n"
                << "Your request will be placed in a queue for admin verification.\n";
            string nm = inputName("Full Name: ");
            string cn = inputCNIC("CNIC: ");
            bool exists = false;
            for (const auto& kv : controller.users) if (kv.second->getCNIC() == cn) { exists = true; break; }
            for (const auto& r : controller.pendingRegistrations) if (r.cnic == cn) { exists = true; break; }
            if (exists) { cout << "[Error] This CNIC is already registered or has a pending request.\n"; continue; }
            string addr = inputAddress("Address: ");
            string em = inputEmail("Email: ");
            string ph = inputPhone("Phone: ");
            int    ag = inputAge("Age (16-25): ");
            Gender gn = inputGender("Gender");
            string roll = inputRollNumber("Roll Number: ");
            string dept = inputDepartment("Department: ");
            string sem = inputSemester("Semester");
            PendingRegistration req{ nm, cn, addr, em, ph, ag, gn, roll, dept, sem };
            controller.pendingRegistrations.push_back(req);
            controller.savePendingRegistrationsToFile();
            cout << "\n[Success] Registration request submitted! CNIC: " << cn
                << "\nAn admin will verify your details. Check status using Option 7.\n";
            continue;
        }

        if (mainChoice == 2 && !hasAdminWithRole(controller, AdminRole::TRANSPORT_MANAGER)) { cout << "[Access Denied] No Transport Manager registered.\n"; continue; }
        if (mainChoice == 3 && !hasAdminWithRole(controller, AdminRole::FINANCE_MANAGER)) { cout << "[Access Denied] No Finance Manager registered.\n"; continue; }
        if (mainChoice == 4 && !hasRole(controller, "Student")) { cout << "[Access Denied] No student accounts approved yet.\n"; continue; }
        if (mainChoice == 5 && !hasRole(controller, "Driver")) { cout << "[Access Denied] No driver accounts yet.\n"; continue; }

        string uid = getRobustInput("Enter System ID: ");
        string pass = getRobustInput("Enter Password: ");
        auto it = controller.users.find(uid);
        if (it == controller.users.end() || !it->second->checkPassword(pass)) {
            cout << "[Access Denied] Invalid ID or Password.\n"; continue;
        }
        auto activeUser = it->second;
        bool portalMismatch = false;
        if (mainChoice == 1 && !(activeUser->getRole() == "Admin" && dynamic_pointer_cast<Admin>(activeUser)->isSuperAdmin()))      portalMismatch = true;
        if (mainChoice == 2 && !(activeUser->getRole() == "Admin" && dynamic_pointer_cast<Admin>(activeUser)->canManageVehicles())) portalMismatch = true;
        if (mainChoice == 3 && !(activeUser->getRole() == "Admin" && dynamic_pointer_cast<Admin>(activeUser)->canManageFinance()))  portalMismatch = true;
        if (mainChoice == 4 && activeUser->getRole() != "Student") portalMismatch = true;
        if (mainChoice == 5 && activeUser->getRole() != "Driver")  portalMismatch = true;
        if (portalMismatch) { cout << "[Access Denied] Wrong portal for your account.\n"; continue; }

        // ================================================================
        // SUPER ADMIN PORTAL
        // ================================================================
        if (mainChoice == 1) {
            bool session = true;
            while (session) {
                cout << "\n--- SUPER ADMIN CONSOLE ---\n"
                    << "1.  Create Student Account Directly\n"
                    << "2.  Create Driver Account\n"
                    << "3.  Create Transport Manager Account (Max 1)\n"
                    << "4.  Create Finance Manager Account (Max 1)\n"
                    << "5.  Manage Pending Student Registrations ("
                    << controller.pendingRegistrations.size() << " request(s))\n"
                    << "6.  View All Transport Passes\n"
                    << "7.  Cancel / Revoke a Pass\n"
                    << "8.  View Driver & Vehicle List\n"
                    << "9.  View Full System Metrics\n"
                    << "10. View All VAN Details\n"
                    << "11. Log Out\n";
                string optStr = getRobustInput("Option: ");
                int opt = -1; try { opt = stoi(optStr); }
                catch (...) {}

                if (opt == 11) { session = false; }
                else if (opt == 1) {
                    string regNum = Student::generateRegistrationNumber();
                    cout << "[Info] Student ID: " << regNum << "\n";
                    string nm = inputName("Name: ");
                    string cn = inputCNIC("CNIC: ");
                    string addr = inputAddress("Address: ");
                    string em = inputEmail("Email: ");
                    string ph = inputPhone("Phone: ");
                    int    ag = inputAge("Age (16-25): ");
                    Gender gn = inputGender("Gender: ");
                    string pw = inputPassword("Password: ");
                    string roll = inputRollNumber("Roll Number: ");
                    string dept = inputDepartment("Department: ");
                    string sem = inputSemester("Semester");
                    controller.registerUser(make_shared<Student>( regNum, nm, cn, addr, em, ph, ag, gn, pw, roll, dept, sem));
                }
                else if (opt == 2) {
                    string empId = Driver::generateEmployeeId();
                    cout << "[Info] Driver ID: " << empId << "\n";
                    string nm = inputName("Name: ");
                    string cn = inputCNIC("CNIC: ");
                    string addr = inputAddress("Address: ");
                    string em = inputEmail("Email: ");
                    string ph = inputPhone("Phone: ");
                    int    ag = inputAgeEmployee("Age (25-80): ");
                    string pw = inputPassword("Password: ");
                    double sal = inputSalary("Salary");
                    string hire = inputHireDate("Hire Date");
                    string lic = inputLicense("License Number: ");
                    controller.registerUser(make_shared<Driver>(
                        empId, nm, cn, addr, em, ph, ag, Gender::MALE, pw,
                        "Driver", sal, hire, lic));
                }
                else if (opt == 3) {
                    if (hasAdminWithRole(controller, AdminRole::TRANSPORT_MANAGER)) {
                        cout << "[System] A Transport Manager is already registered.\n";
                    }
                    else {
                        string empId = Admin::generateEmployeeId();
                        cout << "[Info] Transport Manager ID: " << empId << "\n";
                        string nm = inputName("Name: "); string cn = inputCNIC("CNIC: ");
                        string addr = inputAddress("Address: "); string em = inputEmail("Email: ");
                        string ph = inputPhone("Phone: "); int ag = inputAgeEmployee("Age (25-80): ");
                        string pw = inputPassword("Password: "); double sal = inputSalary("Salary");
                        string hire = inputHireDate("Hire Date");
                        controller.registerUser(make_shared<Admin>(
                            empId, nm, cn, addr, em, ph, ag, Gender::MALE, pw,
                            "Transport Manager", sal, hire, AdminRole::TRANSPORT_MANAGER));
                    }
                }
                else if (opt == 4) {
                    if (hasAdminWithRole(controller, AdminRole::FINANCE_MANAGER)) {
                        cout << "[System] A Finance Manager is already registered.\n";
                    }
                    else {
                        string empId = Admin::generateEmployeeId();
                        cout << "[Info] Finance Manager ID: " << empId << "\n";
                        string nm = inputName("Name: "); string cn = inputCNIC("CNIC: ");
                        string addr = inputAddress("Address: "); string em = inputEmail("Email: ");
                        string ph = inputPhone("Phone: "); int ag = inputAgeEmployee("Age (25-80): ");
                        string pw = inputPassword("Password: "); double sal = inputSalary("Salary");
                        string hire = inputHireDate("Hire Date");
                        controller.registerUser(make_shared<Admin>(
                            empId, nm, cn, addr, em, ph, ag, Gender::MALE, pw,
                            "Finance Manager", sal, hire, AdminRole::FINANCE_MANAGER));
                    }
                }
                else if (opt == 5) {
                    if (controller.pendingRegistrations.empty()) {
                        cout << "[System] No pending student registration requests.\n";
                    }
                    else {
                        cout << "\n--- PENDING STUDENT REGISTRATIONS ---\n";
                        for (size_t i = 0; i < controller.pendingRegistrations.size(); ++i) {
                            const auto& r = controller.pendingRegistrations[i];
                            cout << "  [" << (i + 1) << "] Name: " << r.name
                                << " | Roll: " << r.rollNumber
                                << " | CNIC: " << r.cnic
                                << " | Dept: " << r.department << "\n";
                        }
                        string selStr = getRobustInput("Select Request Number to process (or Enter to cancel): ");
                        if (!selStr.empty()) {
                            try {
                                int idx = stoi(selStr) - 1;
                                if (idx >= 0 && idx < (int)controller.pendingRegistrations.size()) {
                                    auto r = controller.pendingRegistrations[idx];
                                    cout << "\nProcessing request for: " << r.name << "\n"
                                        << "1. Approve & Assign Credentials\n"
                                        << "2. Reject Request\n"
                                        << "3. Cancel\n";
                                    string act = getRobustInput("Select action: ");
                                    if (act == "1") {
                                        string generatedId = Student::generateRegistrationNumber();
                                        cout << "Generated System ID: " << generatedId << "\n";
                                        string assignedId = getRobustInput("Confirm or enter custom System ID (Enter=keep): ");
                                        if (assignedId.empty()) assignedId = generatedId;
                                        if (controller.users.find(assignedId) != controller.users.end()) {
                                            cout << "[Error] This System ID is already in use.\n";
                                        }
                                        else {
                                            string assignedPw = inputPassword("Assign Student Password (8+ chars): ");
                                            auto newStudent = make_shared<Student>(
                                                assignedId, r.name, r.cnic, r.address,
                                                r.email, r.phone, r.age, r.gender,
                                                assignedPw, r.rollNumber, r.department, r.semester);
                                            controller.users[assignedId] = newStudent;
                                            controller.saveUsersToFile();
                                            controller.pendingRegistrations.erase(
                                                controller.pendingRegistrations.begin() + idx);
                                            controller.savePendingRegistrationsToFile();
                                            cout << "[System] Approved! Student ID: " << assignedId << "\n";
                                            cout << "[Note] Communicate the assigned password to the student.\n";
                                        }
                                    }
                                    else if (act == "2") {
                                        controller.pendingRegistrations.erase(
                                            controller.pendingRegistrations.begin() + idx);
                                        controller.savePendingRegistrationsToFile();
                                        cout << "[System] Registration request rejected.\n";
                                    }
                                }
                                else cout << "[Error] Invalid selection.\n";
                            }
                            catch (...) { cout << "[Error] Invalid input.\n"; }
                        }
                    }
                }
                else if (opt == 6) {
                    cout << "\n--- ALL PASSES ---\n"; int cnt = 0;
                    for (const auto& p : controller.passes) {
                        cout << " Pass " << p.getPassId()
                            << " | Student: " << p.getStudentId()
                            << " | Route: " << p.getRouteId()
                            << " | Status: " << passStatusToString(p.getStatus()) << "\n";
                        cnt++;
                    }
                    if (cnt == 0) cout << "No passes yet.\n";
                }
                else if (opt == 7) { string pId = getRobustInput("Pass ID to cancel: "); controller.cancelPass(pId); }
                else if (opt == 8)  controller.viewDriverAssignments();
                else if (opt == 9)  controller.displaySystemStats();
                else if (opt == 10) controller.viewAllVanDetails();
                else cout << "[Error] Invalid option.\n";
            }
        }

        // ================================================================
        // TRANSPORT MANAGER PORTAL
        // ================================================================
        else if (mainChoice == 2) {
            bool session = true;
            while (session) {
                cout << "\n--- TRANSPORT MANAGER PANEL ---\n"
                    << "1.  Add Vehicle (BUS)\n"
                    << "2.  Add VAN (University-Use, with Purpose & Mileage)\n"
                    << "3.  Edit Vehicle / VAN\n"
                    << "4.  Remove Vehicle\n"
                    << "5.  Add Route (with Stops & 15-min gap rule)\n"
                    << "6.  Edit Existing Route (Name / Distance / Stops)\n"
                    << "7.  Assign BUS to Route\n"
                    << "8.  View Driver Availability\n"
                    << "9.  Add Stop to Existing Route\n"
                    << "10. View Routes & Paths\n"
                    << "11. Assign Driver to Vehicle\n"
                    << "12. Unassign Driver from Vehicle\n"
                    << "13. View All Vehicle Trip Logs (Today)\n"
                    << "14. View Route Waitlist\n"
                    << "15. View All VAN Details\n"
                    << "16. Unassign BUS from Route\n"
                    << "17. Log Out\n";
                string optStr = getRobustInput("Option: ");
                int opt = -1; try { opt = stoi(optStr); }
                catch (...) {}

                if (opt == 17) { session = false; }
                else if (opt == 1) {
                    string vId = getRobustInput("Vehicle ID: ");
                    if (any_of(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) {return v.getVehicleId() == vId; })) {
                        cout << "[Error] Vehicle ID already exists.\n"; continue;
                    }
                    string plate;
                    while (true) {
                        plate = getRobustInput("Plate (ABC-1234): ");
                        if (!ValidationUtil::isValidVehiclePlate(plate)) {
                            cout << "[Error] Invalid format.\n";
                        }
                        else if (controller.isVehiclePlateInUse(plate)) {
                            cout << "[Error] License plate is already registered to another vehicle.\n";
                        }
                        else { break; }
                    }
                    string capStr = getRobustInput("Capacity (min 15): ");
                    int cap = 15;
                    while (true) {
                        try { cap = stoi(capStr); if (cap >= 15) break; }
                        catch (...) {}
                        cout << "[Error] BUS capacity must be at least 15.\n";
                        capStr = getRobustInput("Capacity (min 15): ");
                    }
                    double eff = 0.0;
                    while (true) {
                        string es = getRobustInput("Fuel Efficiency (4.2-15.0 km/L): ");
                        try { eff = stod(es); if (eff >= 4.2 && eff <= 15.0) break; }
                        catch (...) {}
                        cout << "[Error] 4.2-15.0\n";
                    }
                    string fType = getRobustInput("Fuel Type (Petrol/Diesel): ");
                    controller.addVehicle(Vehicle(vId, plate, VehicleType::BUS, cap, eff, fType));
                }
                else if (opt == 2) {
                    string vId = getRobustInput("VAN ID: ");
                    if (any_of(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) {return v.getVehicleId() == vId; })) {
                        cout << "[Error] Vehicle ID already exists.\n"; continue;
                    }
                    string plate;
                    while (true) {
                        plate = getRobustInput("Plate (ABC-1234): ");
                        if (!ValidationUtil::isValidVehiclePlate(plate)) {
                            cout << "[Error] Invalid format.\n";
                        }
                        else if (controller.isVehiclePlateInUse(plate)) {
                            cout << "[Error] License plate is already registered to another vehicle.\n";
                        }
                        else { break; }
                    }
                    string capStr = getRobustInput("Capacity (seats): ");
                    int cap = 7;
                    try { cap = stoi(capStr); }
                    catch (...) {}
                    double eff = 0.0;
                    while (true) {
                        string es = getRobustInput("Fuel Efficiency (4.2-15.0 km/L): ");
                        try { eff = stod(es); if (eff >= 4.2 && eff <= 15.0) break; }
                        catch (...) {}
                        cout << "[Error] 4.2-15.0\n";
                    }
                    string fType = getRobustInput("Fuel Type (Petrol/Diesel/CNG): ");
                    cout << "--- VAN DETAILS (University Internal Use) ---\n";
                    string purpose = inputVanPurpose();
                    double dMileage = inputVanDailyMileage();
                    double estFuel = (eff > 0) ? (dMileage / eff) * controller.petrolPricePerLitre : 0;
                    cout << "[Preview] Estimated daily fuel cost: Rs " << fixed << setprecision(2)
                        << estFuel << " (" << dMileage << " km / " << eff
                        << " km/L x Rs " << controller.petrolPricePerLitre << "/L)\n";
                    controller.addVehicle(Vehicle(vId, plate, cap, eff, fType, purpose, dMileage));
                }
                else if (opt == 3) {
                    string vId = getRobustInput("Vehicle ID to edit: ");
                    auto vIt = find_if(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) {return v.getVehicleId() == vId; });
                    if (vIt == controller.vehicles.end()) { cout << "[Error] Not found.\n"; continue; }
                    cout << "Current Plate    : " << vIt->getLicensePlate() << "\n"
                        << "Current Capacity : " << vIt->getCapacity() << "\n"
                        << "Current Eff.     : " << vIt->getFuelEfficiency() << " km/L\n"
                        << "Current FuelType : " << vIt->getFuelType() << "\n";
                    string plate;
                    while (true) {
                        plate = getRobustInput("New Plate (Enter=keep): ");
                        if (plate.empty()) { plate = vIt->getLicensePlate(); break; }
                        if (ValidationUtil::isValidVehiclePlate(plate)) break;
                        cout << "[Error] Invalid.\n";
                    }
                    string capStr = getRobustInput("New Capacity (min 15 for BUS, Enter=keep): ");
                    int cap = vIt->getCapacity();
                    if (!capStr.empty()) {
                        while (true) {
                            try {
                                int newCap = stoi(capStr);
                                if (!vIt->isVAN() && newCap < 15) {
                                    cout << "[Error] BUS capacity must be at least 15.\n";
                                    capStr = getRobustInput("New Capacity (min 15 for BUS): ");
                                    continue;
                                }
                                cap = newCap; break;
                            }
                            catch (...) { cout << "[Error] Invalid number.\n"; capStr = getRobustInput("New Capacity: "); }
                        }
                    }
                    string effStr = getRobustInput("New Efficiency (4.2-15.0, Enter=keep): ");
                    double eff = vIt->getFuelEfficiency();
                    if (!effStr.empty()) {
                        while (true) {
                            try { eff = stod(effStr); if (eff >= 4.2 && eff <= 15.0) break; }
                            catch (...) {}
                            cout << "[Error] 4.2-15.0\n"; effStr = getRobustInput("Efficiency: ");
                        }
                    }
                    string fType = getRobustInput("New Fuel Type (Enter=keep): ");
                    if (fType.empty()) fType = vIt->getFuelType();
                    vIt->setLicensePlate(plate); vIt->setCapacity(cap);
                    vIt->setFuelEfficiency(eff); vIt->setFuelType(fType);
                    if (vIt->isVAN()) {
                        cout << "--- VAN FIELDS (Enter=keep) ---\n"
                            << "Current Purpose       : " << vIt->getVanPurpose() << "\n"
                            << "Current Daily Mileage : " << vIt->getVanDailyMileage() << " km\n";
                        string purpIn = getRobustInput("New Purpose (Enter=keep): ");
                        if (!purpIn.empty()) {
                            if (ValidationUtil::isValidVanPurpose(purpIn)) vIt->setVanPurpose(sanitizeCsv(purpIn));
                            else cout << "[Warning] Invalid purpose   not updated.\n";
                        }
                        string dMStr = getRobustInput("New Daily Mileage 1-6 km (Enter=keep): ");
                        if (!dMStr.empty()) {
                            dMStr = cleanNumericString(dMStr);
                            try { double d = stod(dMStr); if (ValidationUtil::isValidVanDailyKm(d)) vIt->setVanDailyMileage(d); else cout << "[Warning] Must be 1-6 km.\n"; }
                            catch (...) { cout << "[Warning] Invalid.\n"; }
                        }
                        double estFuel = vIt->getVanEstimatedDailyFuelCost(controller.petrolPricePerLitre);
                        cout << "[Updated] Est. daily fuel: Rs " << fixed << setprecision(2) << estFuel << "\n";
                    }
                    controller.saveVehiclesToFile();
                    cout << "[System] Vehicle " << vId << " updated.\n";
                    if (!vIt->isVAN() && !vIt->getAssignedRouteId().empty())
                        controller.processRouteWaitlist(vIt->getAssignedRouteId());
                    if (vIt->isVAN()) vIt->printVanDetails(controller.petrolPricePerLitre);
                }
                else if (opt == 4) {
                    string vId = getRobustInput("Vehicle ID to remove: ");
                    controller.removeVehicle(vId);
                }
                else if (opt == 5) {
                    string rId = inputRouteId("Route ID (alphanumeric, e.g. RT01 or R1): ");
                    if (any_of(controller.routes.begin(), controller.routes.end(),
                        [&](const Route& r) {return r.getRouteId() == rId; })) {
                        cout << "[Error] Route ID already exists.\n"; continue;
                    }
                    string rName = getRobustInput("Route Name: ");
                    double approxKm = 0;
                    while (true) { string ks = getRobustInput("Distance (2.5-6.4 km): "); try { approxKm = stod(ks); if (approxKm >= 2.5 && approxKm <= 6.4) break; } catch (...) {} cout << "[Error] 2.5-6.4 km.\n"; }
                    vector<Stop> routeStops;
                    cout << "Add stops (min 8, max 12):\n"; int lastMin = -999;
                    for (int i = 0; i < 12; ++i) {
                        cout << "\nStop #" << (i + 1) << ":\n";
                        string stopId = inputStopId("  Stop ID (alphanumeric only, e.g. S01 or STOP1): ");
                        bool dupId = false;
                        for (const auto& s : routeStops) if (s.stopId == stopId) { dupId = true; break; }
                        if (dupId) { cout << "[Error] Stop ID already used on this route.\n"; i--; continue; }
                        string stopName;
                        while (true) { stopName = getRobustInput("  Stop Name: "); if (ValidationUtil::isValidName(stopName)) break; cout << "[Error] Letters only.\n"; }
                        string coord = inputCoordinates("  Coordinates");
                        string stopTime; int curMin = -1;
                        while (true) {
                            stopTime = getRobustInput("  Arrival Time (HH:MM): ");
                            curMin = DateUtil::timeToMinutes(stopTime);
                            if (curMin == -1) { cout << "[Error] Invalid time.\n"; continue; }
                            if (i > 0 && curMin < lastMin + 15) { cout << "[Error] Must be 15+ min after previous stop.\n"; continue; }
                            break;
                        }
                        routeStops.push_back({ stopId, stopName, stopTime });
                        lastMin = curMin;
                        if (routeStops.size() >= 8 && routeStops.size() < 12) {
                            string ch = getRobustInput("[" + to_string(routeStops.size()) + "/12 stops] Continue? (y/n): ");
                            if (ch == "n" || ch == "N") break;
                        }
                    }
                    if (routeStops.size() < 8) cout << "[Error] Min 8 stops required. Route aborted.\n";
                    else controller.addRoute(Route(rId, rName, routeStops, approxKm));
                }
                else if (opt == 6) {
                    cout << "\nExisting Routes:\n";
                    for (const auto& r : controller.routes)
                        cout << "  - " << r.getRouteId() << " | " << r.getRouteName()
                        << " | " << r.getApproxKilometer() << " km | "
                        << r.getStops().size() << " stops\n";
                    string rId = getRobustInput("Route ID to edit: ");
                    auto rIt = find_if(controller.routes.begin(), controller.routes.end(),
                        [&](const Route& r) { return r.getRouteId() == rId; });
                    if (rIt == controller.routes.end()) { cout << "[Error] Route not found.\n"; continue; }
                    cout << "\nCurrent Name    : " << rIt->getRouteName() << "\n"
                        << "Current Distance: " << rIt->getApproxKilometer() << " km\n"
                        << "Current Stops   : " << rIt->getStops().size() << "\n";
                    string newName = getRobustInput("New Route Name (Enter=keep): ");
                    if (!newName.empty()) rIt->setRouteName(newName);
                    string newKmStr = getRobustInput("New Distance km (2.5-6.4, Enter=keep): ");
                    if (!newKmStr.empty()) {
                        try {
                            double nk = stod(newKmStr);
                            if (nk >= 2.5 && nk <= 6.4) rIt->setApproxKilometer(nk);
                            else cout << "[Warning] Distance out of range   not updated.\n";
                        }
                        catch (...) { cout << "[Warning] Invalid number   not updated.\n"; }
                    }
                    string editStops = getRobustInput("Edit existing stop details? (y/n): ");
                    if (editStops == "y" || editStops == "Y") {
                        const auto& stps = rIt->getStops();
                        for (size_t si = 0; si < stps.size(); si++)
                            cout << "  Stop [" << (si + 1) << "] ID:" << stps[si].stopId
                            << " Name:" << stps[si].stopName
                            << " Time:" << stps[si].arrivalTime << "\n";
                        string siStr = getRobustInput("Enter stop number to edit (or Enter to skip): ");
                        if (!siStr.empty()) {
                            try {
                                int si = stoi(siStr) - 1;
                                if (si >= 0 && si < (int)rIt->getStops().size()) {
                                    vector<Stop> updatedStops = rIt->getStops();
                                    cout << "Editing Stop " << (si + 1) << ": " << updatedStops[si].stopName << "\n";
                                    string newStopName = getRobustInput("  New Stop Name (Enter=keep): ");
                                    if (!newStopName.empty()) {
                                        if (ValidationUtil::isValidName(newStopName)) updatedStops[si].stopName = newStopName;
                                        else cout << "[Warning] Invalid name   not updated.\n";
                                    }
                                    string newCoord = getRobustInput("  New Coordinates (Enter=keep): ");
                                    /*if (!newCoord.empty()) {
                                        if (ValidationUtil::isValidCoordinates(newCoord))
                                            updatedStops[si].coordinates = sanitizeCsv(newCoord);
                                        else cout << "[Warning] Invalid coordinates   not updated.\n";
                                    }*/
                                    string newTime = getRobustInput("  New Arrival Time HH:MM (Enter=keep): ");
                                    if (!newTime.empty()) {
                                        int tm = DateUtil::timeToMinutes(newTime);
                                        if (tm == -1) cout << "[Warning] Invalid time   not updated.\n";
                                        else {
                                            bool ok = true;
                                            if (si > 0) {
                                                int prevMin = DateUtil::timeToMinutes(updatedStops[si - 1].arrivalTime);
                                                if (tm < prevMin + 15) { cout << "[Warning] Too close to previous stop.\n"; ok = false; }
                                            }
                                            if (ok && si < (int)updatedStops.size() - 1) {
                                                int nextMin = DateUtil::timeToMinutes(updatedStops[si + 1].arrivalTime);
                                                if (nextMin < tm + 15) { cout << "[Warning] Too close to next stop.\n"; ok = false; }
                                            }
                                            if (ok) updatedStops[si].arrivalTime = newTime;
                                        }
                                    }
                                    rIt->setStops(updatedStops);
                                }
                                else cout << "[Error] Invalid stop number.\n";
                            }
                            catch (...) { cout << "[Error] Invalid input.\n"; }
                        }
                    }
                    controller.saveRoutesToFile();
                    cout << "[System] Route " << rId << " updated.\n";
                }
                else if (opt == 7) {
                    string vId = getRobustInput("BUS Vehicle ID: ");
                    auto vIt = find_if(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) { return v.getVehicleId() == vId; });
                    if (vIt != controller.vehicles.end() && !vIt->getAssignedRouteId().empty()) {
                        cout << "[Info] Vehicle " << vId << " is currently on Route "
                            << vIt->getAssignedRouteId() << ". Use option 16 to unassign first.\n";
                    }
                    string rId = getRobustInput("Route ID: ");
                    if (controller.assignVehicleToRoute(vId, rId)) {
                        cout << "[System] Assigned " << vId << " -> " << rId << "\n";
                        controller.processRouteWaitlist(rId);
                    }
                }
                else if (opt == 8) controller.viewDriverAssignments();
                else if (opt == 9) {
                    cout << "\nRoutes:\n";
                    for (const auto& r : controller.routes)
                        cout << " - " << r.getRouteId() << " | " << r.getRouteName() << "\n";
                    string rId = getRobustInput("Route ID to add stop: ");
                    auto rIt = find_if(controller.routes.begin(), controller.routes.end(),
                        [&](const Route& r) {return r.getRouteId() == rId; });
                    if (rIt == controller.routes.end()) { cout << "[Error] Not found.\n"; continue; }
                    if (rIt->getStops().size() >= 12) { cout << "[Error] Max 12 stops.\n"; continue; }
                    string sId = inputStopId("New Stop ID (alphanumeric only, e.g. S09 or STOP9): ");
                    bool dup = false;
                    for (const auto& s : rIt->getStops()) if (s.stopId == sId) { dup = true; break; }
                    if (dup) { cout << "[Error] Stop ID already used on this route.\n"; continue; }
                    string sName;
                    while (true) { sName = getRobustInput("Stop Name: "); if (ValidationUtil::isValidName(sName)) break; cout << "[Error] Letters only.\n"; }
                    string stopTime; int curMin = -1;
                    int lastMin = rIt->getStops().empty() ? -1
                        : DateUtil::timeToMinutes(rIt->getStops().back().arrivalTime);
                    while (true) {
                        stopTime = getRobustInput("Arrival Time (HH:MM): ");
                        curMin = DateUtil::timeToMinutes(stopTime);
                        if (curMin == -1) { cout << "[Error] Invalid time.\n"; continue; }
                        if (lastMin != -1 && curMin < lastMin + 15) {
                            cout << "[Error] Must be 15+ min after last stop.\n"; continue;
                        }
                        break;
                    }
                    rIt->addStop({ sId, sName,stopTime });
                    controller.saveRoutesToFile();
                    cout << "[System] Stop added.\n";
                }
                else if (opt == 10) {
                    cout << "\n=========================================\n"
                        << "       ACTIVE ROUTES & PATHS            \n"
                        << "=========================================\n";
                    if (controller.routes.empty()) cout << "No routes defined.\n";
                    else for (const auto& r : controller.routes) {
                        cout << "Route: " << r.getRouteId() << " (" << r.getRouteName()
                            << ") | " << r.getApproxKilometer() << " km\n"
                            << "Stops:\n";
                        for (size_t i = 0; i < r.getStops().size(); ++i)
                            cout << "  [" << (i + 1) << "] ID:" << r.getStops()[i].stopId
                            << " | " << r.getStops()[i].stopName
                            << " | " << r.getStops()[i].arrivalTime << "\n";
                        cout << "Vehicles: "; bool vf = false;
                        for (const auto& v : controller.vehicles)
                            if (v.getAssignedRouteId() == r.getRouteId()) {
                                int arr = controller.getEffectiveTripCount(v.getVehicleId(), TripDirection::ARRIVAL);
                                int dep = controller.getEffectiveTripCount(v.getVehicleId(), TripDirection::DEPARTURE);
                                cout << v.getVehicleId() << "("
                                    << vehicleTypeToString(v.getType())
                                    << " Seats:" << v.getOccupiedSeats() << "/" << v.getCapacity()
                                    << " ARR=" << arr << "/1 DEP=" << dep << "/1";
                                if (v.isVAN()) cout << " DlyMileage:" << v.getVanDailyMileage() << "km";
                                cout << ") "; vf = true;
                            }
                        if (!vf) cout << "None";
                        cout << "\n-----------------------------------------\n";
                    }
                }
                else if (opt == 11) {
                    string dId = getRobustInput("Driver ID: ");
                    string vId = getRobustInput("Vehicle ID: ");
                    controller.assignDriverToVehicle(dId, vId);
                }
                else if (opt == 12) {
                    string dId = getRobustInput("Driver ID to unassign: ");
                    controller.unassignDriverFromVehicle(dId);
                }
                else if (opt == 13) {
                    for (const auto& v : controller.vehicles)
                        controller.viewDailyTripSummary(v.getVehicleId());
                }
                else if (opt == 14) {
                    string rId = getRobustInput("Route ID: ");
                    controller.viewRouteWaitlist(rId);
                }
                else if (opt == 15) controller.viewAllVanDetails();
                else if (opt == 16) {
                    string vId = getRobustInput("BUS Vehicle ID to unassign from route: ");
                    auto vIt = find_if(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) { return v.getVehicleId() == vId; });
                    if (vIt == controller.vehicles.end()) cout << "[Error] Vehicle not found.\n";
                    else if (vIt->isVAN()) cout << "[Blocked] VANs are not assigned to routes   nothing to unassign.\n";
                    else if (vIt->getAssignedRouteId().empty()) cout << "[Info] Vehicle has no route assigned.\n";
                    else {
                        string oldRoute = vIt->getAssignedRouteId();
                        vIt->setOccupiedSeats(0);
                        vIt->setAssignedRouteId("");
                        controller.saveVehiclesToFile();
                        cout << "[System] Vehicle " << vId << " unassigned from Route "
                            << oldRoute << ". Occupied seat count reset to 0.\n";
                    }
                }
                else cout << "[Error] Invalid option.\n";
            }
        }

        // ================================================================
        // FINANCE MANAGER PORTAL
        // ================================================================
        else if (mainChoice == 3) {
            bool session = true;
            while (session) {
                cout << "\n--- FINANCE MANAGER DESK ---\n"
                    << "1.  Set / Update Monthly Capital Budget\n"
                    << "2.  Update Petrol Price per Litre\n"
                    << "3.  View Monthly Capital Status\n"
                    << "4.  View Vehicle Fuel Cost (Today) by Vehicle ID\n"
                    << "5.  View All Vehicles Fuel Cost Summary (Today)\n"
                    << "6.  View Pending Pass Payments\n"
                    << "7.  Process Pass Payment by Pass ID\n"
                    << "8.  Generate CSV Finance Report (.csv)\n"
                    << "9.  View VAN Mileage & Fuel Estimates\n"
                    << "10. Log Out\n";
                string optStr = getRobustInput("Option: ");
                int opt = -1; try { opt = stoi(optStr); }
                catch (...) {}
                if (opt == 10) { session = false; }
                else if (opt == 1) {
                    string amtStr = getRobustInput("Monthly Capital (any positive amount up to Rs 500,000): ");
                    double amount = 0;
                    try { amount = stod(cleanNumericString(amtStr)); }
                    catch (...) { cout << "[Error] Invalid number.\n"; continue; }
                    controller.setMonthlyCapital(amount);
                }
                else if (opt == 2) {
                    string priceStr = getRobustInput("Petrol Price/L (Rs 50-1000): ");
                    double price = 0;
                    try { price = stod(cleanNumericString(priceStr)); }
                    catch (...) { cout << "[Error] Invalid.\n"; continue; }
                    controller.updatePetrolPrice(price);
                }
                else if (opt == 3) controller.viewMonthlyCapitalStatus();
                else if (opt == 4) {
                    cout << "\nVehicles:\n";
                    for (const auto& v : controller.vehicles)
                        cout << "  - " << v.getVehicleId()
                        << " (" << vehicleTypeToString(v.getType()) << ")"
                        << " | Route: " << (v.isVAN() ? "Campus" : v.getAssignedRouteId())
                        << " | " << v.getFuelEfficiency() << " km/L\n";
                    string vId = getRobustInput("Vehicle ID: ");
                    bool found = any_of(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) {return v.getVehicleId() == vId; });
                    if (!found) cout << "[Error] Vehicle not found.\n";
                    else controller.viewVehicleFuelCostToday(vId);
                }
                else if (opt == 5) {
                    string today = DateUtil::getCurrentDate();
                    cout << "\n--- ALL VEHICLES FUEL COST (" << today << ") ---\n";
                    double grand = 0;
                    for (const auto& v : controller.vehicles) {
                        double litres = 0, cost = 0; int trips = 0;
                        for (const auto& t : controller.tripLogs)
                            if (t.vehicleId == v.getVehicleId() && t.date == today) {
                                litres += t.fuelUsedLiters; cost += t.fuelCostEstimate; trips++;
                            }
                        cout << "  " << v.getVehicleId()
                            << " | " << vehicleTypeToString(v.getType())
                            << " | Eff: " << v.getFuelEfficiency() << " km/L"
                            << " | Trips: " << trips
                            << " | Fuel: " << fixed << setprecision(2) << litres
                            << " L | Cost: Rs " << cost << "\n";
                        grand += cost;
                    }
                    cout << "  TOTAL FLEET COST TODAY: Rs " << fixed << setprecision(2) << grand << "\n";
                }
                else if (opt == 6) {
                    int cnt = 0;
                    for (const auto& p : controller.passes)
                        if (p.getStatus() == PassStatus::PENDING_PAYMENT) {
                            cout << " Pass " << p.getPassId()
                                << " | Student: " << p.getStudentId()
                                << " | Route: " << p.getRouteId()
                                << " | Stop: " << p.getChosenStop() << "\n";
                            cnt++;
                        }
                    if (cnt == 0) cout << "No pending payments.\n";
                }
                else if (opt == 7) { string pId = getRobustInput("Pass ID: "); controller.financeClearPass(pId); }
                else if (opt == 8) { cout << "[Report] Generating CSV reports...\n"; controller.generateCSVReport(); }
                else if (opt == 9) {
                    cout << "\n=========================================\n"
                        << "     VAN MILEAGE & FUEL ESTIMATES        \n"
                        << "=========================================\n";
                    bool any = false;
                    for (const auto& v : controller.vehicles) {
                        if (!v.isVAN()) continue;
                        double estCost = v.getVanEstimatedDailyFuelCost(controller.petrolPricePerLitre);
                        cout << "  VAN: " << v.getVehicleId() << " | Usage: Campus (internal)\n"
                            << "  Purpose         : " << (v.getVanPurpose().empty() ? "N/A" : v.getVanPurpose()) << "\n"
                            << "  Daily Mileage   : " << v.getVanDailyMileage() << " km\n"
                            << "  Efficiency      : " << v.getFuelEfficiency() << " km/L\n"
                            << "  Petrol Rate     : Rs " << fixed << setprecision(2)
                            << controller.petrolPricePerLitre << "/L\n"
                            << "  Est. Fuel/Trip  : Rs " << estCost
                            << " (" << v.getVanDailyMileage() << " / "
                            << v.getFuelEfficiency() << " x "
                            << controller.petrolPricePerLitre << ")\n"
                            << "-----------------------------------------\n";
                        any = true;
                    }
                    if (!any) cout << "  No VANs registered.\n";
                }
                else cout << "[Error] Invalid option.\n";
            }
        }

        // ================================================================
        // STUDENT PORTAL
        // ================================================================
        else if (mainChoice == 4)
        {
            bool session = true;
            while (session) {
                cout << "\n--- STUDENT INTERFACE ---\n"
                    << "1. View Available Routes, Stops & Seats\n"
                    << "2. Request New Transport Pass\n"
                    << "3. Apply for Pass Change (Switch Route)\n"
                    << "4. Check My Pass Status\n"
                    << "5. Update My Profile (Phone / Address / Semester)\n"
                    << "6. Log Out\n";
                string optStr = getRobustInput("Option: ");
                int opt = -1; try { opt = stoi(optStr); }
                catch (...) {}

                if (opt == 6) { session = false; }
                else if (opt == 1) { // VIEW ROUTES SEATS
                    cout << "\n--- AVAILABLE ROUTES ---\n";
                    for (const auto& r : controller.routes) {
                        cout << "Route: " << r.getRouteId() << " (" << r.getRouteName()
                            << ") | " << r.getApproxKilometer() << " km\nStops: ";
                        for (size_t i = 0; i < r.getStops().size(); ++i) {
                            cout << r.getStops()[i].stopName
                                << "(" << r.getStops()[i].arrivalTime << ")";
                            if (i + 1 < r.getStops().size()) cout << " -> ";
                        }
                        int seatsLeft = controller.getRemainingSeatsForRoute(r.getRouteId());
                        cout << "\nSeats Available: " << seatsLeft;
                        if (seatsLeft == 0) cout << " (FULL   you will be waitlisted)";
                        cout << "\n----------------------------------------------\n";
                    }
                }
                else if (opt == 2) { // APPLY REQUEST PASS
                    string rId = getRobustInput("Preferred Route ID (like R1): ");
                    string stopName = getRobustInput("Stop Name: ");
                    controller.requestPass(activeUser->getSystemId(), rId, stopName);
                }
                else if (opt == 3) { // REQUEST PASS CHANGE TO NEW ROUTE
                    string rId = getRobustInput("New Route ID: ");
                    string stopName = getRobustInput("New Stop Name: ");
                    controller.requestPassChange(activeUser->getSystemId(), rId, stopName);
                }
                else if (opt == 4) { // CHECK MY PASS STATUS
                    controller.sweepExpiredPasses(); bool found = false;
                    for (const auto& p : controller.passes)
                        if (p.getStudentId() == activeUser->getSystemId()) {
                            found = true;
                            auto sp = dynamic_pointer_cast<Student>(activeUser);
                            cout << "Pass: " << p.getPassId()
                                << " | Route: " << p.getRouteId()
                                << " | Stop: " << p.getChosenStop();
                            if (sp) cout << " | Sem: " << sp->getSemester()
                                << " | Dept: " << sp->getDepartment();
                            cout << " | Status: ";
                            switch (p.getStatus()) {
                            case PassStatus::PENDING_PAYMENT: cout << "Pending Payment\n"; break;
                            case PassStatus::ACTIVE:   cout << "ACTIVE (Expires: " << p.getExpiryDate() << ")\n"; break;
                            case PassStatus::WAITLISTED: cout << "WAITLISTED (awaiting seat)\n"; break;
                            case PassStatus::EXPIRED:    cout << "EXPIRED\n"; break;
                            }
                        }
                    if (!found) cout << "No pass records found.\n";
                }
                else if (opt == 5) { // CHANGE MY PROFILE DATA
                    auto sp = dynamic_pointer_cast<Student>(activeUser);
                    if (!sp) { cout << "[Error] Internal error.\n"; continue; }
                    cout << "Current Phone   : " << sp->getPhone()
                        << "\nCurrent Address : " << sp->getAddress()
                        << "\nCurrent Semester: " << sp->getSemester() << "\n";
                    string newPhone = getRobustInput("New Phone (Enter=keep): ");
                    if (!newPhone.empty()) {
                        if (ValidationUtil::isValidPhone(newPhone)) sp->setPhone(newPhone);
                        else cout << "[Warning] Invalid phone   not updated.\n";
                    }
                    string newAddr = getRobustInput("New Address (Enter=keep): ");
                    if (!newAddr.empty()) {
                        if (ValidationUtil::isValidAddress(newAddr)) sp->setAddress(sanitizeCsv(newAddr));
                        else cout << "[Warning] Address must be 5+ chars   not updated.\n";
                    }
                    string newSem = getRobustInput("New Semester (1-8, Enter=keep): ");
                    if (!newSem.empty()) {
                        newSem = cleanNumericString(newSem);
                        if (ValidationUtil::isValidSemester(newSem)) sp->setSemester(newSem);
                        else cout << "[Warning] Semester must be 1-8   not updated.\n";
                    }
                    controller.saveUsersToFile();
                    cout << "[System] Profile updated.\n";
                }
                else cout << "[Error] Invalid option.\n";
            }
        }

        // ================================================================
        // DRIVER PORTAL
        // ================================================================
        else if (mainChoice == 5) {
            auto activeDriver = dynamic_pointer_cast<Driver>(activeUser);
            if (!activeDriver) continue;
            bool session = true;
            while (session) {
                string vId = activeDriver->getAssignedVehicle();
                int arrToday = vId.empty() ? 0 : controller.getEffectiveTripCount(vId, TripDirection::ARRIVAL);
                int depToday = vId.empty() ? 0 : controller.getEffectiveTripCount(vId, TripDirection::DEPARTURE);

                bool isVanDriver = false;
                if (!vId.empty()) {
                    auto vIt2 = find_if(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) { return v.getVehicleId() == vId; });
                    if (vIt2 != controller.vehicles.end() && vIt2->isVAN())
                        isVanDriver = true;
                }

                cout << "\n--- DRIVER CONSOLE ---\n"
                    << "ID: " << activeDriver->getSystemId()
                    << " | " << activeDriver->getName()
                    << " | Status: " << driverStatusToString(activeDriver->getStatus())
                    << " | Vehicle: " << (vId.empty() ? "Unassigned" : vId)
                    << "\nToday (effective): ARR=" << arrToday << "/1  DEP=" << depToday << "/1\n";

                if (!vId.empty()) {
                    auto vIt2 = find_if(controller.vehicles.begin(), controller.vehicles.end(),
                        [&](const Vehicle& v) { return v.getVehicleId() == vId; });
                    if (vIt2 != controller.vehicles.end() && vIt2->isVAN()) {
                        double estCost = vIt2->getVanEstimatedDailyFuelCost(controller.petrolPricePerLitre);
                        cout << "[VAN] Daily Mileage: " << vIt2->getVanDailyMileage()
                            << " km | Est. fuel cost/trip: Rs "
                            << fixed << setprecision(2) << estCost << "\n";
                    }
                }

                cout << "----------------------\n";
                if (isVanDriver) {
                    cout << "1. Dispatch Trip (enter 0=ARRIVAL or 1=DEPARTURE)\n";
                }
                else {
                    cout << "1. Start ARRIVAL Trip\n"
                        << "2. Start DEPARTURE Trip\n";
                }
                cout << "3. End Current Shift\n"
                    << "4. Log Manual Fuel Purchase\n"
                    << "5. View Today's Trip Summary\n"
                    << "6. Log Out\n";

                string optStr = getRobustInput("Option: ");
                int opt = -1; try { opt = stoi(optStr); }
                catch (...) {}

                if (opt == 6) { session = false; }
                else if (opt == 1) {
                    if (vId.empty()) {
                        cout << "[Blocked] No vehicle assigned.\n";
                    }
                    else if (activeDriver->getStatus() == DriverStatus::ON_ROUTE) {
                        cout << "[Blocked] Already ON_ROUTE. End shift first (option 3).\n";
                    }
                    else {
                        TripDirection dir = TripDirection::ARRIVAL;
                        if (isVanDriver) {
                            string dirStr = getRobustInput("Direction (0=ARRIVAL, 1=DEPARTURE): ");
                            if (dirStr == "1") {
                                dir = TripDirection::DEPARTURE;
                            }
                            else if (dirStr != "0") {
                                cout << "[Error] Enter 0 for ARRIVAL or 1 for DEPARTURE.\n";
                                continue;
                            }
                        }
                        if (controller.dispatchTrip(vId, dir)) {
                            activeDriver->setStatus(DriverStatus::ON_ROUTE);
                            controller.saveUsersToFile();
                            cout << "[Driver] " << tripDirectionToString(dir) << " trip started.\n";
                        }
                    }
                }
                else if (opt == 2) {
                    if (isVanDriver) {
                        cout << "[Info] VAN dispatch: use option 1 and enter 1 for DEPARTURE.\n";
                    }
                    else if (vId.empty()) {
                        cout << "[Blocked] No vehicle assigned.\n";
                    }
                    else if (activeDriver->getStatus() == DriverStatus::ON_ROUTE) {
                        cout << "[Blocked] Already ON_ROUTE. End shift first (option 3).\n";
                    }
                    else if (controller.dispatchTrip(vId, TripDirection::DEPARTURE)) {
                        activeDriver->setStatus(DriverStatus::ON_ROUTE);
                        controller.saveUsersToFile();
                        cout << "[Driver] DEPARTURE trip started.\n";
                    }
                }
                else if (opt == 3) {
                    if (activeDriver->getStatus() == DriverStatus::FREE)
                        cout << "[Blocked] Already FREE.\n";
                    else {
                        activeDriver->setStatus(DriverStatus::FREE);
                        controller.saveUsersToFile();
                        cout << "[Driver] Shift ended. Status: FREE.\n";
                    }
                }
                else if (opt == 4) {
                    if (vId.empty()) { cout << "[Blocked] No vehicle coupled.\n"; continue; }
                    string litersStr = getRobustInput("Liters purchased: ");
                    string costStr = getRobustInput("Total cost (Rs): ");
                    double liters = 0, cost = 0;
                    try {
                        liters = stod(cleanNumericString(litersStr));
                        cost = stod(cleanNumericString(costStr));
                    }
                    catch (...) { cout << "[Error] Invalid numbers.\n"; continue; }
                    if (liters <= 0 || cost <= 0) { cout << "[Error] Values must be positive.\n"; continue; }
                    PetrolLog newLog{ "L-" + to_string(controller.petrolLogs.size() + 100),
                        vId, DateUtil::getCurrentDate(), liters, cost,
                        activeDriver->getSystemId() };
                    controller.logPetrol(newLog);
                    cout << "[Fuel] Manual purchase archived.\n";
                }
                else if (opt == 5) {
                    if (vId.empty()) cout << "[Blocked] No vehicle assigned.\n";
                    else controller.viewDailyTripSummary(vId);
                }
                else cout << "[Error] Invalid option.\n";
            }
        }
    }
    return 0;
}