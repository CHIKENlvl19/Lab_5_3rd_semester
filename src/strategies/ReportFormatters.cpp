#include "../../include/strategies/ReportFormatters.h"
#include <sstream>

// CSVFormatter
std::string CSVFormatter::format(const std::map<std::string, int>& results) {
    std::stringstream ss;
    ss << "Student Name,Final Grade\n";
    for (const auto& pair : results) {
        ss << pair.first << "," << pair.second << "\n";
    }
    return ss. str();
}

// JSONFormatter
std::string JSONFormatter::format(const std::map<std:: string, int>& results) {
    std::stringstream ss;
    ss << "{\n  \"results\": [\n";
    bool first = true;
    for (const auto& pair : results) {
        if (!first) ss << ",\n";
        ss << "    {\n      \"student\": \"" << pair.first << "\",\n"
           << "      \"grade\": " << pair.second << "\n    }";
        first = false;
    }
    ss << "\n  ]\n}";
    return ss.str();
}

// PlainTextFormatter
std::string PlainTextFormatter::format(const std::map<std::string, int>& results) {
    std::stringstream ss;
    ss << "Subject Results\n";
    for (const auto& pair : results) {
        ss << pair.first << ": " << pair.second << "\n";
    }
    return ss.str();
}