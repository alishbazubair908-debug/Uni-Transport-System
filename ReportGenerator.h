#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <iostream>
#include <iomanip>
using namespace std;

namespace ReportGenerator {

    inline void generateFinancialReport(double totalRevenue, double totalFuelCosts) {
        cout << "\n=========================================\n"
            << "         FINANCIAL SUMMARY REPORT        \n"
            << "=========================================\n"
            << "  Gross Revenue Earned : Rs "
            << fixed << setprecision(2) << totalRevenue << "\n"
            << "  Total Fuel Expenses  : Rs " << totalFuelCosts << "\n"
            << "  Net Operating Margin : Rs "
            << (totalRevenue - totalFuelCosts) << "\n"
            << "=========================================\n";
    }

}

#endif