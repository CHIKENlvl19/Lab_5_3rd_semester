#pragma once

#include "../services/ReportService.h"
#include <string>
#include <map>

// Concrete Formatter 1: CSV
class CSVFormatter : public IReportFormatter {
public:
    std::string format(const std::map<std::string, int>& results) override;
};

// Concrete Formatter 2: JSON
class JSONFormatter : public IReportFormatter {
public:
    std::string format(const std::map<std:: string, int>& results) override;
};

// Concrete Formatter 3: Plain Text
class PlainTextFormatter :  public IReportFormatter {
public:
    std::string format(const std::map<std::string, int>& results) override;
};