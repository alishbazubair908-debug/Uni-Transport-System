#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;

namespace DateUtil 
{

    // Safe wrapper around localtime — returns empty tm if it fails
    inline tm safe_localtime(const time_t& timer)
    {
        tm* tmp = localtime(&timer);
        return tmp ? *tmp : tm{};
    }

    // Returns today's date as "YYYY-MM-DD"
    inline string getCurrentDate() {
        auto now = chrono::system_clock::now();
        auto t = chrono::system_clock::to_time_t(now);
        tm   lt = safe_localtime(t);
        stringstream ss;
        ss << put_time(&lt, "%Y-%m-%d");
        return ss.str();
    }

    // Returns current year and month as "YYYY-MM"
    inline string getCurrentYearMonth() {
        auto now = chrono::system_clock::now();
        auto t = chrono::system_clock::to_time_t(now);
        tm   lt = safe_localtime(t);
        stringstream ss;
        ss << put_time(&lt, "%Y-%m");
        return ss.str();
    }

    // Returns expiry date activeDays from today as "YYYY-MM-DD"
    inline string calculateExpiryDate(int activeDays) {
        auto now = chrono::system_clock::now();
        auto expiry = now + chrono::hours(24 * activeDays);
        auto t = chrono::system_clock::to_time_t(expiry);
        tm   lt = safe_localtime(t);
        stringstream ss;
        ss << put_time(&lt, "%Y-%m-%d");
        return ss.str();
    }

    // Converts "HH:MM" string to total minutes. Returns -1 if invalid.
    inline int timeToMinutes(const string& timeStr)
    {
        // 1. Time string ki length hamesha 4 ya 5 honi chahiye (e.g., "9:30" ya "14:45")
        if (timeStr.length() < 4 || timeStr.length() > 5) return -1;

        // 2. Colon (:) dhoondhein aur check karein ke wo sahi jagah par hai ya nahi
        size_t colonPos = timeStr.find(':');
        if (colonPos == string::npos || colonPos < 1 || colonPos > 2) return -1;

        // 3. Loop chala kar check karein ke colon ke ilawa baaki sab sirf digits hoon
        for (size_t i = 0; i < timeStr.length(); i++) {
            if (i == colonPos) continue; // colon skip karo
            if (!isdigit(static_cast<unsigned char>(timeStr[i]))) return -1;
        }

        // 4. Stringstream se hours aur minutes ko alag alag read karein
        stringstream ss(timeStr);
        string hrsStr, minsStr;
        getline(ss, hrsStr, ':');
        getline(ss, minsStr);

        try {
            int hrs = stoi(hrsStr);
            int mins = stoi(minsStr);

            // 5. Logical ranges check karein (Hours 0-23 aur Minutes 0-59)
            if (hrs < 0 || hrs > 23 || mins < 0 || mins > 59) return -1;

            // Total minutes calculate karein
            return (hrs * 60) + mins;
        }
        catch (...) {
            return -1; // Agar conversion mein koi masla aaye
        }
    }

}

#endif