#ifndef CSVUTILS_H
#define CSVUTILS_H

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// CsvUtil — helpers for building clean CSV output.
// Both functions are static — no object needed, call directly:
//   CsvUtil::field("hello, world")
//   CsvUtil::dblStr(3.14159)

namespace CsvUtil {

    // Wraps a field in quotes if it contains a comma, quote, or newline.
    // This prevents CSV corruption when field values contain special chars.
    static string field(const string& s) {
        bool needsQuote = false;
        for (char c : s) {
            if (c == ',' || c == '"' || c == '\n' || c == '\r') {
                needsQuote = true;
                break;
            }
        }
        if (!needsQuote) return s;

        string out = "\"";
        for (char c : s) {
            if (c == '"') out += "\"\"";  // escape quote by doubling it
            else          out += c;
        }
        out += '"';
        return out;
    }

    // Converts double to string with given decimal precision.
    static string dblStr(double v, int prec = 2) {
        ostringstream o;
        o << fixed << setprecision(prec) << v;
        return o.str();
    }

}

#endif