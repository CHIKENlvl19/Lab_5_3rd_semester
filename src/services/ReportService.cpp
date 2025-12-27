#include "services/ReportService.h"
#include "domain/Student.h"
#include "domain/Subject.h"
#include "domain/Grade.h"
#include <algorithm>

ReportService::ReportService(std::shared_ptr<IReportFormatter> formatter)
    : formatter(formatter) {}

void ReportService::setFormatter(std::shared_ptr<IReportFormatter> formatter) {
    this->formatter = formatter;
}

std::map<std::string, int> ReportService::generateSubjectReport(
    std::shared_ptr<Subject> /*subject*/) {
    std::map<std::string, int> results;
    // В реальной реализации это должно получать данные из репозитория
    return results;
}

std::string ReportService::exportSubjectResults(std::shared_ptr<Subject> subject) {
    auto results = generateSubjectReport(subject);
    return formatter->format(results);
}

std::vector<std::pair<std::string, int>> ReportService::rankStudentsByGrades(
    std::shared_ptr<Subject> /*subject*/) {
    std::vector<std::pair<std::string, int>> ranking;
    // В реальной реализации это должно получать данные из репозитория
    return ranking;
}