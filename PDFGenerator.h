#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H

#include <string>
#include <fstream>
using namespace std;

namespace PDFGenerator
{

    // Generates a mock transport pass PDF file.
    // File is saved as "pass_<passId>.pdf" in the current directory.
    inline void generatePassPDF(const string& passId,
        const string& studentId,
        const string& routeId,
        const string& expiry,
        const string& semester = "",
        const string& department = "",
        const string& vanInfo = "") {
        string  filename = "pass_" + passId + ".pdf";
        ofstream file(filename);
        if (!file.is_open()) return;

        file << "%PDF-1.4 (Mock Pass Document)\n"
            << "=========================================\n"
            << "       UNIVERSITY TRANSPORT PASS         \n"
            << "=========================================\n"
            << "  Pass ID    : " << passId << "\n"
            << "  Student ID : " << studentId << "\n";

        if (!semester.empty())   file << "  Semester   : " << semester << "\n";
        if (!department.empty()) file << "  Department : " << department << "\n";

        file << "  Route ID   : " << routeId << "\n"
            << "  Expiry Date: " << expiry << "\n"
            << "  Status     : ACTIVE\n";

        if (!vanInfo.empty()) file << "  VAN Info   : " << vanInfo << "\n";

        file << "=========================================\n";
    }

}

#endif