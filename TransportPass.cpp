#include "TransportPass.h"

using namespace std;

// Constructor 1 Implementation
TransportPass::TransportPass(string pId, string sId, string rId, string stopName)
    : passId(move(pId)),
    studentId(move(sId)),
    routeId(move(rId)),
    chosenStopName(move(stopName)),
    status(PassStatus::PENDING_PAYMENT) {
}

// Constructor 2 Implementation
TransportPass::TransportPass(string pId, string sId, string rId, string stopName,
    string iDate, string eDate, PassStatus stat)
    : passId(move(pId)),
    studentId(move(sId)),
    routeId(move(rId)),
    chosenStopName(move(stopName)),
    issueDate(move(iDate)),
    expiryDate(move(eDate)),
    status(stat) {
}

// Activation logic updates status, issue date, and expiry timeline
void TransportPass::activate(const string& iDate, const string& eDate) {
    status = PassStatus::ACTIVE;
    issueDate = iDate;
    expiryDate = eDate;
}