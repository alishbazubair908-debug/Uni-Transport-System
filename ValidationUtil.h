#ifndef VALIDATIONUTILS_H
#define VALIDATIONUTILS_H

#include <string>
#include <cctype>
using namespace std;

namespace ValidationUtil 
{

    inline bool isValidEmail(const string& email)
    {
        if (email.empty()) return false;

        int atIndex = -1;
        int dotIndex = -1;

        for (int i = 0; i < email.length(); i++) {
            if (email[i] == ' ') return false; // Email mein space nahi ho sakti
            if (email[i] == '@') {
                if (atIndex != -1) return false; // Ek se zyada @ nahi ho sakte
                atIndex = i;
            }
        }

        // Aakhri loop se dot (.) dhoondte hain jo @ ke BAAD aana chahiye
        if (atIndex > 0) { // @ shuru mein nahi hona chahiye
            for (int i = atIndex + 1; i < email.length(); i++) {
                if (email[i] == '.') {
                    dotIndex = i; // @ ke baad dot mil gaya
                }
            }
        }

        // Check karo ke @ aur . dono mile, aur . ke baad kam se kam 2 characters hoon (jaise .com, .pk)
        if (atIndex != -1 && dotIndex != -1 && (dotIndex > atIndex + 1) && (email.length() - 1 - dotIndex >= 2)) {
            return true;
        }
        return false;
    }


    inline bool isValidVehiclePlate(const string& plate)
    {
        // 1. Vehicle plate ki total length hamesha exact 8 honi chahiye
        if (plate.length() != 8) return false;

        // 2. 3rd index par dash (-) hona chahiye (0, 1, 2 ke baad)
        if (plate[3] != '-') return false;

        // 3. Shuru ke 3 characters Alphabets (A-Z) hone chahiye
        for (int i = 0; i < 3; i++) {
            if (!isalpha(static_cast<unsigned char>(plate[i]))) {
                return false;
            }
        }

        // 4. Aakhri 4 characters Digits (0-9) hone chahiye
        for (int i = 4; i < 8; i++) {
            if (!isdigit(static_cast<unsigned char>(plate[i]))) {
                return false;
            }
        }

        return true; // Agar saari conditions sahi hain
    }


    inline bool isValidPassword(const string& pw) 
    {
        return pw.length() >= 8;
    }

    inline bool isValidName(const string& name)
    {
        if (name.empty() || name.length()<3) return false;
        bool hasLetter = false;
        for (char c : name) {
            if (isalpha(static_cast<unsigned char>(c))) { hasLetter = true; continue; }
            if (c == ' ' || c == '.' || c == '-')       continue;
            return false;
        }
        return hasLetter;
    }

    inline bool isValidCNIC(const string& cnic)
    {
        // 1. CNIC ki total length hamesha 15 honi chahiye (13 digits + 2 dashes)
        if (cnic.length() != 15) return false;

        // 2. 5th aur 13th index par dash (-) hona chahiye
        if (cnic[5] != '-' || cnic[13] != '-') return false;

        // 3. Baaki saari jagahon par sirf numbers (digits) hone chahiye
        for (int i = 0; i < 15; i++) {
            if (i == 5 || i == 13) continue; // dashes ko skip karo
            if (!isdigit(static_cast<unsigned char>(cnic[i]))) {
                return false; // Agar koi character number nahi hai to reject
            }
        }
        return true;
    }

    inline bool isValidPhone(const string& phone)
    {
        // Format 1: 03XX-XXXXXXX (Length hamesha 12)
        if (phone.length() == 12) {
            if (phone[0] != '0' || phone[1] != '3') return false;
            if (phone[4] != '-') return false;

            for (int i = 0; i < 12; i++) {
                if (i == 4) continue; // dash skip karo
                if (!isdigit(static_cast<unsigned char>(phone[i]))) return false;
            }
            return true;
        }

        // Format 2: +923XXXXXXXXX (Length hamesha 13)
        if (phone.length() == 13) {
            if (phone[0] != '+' || phone[1] != '9' || phone[2] != '2' || phone[3] != '3') return false;

            for (int i = 1; i < 13; i++) { // '+' ke baad saare digits check karo
                if (!isdigit(static_cast<unsigned char>(phone[i]))) return false;
            }
            return true;
        }

        return false; // Agar dono formats mien se kisi par poora na utre
    }


    inline bool isValidAge(int age) { return age >= 16 && age <= 25; }
    inline bool isValidAgeEmployee(int age) { return age >= 25 && age <= 80; }
    inline bool isValidSalary(double salary) { return salary >= 15000.0 && salary <= 500000.0; }

    inline bool isValidLicense(const string& lic)
    {
        if (lic.size() < 6) return false;
        for (char c : lic)
            if (!isalnum(static_cast<unsigned char>(c)) && c != '-') return false;
        return true;
    }

    inline bool isValidRollNumber(const string& roll) { return roll.size() >= 5; }

    inline bool isValidSemester(const string& sem)
    {
        try { int s = stoi(sem); return s >= 1 && s <= 8; }
        catch (...) { return false; }
    }

    inline bool isValidDepartment(const string& dept) { return isValidName(dept); }
    inline bool isValidAddress(const string& addr) { return addr.size() >= 5; }

    inline bool isValidHireDate(const string& date)
    {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;

        for (int i = 0; i < 10; i++) {
            if (i == 4 || i == 7) continue; // dashes ko skip karo
            if (!isdigit(static_cast<unsigned char>(date[i]))) return false;
        }
        return true;
    }

    inline bool isValidDesignation(const string& d)
    {
        return !d.empty() && d.size() <= 60;
    }

    inline bool isValidVanDailyKm(double km) { return km >= 1.0 && km <= 6.0; }
    inline bool isValidVanPurpose(const string& p) { return !p.empty() && p.size() >= 5 && p.size() <= 120; }
    
    // Stop ID must be at least 2 chars and contain both letters and digits
    inline bool isValidStopId(const string& id) {
        if (id.length() < 2) return false;
        bool hasLetter = false, hasDigit = false;
        for (char c : id) {
            if (isalpha(static_cast<unsigned char>(c))) hasLetter = true;
            else if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
            else return false;   // rejects spaces, hyphens, special chars
        }
        return hasLetter && hasDigit;
    }

    inline bool isValidRouteId(const string& id)
    {
        if (id.empty() || id.size() < 2) return false;
        for (char c : id)
            if (!isalnum(static_cast<unsigned char>(c))) return false;
        return true;
    }

    //inline bool isValidCoordinates(const string& coord)
    //{
    //    if (coord.size() < 3) return false;

    //    int commaCount = 0;
    //    for (char c : coord) {
    //        if (c == ',') {
    //            commaCount++;
    //            continue;
    //        }
    //        // Sirf numbers, dot, ya minus sign ki ijazat hai
    //        if (!isdigit(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
    //            return false;
    //        }
    //    }

    //    // Exact ek hi comma hona chahiye poori string mein
    //    return (commaCount == 1);
    //}
}

#endif