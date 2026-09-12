#include "IdCounters.h"
using namespace std;

// The ONE global definition of gCounters.
// All other files use extern to reference this.
IdCounters gCounters;

void IdCounters::saveToFile() const {
    ofstream f("id_counters.txt");
    if (!f) return;
    f << adminNext << "\n"
        << driverNext << "\n"
        << studentNext << "\n"
        << tripNext << "\n"
        << billNext << "\n"
        << payNext << "\n";
}

void IdCounters::loadFromFile() {
    ifstream f("id_counters.txt");
    if (!f) return;
    f >> adminNext >> driverNext >> studentNext
        >> tripNext >> billNext >> payNext;
}