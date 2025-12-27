#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include "../domain/Student.h"
#include "../domain/Subject.h"
#include "../domain/Grade.h"

class Student;
class Subject;
class Grade;

// Strategy Pattern - интерфейс для разных форматов отчётов
class IReportFormatter {
public:
    virtual ~IReportFormatter() = default;
    virtual std::string format(const std::map<std::string, int>& results) = 0;
};

class ReportService {
private: 
    std::shared_ptr<IReportFormatter> formatter;

public:
    ReportService(std::shared_ptr<IReportFormatter> formatter);

    void setFormatter(std::shared_ptr<IReportFormatter> formatter);

    std::map<std::string, int> generateSubjectReport(
        std::shared_ptr<Subject> subject);

    std::string exportSubjectResults(std::shared_ptr<Subject> subject);

    std::vector<std::pair<std::string, int>> rankStudentsByGrades(
        std::shared_ptr<Subject> subject);
};