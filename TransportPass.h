#ifndef TRANSPORT_PASS_H
#define TRANSPORT_PASS_H

#include <string>
#include <utility>
#include"enums.h"

// Assuming PassStatus enum is declared somewhere.
// If it's in another file, replace this with #include "PassStatus.h"

class TransportPass
{
private:
    std::string passId;
    std::string studentId;
    std::string routeId;
    std::string chosenStopName;
    std::string issueDate;
    std::string expiryDate;
    PassStatus status;

public:
    // Constructor for a new pass (Defaults to PENDING_PAYMENT)
    TransportPass(std::string pId, std::string sId, std::string rId, std::string stopName);

    // Constructor for loading an existing pass record (e.g., from a database or CSV file)
    TransportPass(std::string pId, std::string sId, std::string rId, std::string stopName,
        std::string iDate, std::string eDate, PassStatus stat);

    // Getters (Left inline in the header for fast evaluation)
    std::string getPassId() const { return passId; }
    std::string getStudentId() const { return studentId; }
    std::string getRouteId() const { return routeId; }
    std::string getChosenStop() const { return chosenStopName; }
    PassStatus getStatus() const { return status; }
    std::string getExpiryDate() const { return expiryDate; }
    std::string getIssueDate() const { return issueDate; }

    // Setters & State Changers (Moved to .cpp)
    void setStatus(PassStatus s) { status = s; }
    void activate(const std::string& iDate, const std::string& eDate);
};

#endif // TRANSPORT_PASS_H