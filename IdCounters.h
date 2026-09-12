#ifndef IDCOUNTERS_H
#define IDCOUNTERS_H

#include <fstream>
#include <string>
using namespace std;

// IdCounters stores auto-increment counters for every ID type.
// Saved to file so IDs never duplicate across sessions.
struct IdCounters {
    int adminNext = 2001;
    int driverNext = 2001;
    int studentNext = 1001;
    int tripNext = 5001;
    int billNext = 2001;
    int payNext = 3001;

    void saveToFile() const;
    void loadFromFile();
};

// extern = gCounters is defined ONCE in IdCounters.cpp
// Every file that includes this header shares the same instance.
// Without extern, each .cpp would get its own copy — counters would
// never stay in sync and IDs would duplicate.
extern IdCounters gCounters;

#endif