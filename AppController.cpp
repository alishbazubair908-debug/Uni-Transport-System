#include "AppController.h"
using namespace std;

// ═══════════════════════════════════════════════════════════════
// FILE I/O
// ═══════════════════════════════════════════════════════════════

void AppController::saveUsersToFile()
{
    ofstream file("users_database.txt");
    if (!file.is_open()) return;
    for (const auto& kv : users) 
    {
        const auto& p = kv.second;
        file << p->getRole() << ","
            << p->getSystemId() << ","
            << sanitizeCsv(p->getName()) << ","
            << p->getCNIC() << ","
            << sanitizeCsv(p->getAddress()) << ","
            << p->getEmail() << ","
            << p->getPhone() << ","
            << p->getAge() << ","
            << genderToString(p->getGender()) << ","
            << p->getPassword();

        if (p->getRole() == "Admin") {
            auto a = dynamic_pointer_cast<Admin>(p);
            if (a) file << "," << sanitizeCsv(a->getDesignation())
                << "," << a->getSalary()
                << "," << a->getHireDate()
                << "," << adminRoleToString(a->getAdminRole());
        }
        else if (p->getRole() == "Driver") {
            auto d = dynamic_pointer_cast<Driver>(p);
            if (d) file << "," << sanitizeCsv(d->getDesignation())
                << "," << d->getSalary()
                << "," << d->getHireDate()
                << "," << d->getLicenseNumber()
                << "," << (d->getStatus() == DriverStatus::ON_ROUTE ? "1" : "0")
                << "," << d->getAssignedVehicle();
        }
        else if (p->getRole() == "Student") {
            auto s = dynamic_pointer_cast<Student>(p);
            if (s) file << "," << s->getRollNumber()
                << "," << sanitizeCsv(s->getDepartment())
                << "," << s->getSemester()
                << "," << (s->hasActivePass() ? "1" : "0");
        }
        file << "\n";
    }
}

void AppController::loadUsersFromFile()
{
    cout << "[Boot] Reading 'users_database.txt'...\n";
    ifstream file("users_database.txt");
    if (!file.is_open()) { cout << "[Boot] No user DB found. Fresh start.\n"; return; }

    string line; int loaded = 0;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream    ss(line);
        vector<string>  t;
        string          tok;
        while (getline(ss, tok, ',')) t.push_back(tok);
        if (t.size() < 10) continue;

        string role = t[0], sysId = t[1], nm = t[2], cn = t[3],
            addr = t[4], em = t[5], ph = t[6], pw = t[9];
        int ag = 0;
        try { ag = stoi(t[7]); }
        catch (...) {}
        Gender gn = genderFromString(t[8]);

        shared_ptr<Person> p;
        if (role == "Admin" && t.size() >= 14) {
            double sal = 0;
            try { sal = stod(t[11]); }
            catch (...) {}
            AdminRole ar = adminRoleFromString(t[13]);
            p = make_shared<Admin>(sysId, nm, cn, addr, em, ph,
                ag, gn, pw, t[10], sal, t[12], ar);
        }
        else if (role == "Driver" && t.size() >= 16) {
            double sal = 0;
            try { sal = stod(t[11]); }
            catch (...) {}
            string av = (t.size() > 15) ? t[15] : "";
            auto d = make_shared<Driver>(sysId, nm, cn, addr, em, ph,
                ag, gn, pw, t[10], sal, t[12], t[13]);
            d->setStatus(t[14] == "1" ? DriverStatus::ON_ROUTE : DriverStatus::FREE);
            d->setAssignedVehicle(av);
            p = d;
        }
        else if (role == "Student" && t.size() >= 14) {
            auto s = make_shared<Student>(sysId, nm, cn, addr, em, ph,
                ag, gn, pw, t[10], t[11], t[12]);
            if (t[13] == "1") s->setPassStatus(true);
            p = s;
        }
        if (p) { users[sysId] = p; loaded++; }
    }
    cout << "[Boot] Loaded " << loaded << " accounts.\n";
}

void AppController::savePendingRegistrationsToFile() {
    ofstream file("pending_registrations.txt");
    if (!file.is_open()) return;
    for (const auto& r : pendingRegistrations)
        file << r.to_string() << "\n";
}

void AppController::loadPendingRegistrationsToFile() {
    ifstream file("pending_registrations.txt");
    if (!file.is_open()) return;
    pendingRegistrations.clear();
    string line;
    while (getline(file, line))
        if (!line.empty())
            pendingRegistrations.push_back(PendingRegistration::from_string(line));
}

void AppController::saveVehiclesToFile() {
    ofstream file("vehicles_database.txt");
    if (!file.is_open()) return;
    for (const auto& v : vehicles) {
        file << v.getVehicleId() << ","
            << v.getLicensePlate() << ","
            << vehicleTypeToString(v.getType()) << ","
            << v.getCapacity() << ","
            << v.getOccupiedSeats() << ","
            << v.getCurrentDriverId() << ","
            << v.getAssignedRouteId() << ","
            << v.getFuelEfficiency() << ","
            << v.getFuelType();
        if (v.isVAN()) {
            string purp = v.getVanPurpose();
            for (char& c : purp) if (c == ',') c = ';';
            file << "," << purp << "," << v.getVanDailyMileage();
        }
        file << "\n";
    }
}

void AppController::loadVehiclesFromFile() {
    ifstream file("vehicles_database.txt");
    if (!file.is_open()) return;
    vehicles.clear();
    string line; int lineNum = 0;
    while (getline(file, line)) {
        ++lineNum;
        if (line.empty()) continue;
        stringstream ss(line);
        string vId, plate, typeStr, capStr, occStr,
            driverId, routeId, effStr, fType;
        getline(ss, vId, ','); getline(ss, plate, ',');
        getline(ss, typeStr, ','); getline(ss, capStr, ',');
        getline(ss, occStr, ','); getline(ss, driverId, ',');
        getline(ss, routeId, ','); getline(ss, effStr, ',');
        getline(ss, fType, ',');
        try {
            int    cap = stoi(capStr), occ = stoi(occStr);
            double eff = stod(effStr);
            VehicleType vt = vehicleTypeFromString(typeStr);
            if (vt == VehicleType::VAN) {
                string purp, dMileageStr;
                getline(ss, purp, ','); getline(ss, dMileageStr, ',');
                double dMileage = 0;
                try { dMileage = stod(dMileageStr); }
                catch (...) {
                    cerr << "[Warn] VAN mileage malformed on line " << lineNum << "\n";
                }
                Vehicle v(vId, plate, cap, eff, fType, purp, dMileage);
                v.setOccupiedSeats(occ); v.setDriver(driverId);
                v.setAssignedRouteId(routeId);
                vehicles.push_back(v);
            }
            else {
                Vehicle v(vId, plate, vt, cap, eff, fType);
                v.setOccupiedSeats(occ); v.setDriver(driverId);
                v.setAssignedRouteId(routeId);
                vehicles.push_back(v);
            }
        }
        catch (...) {
            cerr << "[Warn] Skipped malformed vehicle on line "
                << lineNum << ": " << vId << "\n";
        }
    }
}

void AppController::saveRoutesToFile() {
    ofstream file("routes_database.txt");
    if (!file.is_open()) return;
    for (const auto& r : routes) {
        file << "ROUTE," << r.getRouteId() << ","
            << r.getRouteName() << ","
            << r.getApproxKilometer() << "\n";
        for (const auto& s : r.getStops())
            file << "STOP," << r.getRouteId() << ","
            << s.stopId << "," << s.stopName << ","
             << "," << s.arrivalTime << "\n";
    }
}

void AppController::loadRoutesFromFile() {
    ifstream file("routes_database.txt");
    if (!file.is_open()) return;
    routes.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string tag; getline(ss, tag, ',');
        if (tag == "ROUTE") {
            string rId, rName, kmStr, dummy;
            getline(ss, rId, ','); getline(ss, rName, ',');
            getline(ss, kmStr, ','); getline(ss, dummy, ',');
            try { routes.push_back(Route(rId, rName, {}, stod(kmStr))); }
            catch (...) {}
        }
        else if (tag == "STOP") {
            string rId, sId, sName, coord, arrTime;
            getline(ss, rId, ','); getline(ss, sId, ',');
            getline(ss, sName, ','); getline(ss, coord, ',');
            getline(ss, arrTime, ',');
            auto rIt = find_if(routes.begin(), routes.end(),
                [&](const Route& r) { return r.getRouteId() == rId; });
            if (rIt != routes.end())
                rIt->addStop({ sId, sName, arrTime });
        }
    }
}

void AppController::savePassesToFile() {
    ofstream file("passes_database.txt");
    if (!file.is_open()) return;
    for (const auto& p : passes)
        file << p.getPassId() << "," << p.getStudentId() << ","
        << p.getRouteId() << "," << p.getChosenStop() << ","
        << p.getIssueDate() << "," << p.getExpiryDate() << ","
        << passStatusToString(p.getStatus()) << "\n";
}

void AppController::loadPassesFromFile() {
    ifstream file("passes_database.txt");
    if (!file.is_open()) return;
    passes.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string pId, sId, rId, stop, iDate, eDate, statusStr;
        getline(ss, pId, ','); getline(ss, sId, ',');
        getline(ss, rId, ','); getline(ss, stop, ',');
        getline(ss, iDate, ','); getline(ss, eDate, ',');
        getline(ss, statusStr, ',');
        passes.push_back(TransportPass(pId, sId, rId, stop,
            iDate, eDate, passStatusFromString(statusStr)));
    }
}

void AppController::saveBillsToFile() {
    ofstream file("bills_database.txt");
    if (!file.is_open()) return;
    for (const auto& b : bills)
        file << b.billId << "," << b.studentId << ","
        << b.amount << "," << b.dueDate << ","
        << (b.isPaid ? "1" : "0") << "\n";
}

void AppController::loadBillsFromFile() {
    ifstream file("bills_database.txt");
    if (!file.is_open()) return;
    bills.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string bId, sId, amtStr, due, paidStr;
        getline(ss, bId, ','); getline(ss, sId, ',');
        getline(ss, amtStr, ','); getline(ss, due, ',');
        getline(ss, paidStr, ',');
        try {
            Bill b;
            b.billId = bId;    b.studentId = sId;
            b.amount = stod(amtStr);
            b.dueDate = due;    b.isPaid = (paidStr == "1");
            bills.push_back(b);
        }
        catch (...) {}
    }
}

void AppController::savePaymentsToFile() {
    ofstream file("payments_database.txt");
    if (!file.is_open()) return;
    for (const auto& pr : paymentRecords)
        file << pr.paymentId << "," << pr.billId << ","
        << pr.amountPaid << "," << pr.paymentDate << ","
        << pr.paymentMethod << "\n";
}

void AppController::loadPaymentsFromFile() {
    ifstream file("payments_database.txt");
    if (!file.is_open()) return;
    paymentRecords.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string pId, bId, amtStr, date, method;
        getline(ss, pId, ','); getline(ss, bId, ',');
        getline(ss, amtStr, ','); getline(ss, date, ',');
        getline(ss, method, ',');
        try {
            PaymentRecord pr;
            pr.paymentId = pId;  pr.billId = bId;
            pr.amountPaid = stod(amtStr);
            pr.paymentDate = date; pr.paymentMethod = method;
            paymentRecords.push_back(pr);
        }
        catch (...) {}
    }
}

void AppController::saveWaitlistsToFile() {
    ofstream file("waitlists_database.txt");
    if (!file.is_open()) return;
    for (const auto& kv : routeWaitlists) {
        auto tmpQ = kv.second;
        while (!tmpQ.empty()) {
            file << kv.first << "," << tmpQ.front() << "\n";
            tmpQ.pop();
        }
    }
}

void AppController::loadWaitlistsFromFile() {
    ifstream file("waitlists_database.txt");
    if (!file.is_open()) return;
    routeWaitlists.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string routeId, studentId;
        if (getline(ss, routeId, ',') && getline(ss, studentId))
            routeWaitlists[trim(routeId)].push(trim(studentId));
    }
}

void AppController::saveTripLogsToFile() {
    ofstream file("trip_logs.txt");
    if (!file.is_open()) return;
    for (const auto& t : tripLogs) file << t.to_string() << "\n";
}

void AppController::loadTripLogsFromFile() {
    ifstream file("trip_logs.txt");
    if (!file.is_open()) return;
    tripLogs.clear();
    string line;
    while (getline(file, line))
        if (!line.empty()) tripLogs.push_back(TripLog::from_string(line));
}

void AppController::savePetrolLogsToFile() {
    ofstream file("petrol_logs_archive.txt");
    if (!file.is_open()) return;
    for (const auto& p : petrolLogs) file << p.to_string() << "\n";
}

void AppController::loadPetrolLogsFromFile() {
    ifstream file("petrol_logs_archive.txt");
    if (!file.is_open()) return;
    petrolLogs.clear();
    string line;
    while (getline(file, line))
        if (!line.empty()) petrolLogs.push_back(PetrolLog::from_string(line));
}

void AppController::saveMonthlyCapitalToFile() {
    ofstream file("monthly_capital.txt");
    if (!file.is_open()) return;
    for (const auto& kv : monthlyCapitals) {
        const auto& mc = kv.second;
        file << mc.month << "," << fixed << setprecision(2)
            << mc.totalCapital << "," << mc.spentOnFuel << "\n";
    }
    file << "PETROL_PRICE," << petrolPricePerLitre << "\n";
}

void AppController::loadMonthlyCapitalFromFile() {
    ifstream file("monthly_capital.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string t1, t2, t3;
        getline(ss, t1, ','); getline(ss, t2, ','); getline(ss, t3, ',');
        if (t1 == "PETROL_PRICE") {
            try { petrolPricePerLitre = stod(t2); }
            catch (...) {}
            continue;
        }
        try {
            MonthlyCapital mc;
            mc.month = t1;
            mc.totalCapital = stod(t2);
            mc.spentOnFuel = stod(t3);
            monthlyCapitals[mc.month] = mc;
        }
        catch (...) {}
    }
}

// ═══════════════════════════════════════════════════════════════
// SYSTEM PIPELINES
// ═══════════════════════════════════════════════════════════════

void AppController::sweepExpiredPasses() {
    string today = DateUtil::getCurrentDate();
    bool   changed = false;
    for (auto& p : passes)
    {
        if (p.getStatus() == PassStatus::ACTIVE && p.getExpiryDate() < today) {
            p.setStatus(PassStatus::EXPIRED);
            changed = true;
            auto uIt = users.find(p.getStudentId());
            if (uIt != users.end() && uIt->second->getRole() == "Student") {
                auto sp = dynamic_pointer_cast<Student>(uIt->second);
                if (sp) sp->setPassStatus(false);
            }
            string routeId = p.getRouteId();
            bool   seatFreed = false;
            for (auto& v : vehicles) {
                if (v.getAssignedRouteId() == routeId && v.getOccupiedSeats() > 0) {
                    v.decrementOccupiedSeats();
                    cout << "[Sweep] Pass " << p.getPassId()
                        << " expired. Seat freed on " << v.getVehicleId() << ".\n";
                    seatFreed = true; break;
                }
            }
            if (!seatFreed)
                cout << "[Sweep] Pass " << p.getPassId() << " expired (no seat freed).\n";
            processRouteWaitlist(routeId);
        }
    }
    if (changed) { saveUsersToFile(); saveVehiclesToFile(); savePassesToFile(); }
}

bool AppController::registerUser(const shared_ptr<Person>& person) {
    if (!ValidationUtil::isValidName(person->getName())) {
        cout << "[Error] Name must contain letters only (spaces, hyphens, dots allowed).\n";
        return false;
    }
    if (!ValidationUtil::isValidEmail(person->getEmail())) {
        cout << "[Error] Invalid email format.\n"; return false;
    }
    if (!ValidationUtil::isValidPassword(person->getPassword())) {
        cout << "[Error] Password must be 8+ characters.\n"; return false;
    }
    if (!ValidationUtil::isValidCNIC(person->getCNIC())) {
        cout << "[Error] Invalid CNIC. Use: XXXXX-XXXXXXX-X\n"; return false;
    }
    if (!ValidationUtil::isValidPhone(person->getPhone())) {
        cout << "[Error] Invalid phone. Use: 03XX-XXXXXXX or +923XXXXXXXXX\n"; return false;
    }
    if (!ValidationUtil::isValidAddress(person->getAddress())) {
        cout << "[Error] Address must be 5+ chars.\n"; return false;
    }
    if (users.find(person->getSystemId()) != users.end()) {
        cout << "[Error] System ID '" << person->getSystemId() << "' already in use.\n";
        return false;
    }
    for (const auto& kv : users)
        if (kv.second->getCNIC() == person->getCNIC()) {
            cout << "[Error] CNIC already registered.\n"; return false;
        }
    if (person->getRole() == "Admin") {
        auto a = dynamic_pointer_cast<Admin>(person);
        if (a) {
            for (const auto& kv : users)
                if (kv.second->getRole() == "Admin") {
                    auto ea = dynamic_pointer_cast<Admin>(kv.second);
                    if (ea && ea->getAdminRole() == a->getAdminRole() &&
                        a->getAdminRole() != AdminRole::SUPER_ADMIN) {
                        cout << "[Error] Only one " << adminRoleToString(a->getAdminRole())
                            << " allowed.\n";
                        return false;
                    }
                }
        }
    }
    if (auto emp = dynamic_pointer_cast<Employee>(person)) {
        if (!ValidationUtil::isValidDesignation(emp->getDesignation())) {
            cout << "[Error] Designation must be 1-60 chars.\n"; return false;
        }
        if (!ValidationUtil::isValidSalary(emp->getSalary())) {
            cout << "[Error] Salary must be Rs 15,000-500,000.\n"; return false;
        }
        if (!ValidationUtil::isValidHireDate(emp->getHireDate())) {
            cout << "[Error] Hire date must be YYYY-MM-DD.\n"; return false;
        }
    }
    if (person->getRole() == "Driver") {
        auto d = dynamic_pointer_cast<Driver>(person);
        if (d && !ValidationUtil::isValidLicense(d->getLicenseNumber())) {
            cout << "[Error] License must be 6+ alphanumeric chars.\n"; return false;
        }
    }
    if (person->getRole() == "Student") {
        auto s = dynamic_pointer_cast<Student>(person);
        if (s) {
            if (!ValidationUtil::isValidRollNumber(s->getRollNumber())) {
                cout << "[Error] Roll number must be 5+ chars.\n"; return false;
            }
            if (!ValidationUtil::isValidSemester(s->getSemester())) {
                cout << "[Error] Semester must be 1-8.\n"; return false;
            }
            if (!ValidationUtil::isValidDepartment(s->getDepartment())) {
                cout << "[Error] Department must contain letters only.\n"; return false;
            }
        }
    }
    users[person->getSystemId()] = person;
    saveUsersToFile();
    cout << "[System] Account created. System ID: " << person->getSystemId() << "\n";
    return true;
}

void AppController::addVehicle(const Vehicle& vehicle) {
    if (!ValidationUtil::isValidVehiclePlate(vehicle.getLicensePlate())) {
        cout << "[Error] Invalid plate format. Use ABC-1234.\n"; return;
    }
    vehicles.push_back(vehicle);
    saveVehiclesToFile();
    cout << "[System] Vehicle registered: " << vehicle.getVehicleId() << "\n";
    if (vehicle.isVAN()) vehicle.printVanDetails(petrolPricePerLitre);
}

bool AppController::removeVehicle(const string& vehicleId) {
    auto vIt = find_if(vehicles.begin(), vehicles.end(),
        [&](const Vehicle& v) { return v.getVehicleId() == vehicleId; });
    if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return false; }

    shared_ptr<Driver> coupled = nullptr;
    for (const auto& kv : users)
        if (kv.second->getRole() == "Driver") {
            auto d = dynamic_pointer_cast<Driver>(kv.second);
            if (d && d->getAssignedVehicle() == vehicleId) { coupled = d; break; }
        }
    if (coupled && coupled->getStatus() == DriverStatus::ON_ROUTE) {
        cout << "[Blocked] Vehicle " << vehicleId
            << " cannot be removed — driver is ON_ROUTE.\n";
        return false;
    }
    if (coupled) {
        coupled->setAssignedVehicle(""); saveUsersToFile();
        cout << "[System] Driver " << coupled->getSystemId()
            << " uncoupled from " << vehicleId << ".\n";
    }
    vehicles.erase(vIt);
    saveVehiclesToFile();
    cout << "[System] Vehicle " << vehicleId << " removed.\n";
    return true;
}

void AppController::addRoute(const Route& route) {
    routes.push_back(route);
    saveRoutesToFile();
    cout << "[System] Route registered: " << route.getRouteName() << "\n";
}

bool AppController::assignVehicleToRoute(const string& vehicleId,
    const string& routeId) {
    auto vIt = find_if(vehicles.begin(), vehicles.end(),
        [&](const Vehicle& v) { return v.getVehicleId() == vehicleId; });
    if (vIt == vehicles.end()) {
        cout << "[Error] Vehicle '" << vehicleId << "' not found.\n"; return false;
    }
    if (vIt->isVAN()) {
        cout << "[Blocked] VANs are campus-only and cannot be assigned to student routes.\n";
        return false;
    }
    auto rIt = find_if(routes.begin(), routes.end(),
        [&](const Route& r) { return r.getRouteId() == routeId; });
    if (rIt == routes.end()) {
        cout << "[Error] Route '" << routeId << "' not found.\n"; return false;
    }
    if (!vIt->getAssignedRouteId().empty() && vIt->getAssignedRouteId() != routeId) {
        cout << "[Blocked] Vehicle already assigned to Route "
            << vIt->getAssignedRouteId() << ". Unassign first.\n";
        return false;
    }
    if (vIt->getAssignedRouteId() == routeId) {
        cout << "[Info] Vehicle " << vehicleId << " already on Route " << routeId << ".\n";
        return true;
    }
    vIt->setAssignedRouteId(routeId);
    saveVehiclesToFile();
    return true;
}

void AppController::assignDriverToVehicle(const string& driverId,
    const string& vehicleId) {
    auto dIt = users.find(driverId);
    if (dIt == users.end() || dIt->second->getRole() != "Driver")
    {
        cout << "[Error] Driver " << driverId << " not found.\n"; return;
    }
    auto driver = dynamic_pointer_cast<Driver>(dIt->second);
    if (!driver) return;

    auto vIt = find_if(vehicles.begin(), vehicles.end(),
        [&](const Vehicle& v) { return v.getVehicleId() == vehicleId; });
    if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return; }
    if (!vIt->getCurrentDriverId().empty()) {
        cout << "[Error] Vehicle already has driver: "
            << vIt->getCurrentDriverId() << "\n"; return;
    }
    if (!driver->getAssignedVehicle().empty())
    {
        cout << "[Error] Driver already assigned to: "
            << driver->getAssignedVehicle() << "\n"; return;
    }
    vIt->setDriver(driverId);
    driver->setAssignedVehicle(vehicleId);
    saveUsersToFile(); saveVehiclesToFile();
    cout << "[System] Coupled Driver " << driverId
        << " with Vehicle " << vehicleId << ".\n";
}

void AppController::unassignDriverFromVehicle(const string& driverId) {
    auto dIt = users.find(driverId);
    if (dIt == users.end() || dIt->second->getRole() != "Driver") {
        cout << "[Error] Driver not found.\n"; return;
    }
    auto driver = dynamic_pointer_cast<Driver>(dIt->second);
    if (!driver || driver->getAssignedVehicle().empty()) {
        cout << "[Error] Driver has no vehicle assigned.\n"; return;
    }
    if (driver->getStatus() == DriverStatus::ON_ROUTE) {
        cout << "[Blocked] Cannot unassign driver while ON_ROUTE.\n"; return;
    }
    string vId = driver->getAssignedVehicle();
    for (auto& v : vehicles) if (v.getVehicleId() == vId) { v.setDriver(""); break; }
    driver->setAssignedVehicle("");
    saveUsersToFile(); saveVehiclesToFile();
    cout << "[System] Driver " << driverId
        << " uncoupled from vehicle " << vId << ".\n";
}

bool AppController::isVehiclePlateInUse(const string& plate,
    const string& excludeVehicleId) const {
    for (const auto& v : vehicles)
        if (v.getVehicleId() != excludeVehicleId && v.getLicensePlate() == plate)
            return true;
    return false;
}

// ═══════════════════════════════════════════════════════════════
// PASS MANAGEMENT
// ═══════════════════════════════════════════════════════════════

void AppController::requestPass(const string& studentId,const string& routeId,const string& stopName)
{
    sweepExpiredPasses();
    bool routeExists = any_of(routes.begin(), routes.end(),
        [&](const Route& r) { return r.getRouteId() == routeId; });
    if (!routeExists) {
        cout << "[Error] Route '" << routeId << "' does not exist.\n"; return;
    }
    if (!isStopOnRoute(routeId, stopName)) {
        cout << "[Error] Stop '" << stopName << "' not on route " << routeId << ".\n";
        return;
    }
    const Vehicle* assignedVan = nullptr;
    for (const auto& v : vehicles)
        if (v.isVAN() && v.getAssignedRouteId() == routeId
            && v.getCapacity() > 0 && v.getVanDailyMileage() > 0.0) {
            assignedVan = &v; break;
        }
    bool routeHasVan = (assignedVan != nullptr);
    if (routeHasVan) {
        auto uIt = users.find(studentId);
        if (uIt != users.end() && uIt->second->getRole() == "Student") {
            auto sp = dynamic_pointer_cast<Student>(uIt->second);
            if (sp) {
                int sem = 0;
                try { sem = stoi(sp->getSemester()); }
                catch (...) {}
                if (sem > 8) {
                    cout << "[Blocked] VAN routes restricted to Semester 1-8.\n"
                        << "          Your semester: " << sp->getSemester() << "\n";
                    return;
                }
            }
        }
    }
    bool hasLivePass = false;
    for (const auto& p : passes)
        if (p.getStudentId() == studentId &&
            (p.getStatus() == PassStatus::PENDING_PAYMENT ||
                p.getStatus() == PassStatus::ACTIVE ||
                p.getStatus() == PassStatus::WAITLISTED)) {
            hasLivePass = true; break;
        }
    if (hasLivePass) {
        cout << "[Blocked] You already have an active, pending, or waitlisted pass.\n";
        return;
    }
    auto uIt = users.find(studentId);
    if (uIt != users.end() && uIt->second->getRole() == "Student") 
    {
        auto sp = dynamic_pointer_cast<Student>(uIt->second);
        if (sp) sp->setPassStatus(false);
    }
    string passId = "PASS-" + to_string(gCounters.billNext);
    string billId = "BILL-" + to_string(gCounters.billNext++);
    gCounters.saveToFile();
    double billAmount = 200.0;
    string surchargeNote = "";
    if (routeHasVan && assignedVan != nullptr) {
        double estDailyFuel = assignedVan->getVanEstimatedDailyFuelCost(petrolPricePerLitre);
        int    cap = assignedVan->getCapacity();
        double surcharge = static_cast<double>(
            static_cast<int>((estDailyFuel * 20.0) / cap + 0.5));
        billAmount += surcharge;
        ostringstream sn;
        sn << fixed << setprecision(2)
            << " (Base Rs 200.00 + VAN surcharge Rs " << surcharge
            << " = Rs " << billAmount << ")";
        surchargeNote = sn.str();
    }
    passes.emplace_back(passId, studentId, routeId, stopName);
    bills.push_back({ billId, studentId, billAmount, "2026-06-30", false });
    savePassesToFile(); saveBillsToFile();
    cout << "[System] Pass request submitted. Invoice " << billId
        << " for Rs " << fixed << setprecision(2) << billAmount
        << " generated." << surchargeNote
        << "\nPay at Finance Console to activate.\n";
}

void AppController::requestPassChange(const string& studentId,
    const string& newRouteId,
    const string& newStopName) {
    sweepExpiredPasses();
    TransportPass* livePass = nullptr;
    for (auto& p : passes)
        if (p.getStudentId() == studentId &&
            (p.getStatus() == PassStatus::ACTIVE ||
                p.getStatus() == PassStatus::WAITLISTED)) {
            livePass = &p; break;
        }
    if (!livePass) {
        cout << "[Info] No active/waitlisted pass found. Submitting fresh request.\n";
        requestPass(studentId, newRouteId, newStopName);
        return;
    }
    if (livePass->getRouteId() == newRouteId) {
        cout << "[Info] Already assigned to route " << newRouteId << ".\n"; return;
    }
    int seatsAvailable = getRemainingSeatsForRoute(newRouteId);
    cout << "[Change Request] This will cancel your current pass on route "
        << livePass->getRouteId() << " and request route " << newRouteId << ".\n";
    if (seatsAvailable == 0)
        cout << "[Info] Route " << newRouteId << " has no seats — you will be waitlisted.\n";
    else
        cout << "[Info] Route " << newRouteId << " has " << seatsAvailable << " seat(s).\n";
    string confirm = getRobustInput("Confirm route change? (y/n): ");
    if (confirm != "y" && confirm != "Y") { cout << "[Cancelled]\n"; return; }

    PassStatus oldStatus = livePass->getStatus();
    string     oldRouteId = livePass->getRouteId();

    if (oldStatus == PassStatus::ACTIVE) {
        for (auto& v : vehicles)
            if (v.getAssignedRouteId() == oldRouteId && v.getOccupiedSeats() > 0) {
                v.decrementOccupiedSeats();
                cout << "[Change] Seat freed on " << v.getVehicleId() << ".\n"; break;
            }
    }
    else {
        auto wIt = routeWaitlists.find(oldRouteId);
        if (wIt != routeWaitlists.end()) {
            queue<string> newQ; auto tmpQ = wIt->second;
            while (!tmpQ.empty()) {
                if (tmpQ.front() != studentId) newQ.push(tmpQ.front());
                tmpQ.pop();
            }
            wIt->second = newQ;
        }
    }
    livePass->setStatus(PassStatus::EXPIRED);
    auto uIt = users.find(studentId);
    if (uIt != users.end() && uIt->second->getRole() == "Student") {
        auto sp = dynamic_pointer_cast<Student>(uIt->second);
        if (sp) sp->setPassStatus(false);
    }
    saveVehiclesToFile(); savePassesToFile();
    saveUsersToFile();    saveWaitlistsToFile();
    cout << "[Change] Old pass cancelled. Opening old route waitlist...\n";
    processRouteWaitlist(oldRouteId);

    bool routeExists = any_of(routes.begin(), routes.end(),
        [&](const Route& r) { return r.getRouteId() == newRouteId; });
    if (!routeExists) {
        cout << "[Error] Route '" << newRouteId << "' does not exist.\n"; return;
    }
    if (!isStopOnRoute(newRouteId, newStopName)) {
        cout << "[Error] Stop '" << newStopName << "' not on route " << newRouteId << ".\n";
        return;
    }
    string passId = "PASS-" + to_string(gCounters.billNext);
    string billId = "BILL-" + to_string(gCounters.billNext++);
    gCounters.saveToFile();
    passes.emplace_back(passId, studentId, newRouteId, newStopName);
    bills.push_back({ billId, studentId, 0.0, "2026-06-30", true });
    string payId = "PAY-" + to_string(gCounters.payNext++);
    gCounters.saveToFile();
    paymentRecords.push_back({ payId, billId, 0.0,
        DateUtil::getCurrentDate(), "Route Transfer (pre-paid)" });
    savePassesToFile(); saveBillsToFile(); savePaymentsToFile();
    cout << "[System] Route change recorded. No additional charge.\n"
        << "         New pass " << passId << " pending Finance activation.\n";
}

void AppController::financeClearPass(const string& passId) {
    auto pIt = find_if(passes.begin(), passes.end(),
        [&](const TransportPass& p) { return p.getPassId() == passId; });
    if (pIt == passes.end()) { cout << "[Error] Pass not found.\n"; return; }
    if (pIt->getStatus() != PassStatus::PENDING_PAYMENT) {
        cout << "[Error] Pass not pending payment (status: "
            << passStatusToString(pIt->getStatus()) << ").\n"; return;
    }
    string passSuffix = "";
    size_t dashPos = passId.find('-');
    if (dashPos != string::npos) passSuffix = passId.substr(dashPos + 1);
    string targetBillId = "BILL-" + passSuffix;

    auto bIt = find_if(bills.begin(), bills.end(), [&](const Bill& b) {
        return b.billId == targetBillId && b.studentId == pIt->getStudentId();
        });
    if (bIt == bills.end()) {
        cout << "[Error] Bill (" << targetBillId << ") not found.\n"; return;
    }
    if (!bIt->isPaid) {
        bIt->isPaid = true;
        string payId = "PAY-" + to_string(gCounters.payNext++);
        gCounters.saveToFile();
        paymentRecords.push_back({ payId, bIt->billId, bIt->amount,
            DateUtil::getCurrentDate(), "University Cashier" });
    }
    string   targetRoute = pIt->getRouteId();
    Vehicle* targetVehicle = nullptr;
    for (auto& v : vehicles)
        if (v.getAssignedRouteId() == targetRoute && v.getRemainingSeats() > 0) {
            targetVehicle = &v; break;
        }
    if (targetVehicle) {
        targetVehicle->incrementOccupiedSeats();
        pIt->activate(DateUtil::getCurrentDate(),
            DateUtil::calculateExpiryDate(180));
        string sSem = "", sDept = "", vanInfo = "";
        auto uIt = users.find(pIt->getStudentId());
        if (uIt != users.end() && uIt->second->getRole() == "Student") {
            auto sp = dynamic_pointer_cast<Student>(uIt->second);
            if (sp) {
                sp->setPassStatus(true);
                sSem = sp->getSemester(); sDept = sp->getDepartment();
            }
        }
        if (targetVehicle->isVAN()) {
            ostringstream vi;
            vi << "VAN " << targetVehicle->getVehicleId()
                << " | Purpose: " << targetVehicle->getVanPurpose()
                << " | Daily Mileage: " << targetVehicle->getVanDailyMileage() << " km";
            vanInfo = vi.str();
            cout << "[VAN] Student assigned. Daily mileage: "
                << targetVehicle->getVanDailyMileage() << " km | Est. fuel cost/trip: Rs "
                << fixed << setprecision(2)
                << targetVehicle->getVanEstimatedDailyFuelCost(petrolPricePerLitre) << "\n";
        }
        cout << "[System] Payment cleared! Seat reserved on "
            << targetVehicle->getVehicleId() << ". Pass " << passId << " ACTIVE.\n";
        PDFGenerator::generatePassPDF(pIt->getPassId(), pIt->getStudentId(),
            pIt->getRouteId(), pIt->getExpiryDate(), sSem, sDept, vanInfo);
    }
    else {
        pIt->setStatus(PassStatus::WAITLISTED);
        routeWaitlists[targetRoute].push(pIt->getStudentId());
        cout << "[System] Payment cleared. Route " << targetRoute
            << " full — student waitlisted.\n";
    }
    saveUsersToFile(); saveVehiclesToFile(); savePassesToFile();
    saveBillsToFile(); savePaymentsToFile(); saveWaitlistsToFile();
}

void AppController::cancelPass(const string& passId) {
    auto pIt = find_if(passes.begin(), passes.end(),
        [&](const TransportPass& p) { return p.getPassId() == passId; });
    if (pIt == passes.end()) { cout << "[Error] Pass not found.\n"; return; }
    if (pIt->getStatus() != PassStatus::ACTIVE &&
        pIt->getStatus() != PassStatus::WAITLISTED) {
        cout << "[Error] Only ACTIVE or WAITLISTED passes can be cancelled.\n"; return;
    }
    string routeId = pIt->getRouteId();
    if (pIt->getStatus() == PassStatus::ACTIVE) 
    {
        for (auto& v : vehicles)
            if (v.getAssignedRouteId() == routeId && v.getOccupiedSeats() > 0) {
                v.decrementOccupiedSeats();
                cout << "[Cancel] Seat freed on " << v.getVehicleId() << ".\n"; break;
            }
    }
    else
    {
        auto wIt = routeWaitlists.find(routeId);
        if (wIt != routeWaitlists.end()) {
            queue<string> newQ; auto tmpQ = wIt->second;
            while (!tmpQ.empty()) {
                if (tmpQ.front() != pIt->getStudentId()) newQ.push(tmpQ.front());
                tmpQ.pop();
            }
            wIt->second = newQ;
        }
    }
    pIt->setStatus(PassStatus::EXPIRED);
    auto uIt = users.find(pIt->getStudentId());
    if (uIt != users.end() && uIt->second->getRole() == "Student") {
        auto sp = dynamic_pointer_cast<Student>(uIt->second);
        if (sp) sp->setPassStatus(false);
    }
    cout << "[System] Pass " << passId << " cancelled and marked EXPIRED.\n";
    savePassesToFile(); saveVehiclesToFile();
    saveUsersToFile();  saveWaitlistsToFile();
    processRouteWaitlist(routeId);
}

void AppController::logPetrol(const PetrolLog& log) {
    petrolLogs.push_back(log);
    savePetrolLogsToFile();
}

// ═══════════════════════════════════════════════════════════════
// TRIP & FUEL
// ═══════════════════════════════════════════════════════════════

bool AppController::dispatchTrip(const string& vehicleId, TripDirection direction) {
    auto vIt = find_if(vehicles.begin(), vehicles.end(),
        [&](const Vehicle& v) { return v.getVehicleId() == vehicleId; });
    if (vIt == vehicles.end()) { cout << "[Error] Vehicle not found.\n"; return false; }

    if (getEffectiveTripCount(vehicleId, direction) >= 1) {
        cout << "[Blocked] Vehicle already did "
            << tripDirectionToString(direction) << " trip today.\n";
        return false;
    }
    if (getTodayTotalEffectiveTrips(vehicleId) >= 2) {
        cout << "[Blocked] Daily trip limit reached (1 ARRIVAL + 1 DEPARTURE).\n";
        return false;
    }
    double routeKm = 0.0;
    string routeId;
    if (vIt->isVAN()) {
        routeKm = vIt->getVanDailyMileage();
        if (routeKm <= 0.0) {
            cout << "[Error] VAN daily mileage not set.\n"; return false;
        }
        if (vIt->getFuelEfficiency() <= 0.0) {
            cout << "[Error] VAN fuel efficiency is zero.\n"; return false;
        }
        routeId = "VAN-INTERNAL";
    }
    else {
        routeId = vIt->getAssignedRouteId();
        if (routeId.empty()) {
            cout << "[Error] Vehicle has no assigned route.\n"; return false;
        }
        for (const auto& r : routes)
            if (r.getRouteId() == routeId) { routeKm = r.getApproxKilometer(); break; }
        if (routeKm <= 0.0) {
            cout << "[Error] Route distance not set.\n"; return false;
        }
    }
    double litres = routeKm / vIt->getFuelEfficiency();
    double fuelCost = litres * petrolPricePerLitre;

    TripLog tl;
    tl.tripId = "TRIP-" + to_string(gCounters.tripNext++);
    gCounters.saveToFile();
    tl.vehicleId = vehicleId;
    tl.routeId = routeId;
    tl.date = DateUtil::getCurrentDate();
    tl.direction = direction;
    tl.routeKm = routeKm;
    tl.fuelUsedLiters = litres;
    tl.fuelCostEstimate = fuelCost;
    tripLogs.push_back(tl);
    saveTripLogsToFile();

    string month = DateUtil::getCurrentYearMonth();
    if (monthlyCapitals.find(month) != monthlyCapitals.end()) {
        auto& mc = monthlyCapitals[month];
        if (mc.remaining() < fuelCost)
            cout << "[Finance Alert] Insufficient capital! Rs "
            << fixed << setprecision(2) << mc.remaining()
            << " remaining vs Rs " << fuelCost << " — Overdraft.\n";
        mc.spentOnFuel += fuelCost;
        saveMonthlyCapitalToFile();
        cout << "[Finance] Rs " << fixed << setprecision(2) << fuelCost
            << " deducted. Remaining: Rs " << mc.remaining() << "\n";
    }
    else {
        cout << "[Finance Warning] No capital set for " << month
            << ". Cost Rs " << fixed << setprecision(2) << fuelCost
            << " not deducted.\n";
    }
    cout << "[Trip] " << tripDirectionToString(direction)
        << " logged | Vehicle: " << vehicleId
        << " | " << (vIt->isVAN() ? "Campus" : "Route: " + routeId)
        << " | " << routeKm << " km | Fuel: "
        << fixed << setprecision(2) << litres
        << " L | Cost: Rs " << fuelCost << "\n";
    return true;
}

void AppController::viewDailyTripSummary(const string& vehicleId) const {
    string today = DateUtil::getCurrentDate();
    cout << "\n--- TRIP SUMMARY: " << vehicleId << " (" << today << ") ---\n";
    double totalKm = 0, totalL = 0, totalCost = 0; bool any = false;
    for (const auto& t : tripLogs) {
        if (t.vehicleId == vehicleId && t.date == today) {
            cout << "  " << t.tripId << " | " << tripDirectionToString(t.direction)
                << " | " << t.routeId << " | " << t.routeKm << " km | "
                << fixed << setprecision(2) << t.fuelUsedLiters
                << " L | Rs " << t.fuelCostEstimate << "\n";
            totalKm += t.routeKm;
            totalL += t.fuelUsedLiters;
            totalCost += t.fuelCostEstimate;
            any = true;
        }
    }
    if (!any) { cout << "  No trips today.\n"; return; }
    cout << "  Total Km: " << totalKm << " | Fuel: " << totalL
        << " L | Cost: Rs " << totalCost << "\n";
}

void AppController::viewVehicleFuelCostToday(const string& vehicleId) const {
    string today = DateUtil::getCurrentDate();
    double totalL = 0, totalCost = 0; int trips = 0;
    for (const auto& t : tripLogs)
        if (t.vehicleId == vehicleId && t.date == today) {
            totalL += t.fuelUsedLiters;
            totalCost += t.fuelCostEstimate;
            trips++;
        }
    double eff = 0;
    for (const auto& v : vehicles)
        if (v.getVehicleId() == vehicleId) { eff = v.getFuelEfficiency(); break; }
    cout << "\n--- FUEL COST: " << vehicleId << " (" << today << ") ---\n"
        << "  Trips: " << trips << " | Efficiency: " << eff
        << " km/L | Petrol: Rs " << fixed << setprecision(2)
        << petrolPricePerLitre << "/L\n"
        << "  Total Fuel: " << totalL
        << " L | Total Cost: Rs " << totalCost << "\n";
}

void AppController::viewAllVanDetails() const {
    cout << "\n=========================================\n"
        << "          REGISTERED VAN FLEET           \n"
        << "=========================================\n";
    int cnt = 0;
    for (const auto& v : vehicles) {
        if (!v.isVAN()) continue;
        double estCost = v.getVanEstimatedDailyFuelCost(petrolPricePerLitre);
        cout << "  VAN ID  : " << v.getVehicleId() << "\n"
            << "  Plate   : " << v.getLicensePlate() << "\n"
            << "  Capacity: " << v.getCapacity()
            << " seats (" << v.getOccupiedSeats() << " occupied)\n"
            << "  Route   : "
            << (v.getAssignedRouteId().empty() ? "Unassigned" : v.getAssignedRouteId()) << "\n"
            << "  Driver  : "
            << (v.getCurrentDriverId().empty() ? "Unassigned" : v.getCurrentDriverId()) << "\n"
            << "  Eff.    : " << v.getFuelEfficiency()
            << " km/L | Fuel: " << v.getFuelType() << "\n"
            << "  Purpose : " << (v.getVanPurpose().empty() ? "N/A" : v.getVanPurpose()) << "\n"
            << "  Daily Mileage   : " << v.getVanDailyMileage() << " km\n"
            << "  Est. Daily Fuel : Rs " << fixed << setprecision(2) << estCost << "\n"
            << "-----------------------------------------\n";
        cnt++;
    }
    if (cnt == 0) cout << "  No VANs registered.\n";
    cout << "=========================================\n";
}

// ═══════════════════════════════════════════════════════════════
// FINANCE
// ═══════════════════════════════════════════════════════════════

void AppController::setMonthlyCapital(double amount) {
    if (amount <= 0.0 || amount > 500000.0) {
        cout << "[Error] Capital must be a positive value up to Rs 500,000.\n"; return;
    }
    string month = DateUtil::getCurrentYearMonth();
    if (monthlyCapitals.find(month) != monthlyCapitals.end()) {
        cout << "[Warning] Capital for " << month << " already set to Rs "
            << fixed << setprecision(2)
            << monthlyCapitals[month].totalCapital << ".\n";
        string confirm = getRobustInput("  Override? (y/n): ");
        if (confirm != "y" && confirm != "Y") { cout << "[Cancelled]\n"; return; }
        double spent = monthlyCapitals[month].spentOnFuel;
        monthlyCapitals[month] = { month, amount, spent };
    }
    else {
        monthlyCapitals[month] = { month, amount, 0.0 };
    }
    saveMonthlyCapitalToFile();
    cout << "[Finance] Capital for " << month << " set to Rs "
        << fixed << setprecision(2) << amount << "\n";
}

void AppController::viewMonthlyCapitalStatus() const {
    string month = DateUtil::getCurrentYearMonth();
    const auto it = monthlyCapitals.find(month);
    if (it == monthlyCapitals.end()) {
        cout << "[Finance] No capital set for " << month << ".\n"; return;
    }
    const auto& mc = it->second;
    cout << "\n=========================================\n"
        << "   MONTHLY CAPITAL STATUS (" << month << ")\n"
        << "=========================================\n"
        << "  Allocated : Rs " << fixed << setprecision(2) << mc.totalCapital << "\n"
        << "  Fuel Spent: Rs " << mc.spentOnFuel << "\n"
        << "  Remaining : Rs " << mc.remaining() << "\n"
        << "  Petrol/L  : Rs " << petrolPricePerLitre << "\n"
        << "=========================================\n";
}

void AppController::updatePetrolPrice(double price) {
    if (price < 50.0 || price > 1000.0) {
        cout << "[Error] Petrol price must be Rs 50-1000/L.\n"; return;
    }
    petrolPricePerLitre = price;
    saveMonthlyCapitalToFile();
    cout << "[Finance] Petrol price updated to Rs "
        << fixed << setprecision(2) << price << "/L.\n";
}

// ═══════════════════════════════════════════════════════════════
// REPORTS
// ═══════════════════════════════════════════════════════════════

void AppController::generateCSVReport() const {
    string today = DateUtil::getCurrentDate();
    string month = DateUtil::getCurrentYearMonth();
    string fname = "UTMS_Finance_Report_" + month + ".csv";

    double totalCapital = 0.0, spentFuel = 0.0;
    auto capIt = monthlyCapitals.find(month);
    if (capIt != monthlyCapitals.end()) {
        totalCapital = capIt->second.totalCapital;
        spentFuel = capIt->second.spentOnFuel;
    }
    double totalRevenue = 0.0;
    for (const auto& r : paymentRecords) totalRevenue += r.amountPaid;
    double netBalance = totalCapital - spentFuel;

    ofstream file(fname);
    if (!file.is_open()) {
        cout << "[Report Error] Could not open '" << fname << "' for writing.\n";
        return;
    }

    // Section 1: Monthly Financial Summary
    file << "MONTHLY TRANSPORT FINANCIAL SUMMARY - " << month << "\n";
    file << "Generated," << today << "\n\n";
    file << "Description,Amount (Rs),Notes\n";
    file << CsvUtil::field("Monthly Capital Allocated") << ","
        << CsvUtil::dblStr(totalCapital) << ","
        << CsvUtil::field("Budget set by Finance Manager for " + month) << "\n";
    file << CsvUtil::field("Gross Revenue (Pass Payments)") << ","
        << CsvUtil::dblStr(totalRevenue) << ","
        << CsvUtil::field("Total collected from all student pass payments") << "\n";
    file << CsvUtil::field("Fuel Expenditure (Trip Logs)") << ","
        << CsvUtil::dblStr(spentFuel) << ","
        << CsvUtil::field("Deducted per vehicle trip dispatched this month") << "\n";
    file << CsvUtil::field("Net Remaining Capital") << ","
        << CsvUtil::dblStr(netBalance) << ","
        << CsvUtil::field("Capital Allocated minus Fuel Spent") << "\n";
    file << CsvUtil::field("Petrol Rate (Rs per Litre)") << ","
        << CsvUtil::dblStr(petrolPricePerLitre) << ","
        << CsvUtil::field("Current rate used for fuel calculations") << "\n";
    file << CsvUtil::field("Revenue minus Fuel Cost") << ","
        << CsvUtil::dblStr(totalRevenue - spentFuel) << ","
        << CsvUtil::field("Operating surplus or deficit") << "\n";

    // Section 2: Vehicle Daily Fuel & Mileage Log
    file << "\nVEHICLE FLEET DAILY FUEL & MILEAGE LOG - " << today << "\n";
    file << "Vehicle ID,Type,Route/Usage,Plate,"
        << "Efficiency (km/L),Mileage (km),Trips Today,"
        << "Fuel Used (L),Fuel Cost (Rs)\n";

    for (const auto& v : vehicles) {
        double litres = 0, cost = 0, km = 0; int trips = 0;
        for (const auto& t : tripLogs)
            if (t.vehicleId == v.getVehicleId() && t.date == today) {
                litres += t.fuelUsedLiters;
                cost += t.fuelCostEstimate;
                km += t.routeKm;
                trips++;
            }
        if (v.isVAN() && trips == 0 && v.getVanDailyMileage() > 0
            && !v.getCurrentDriverId().empty()) {
            km = v.getVanDailyMileage();
            litres = (v.getFuelEfficiency() > 0) ? km / v.getFuelEfficiency() : 0;
            cost = litres * petrolPricePerLitre;
        }
        string routeStr = v.isVAN() ? "Campus (internal)"
            : (v.getAssignedRouteId().empty() ? "Unassigned"
                : v.getAssignedRouteId());
        string typeLabel = vehicleTypeToString(v.getType());
        if (v.isVAN()) typeLabel += " (Uni)";

        file << CsvUtil::field(v.getVehicleId()) << ","
            << CsvUtil::field(typeLabel) << ","
            << CsvUtil::field(routeStr) << ","
            << CsvUtil::field(v.getLicensePlate()) << ","
            << CsvUtil::dblStr(v.getFuelEfficiency()) << ","
            << CsvUtil::dblStr(km) << ","
            << trips << ","
            << CsvUtil::dblStr(litres) << ","
            << CsvUtil::dblStr(cost) << "\n";
    }
    if (vehicles.empty()) file << "No vehicles registered.\n";

    file.close();
    cout << "[Report] CSV saved: '" << fname << "'\n"
        << "         Section 1: Monthly Financial Summary\n"
        << "         Section 2: Vehicle Daily Fuel & Mileage Log\n";
}

void AppController::displaySystemStats() {
    sweepExpiredPasses();
    cout << "\n=========================================\n"
        << "          FULL SYSTEM METRICS            \n"
        << "=========================================\n"
        << "  Registered Users  : " << users.size() << "\n"
        << "  Vehicles in Fleet : " << vehicles.size() << "\n"
        << "  Active Routes     : " << routes.size() << "\n";
    int busCount = 0, vanCount = 0;
    for (const auto& v : vehicles) { if (v.isVAN()) vanCount++; else busCount++; }
    cout << "    BUS count : " << busCount << "\n    VAN count : " << vanCount << "\n";
    int activePasses = 0;
    for (const auto& p : passes)
        if (p.getStatus() == PassStatus::ACTIVE) activePasses++;
    cout << "  Active Passes     : " << activePasses << "\n";
    int driverCount = 0, onRoute = 0;
    for (const auto& kv : users)
        if (kv.second->getRole() == "Driver") {
            driverCount++;
            auto d = dynamic_pointer_cast<Driver>(kv.second);
            if (d && d->getStatus() == DriverStatus::ON_ROUTE) onRoute++;
        }
    cout << "  Drivers Enrolled  : " << driverCount
        << "\n  Drivers On Route  : " << onRoute
        << " (Free: " << (driverCount - onRoute) << ")\n";
    double revenueSum = 0;
    for (const auto& r : paymentRecords) revenueSum += r.amountPaid;
    double fuelSum = 0;
    for (const auto& t : tripLogs)   fuelSum += t.fuelCostEstimate;
    for (const auto& l : petrolLogs) fuelSum += l.cost;
    ReportGenerator::generateFinancialReport(revenueSum, fuelSum);
    viewMonthlyCapitalStatus();
}

// ═══════════════════════════════════════════════════════════════
// WAITLIST
// ═══════════════════════════════════════════════════════════════

void AppController::viewRouteWaitlist(const string& routeId) {
    auto it = routeWaitlists.find(routeId);
    if (it == routeWaitlists.end() || it->second.empty()) {
        cout << "[Waitlist] No students waiting for Route " << routeId << ".\n"; return;
    }
    cout << "\n--- WAITLIST: Route " << routeId
        << " (" << it->second.size() << " waiting) ---\n";
    auto tmpQ = it->second; int pos = 1;
    while (!tmpQ.empty()) {
        string sId = tmpQ.front(); tmpQ.pop();
        auto   uIt = users.find(sId);
        string nm = (uIt != users.end()) ? uIt->second->getName() : "Unknown";
        cout << "  [" << pos++ << "] " << sId << " | " << nm << "\n";
    }
}

void AppController::processRouteWaitlist(const string& routeId) {
    auto it = routeWaitlists.find(routeId);
    if (it == routeWaitlists.end() || it->second.empty()) return;
    {
        queue<string> cleaned; auto tmpQ = it->second;
        while (!tmpQ.empty()) {
            string sid = tmpQ.front(); tmpQ.pop();
            auto passIt = find_if(passes.begin(), passes.end(),
                [&](const TransportPass& p) {
                    return p.getStudentId() == sid &&
                        p.getRouteId() == routeId &&
                        p.getStatus() == PassStatus::WAITLISTED;
                });
            if (passIt != passes.end()) cleaned.push(sid);
        }
        it->second = cleaned;
        saveWaitlistsToFile();
    }
    bool promoted = false;
    while (!it->second.empty()) {
        Vehicle* targetVehicle = nullptr;
        for (auto& v : vehicles)
            if (v.getAssignedRouteId() == routeId && v.getRemainingSeats() > 0) {
                targetVehicle = &v; break;
            }
        if (!targetVehicle) break;
        string studentId = it->second.front(); it->second.pop();
        auto passIt = find_if(passes.begin(), passes.end(),
            [&](const TransportPass& p) {
                return p.getStudentId() == studentId &&
                    p.getRouteId() == routeId &&
                    p.getStatus() == PassStatus::WAITLISTED;
            });
        if (passIt == passes.end()) continue;
        targetVehicle->incrementOccupiedSeats();
        passIt->activate(DateUtil::getCurrentDate(),
            DateUtil::calculateExpiryDate(180));
        string sSem = "", sDept = "", vanInfo = "";
        auto uIt = users.find(studentId);
        if (uIt != users.end() && uIt->second->getRole() == "Student") {
            auto sp = dynamic_pointer_cast<Student>(uIt->second);
            if (sp) {
                sp->setPassStatus(true);
                sSem = sp->getSemester(); sDept = sp->getDepartment();
            }
        }
        if (targetVehicle->isVAN()) {
            ostringstream vi;
            vi << "VAN " << targetVehicle->getVehicleId()
                << " | Daily Mileage: " << targetVehicle->getVanDailyMileage() << " km";
            vanInfo = vi.str();
        }
        cout << "[Waitlist] Promoted " << studentId
            << " -> Route " << routeId
            << " (Vehicle: " << targetVehicle->getVehicleId() << ")\n";
        PDFGenerator::generatePassPDF(passIt->getPassId(), passIt->getStudentId(),
            passIt->getRouteId(), passIt->getExpiryDate(), sSem, sDept, vanInfo);
        promoted = true;
    }
    if (promoted) {
        saveUsersToFile(); saveVehiclesToFile();
        savePassesToFile(); saveWaitlistsToFile();
    }
}

// ═══════════════════════════════════════════════════════════════
// QUERY HELPERS
// ═══════════════════════════════════════════════════════════════

int AppController::getRemainingSeatsForRoute(const string& routeId) const {
    int total = 0; bool found = false;
    for (const auto& v : vehicles)
        if (v.getAssignedRouteId() == routeId) {
            total += v.getRemainingSeats(); found = true;
        }
    return found ? total : 0;
}

bool AppController::isStopOnRoute(const string& routeId,
    const string& stopName) const {
    for (const auto& r : routes)
        if (r.getRouteId() == routeId)
            for (const auto& s : r.getStops())
                if (s.stopName == stopName) return true;
    return false;
}

int AppController::getTodayTripCount(const string& vehicleId,
    TripDirection direction) const {
    string today = DateUtil::getCurrentDate(); int count = 0;
    for (const auto& t : tripLogs)
        if (t.vehicleId == vehicleId &&
            t.date == today &&
            t.direction == direction) count++;
    return count;
}

int AppController::getEffectiveTripCount(const string& vehicleId,
    TripDirection direction) const {
    return getTodayTripCount(vehicleId, direction);
}

int AppController::getTodayTotalTrips(const string& vehicleId) const {
    string today = DateUtil::getCurrentDate(); int count = 0;
    for (const auto& t : tripLogs)
        if (t.vehicleId == vehicleId && t.date == today) count++;
    return count;
}

int AppController::getTodayTotalEffectiveTrips(const string& vehicleId) const {
    return getTodayTotalTrips(vehicleId);
}

void AppController::viewDriverAssignments() const {
    cout << "\n--- REGISTERED DRIVERS ---\n"; int count = 0;
    for (const auto& kv : users)
        if (kv.second->getRole() == "Driver") {
            auto d = dynamic_pointer_cast<Driver>(kv.second);
            if (d) {
                cout << " - ID: " << d->getSystemId()
                    << " | " << d->getName()
                    << " | Lic: " << d->getLicenseNumber()
                    << " | " << driverStatusToString(d->getStatus())
                    << " | Vehicle: "
                    << (d->getAssignedVehicle().empty() ? "None"
                        : d->getAssignedVehicle())
                    << "\n";
                count++;
            }
        }
    if (count == 0) cout << "No drivers registered.\n";
}