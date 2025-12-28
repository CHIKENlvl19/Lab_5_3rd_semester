#include "services/ReportService.h"
#include "repositories/DataRepository.h"
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
    std::shared_ptr<Subject> subject) {
    std::map<std::string, int> results;
    auto repo = DataRepository::getInstance();
    auto allGrades = repo->getGradesBySubject(subject->getId());
    
    // Группировать оценки по студентам
    std::map<std::string, std::vector<std::shared_ptr<Grade>>> studentGrades;
    for (const auto& grade : allGrades) {
        studentGrades[grade->getStudent()->getName()].push_back(grade);
    }
    
    // Рассчитать средний балл для каждого студента
    for (const auto& pair : studentGrades) {
        int sum = 0;
        for (const auto& grade : pair.second) {
            sum += grade->getScore();
        }
        results[pair.first] = sum / pair.second.size();
    }
    
    return results;
}

std::string ReportService::exportSubjectResults(std::shared_ptr<Subject> subject) {
    auto results = generateSubjectReport(subject);
    return formatter->format(results);
}

std::vector<std::pair<std::string, int>> ReportService::rankStudentsByGrades(
    std::shared_ptr<Subject> subject) {
    auto results = generateSubjectReport(subject);
    std::vector<std::pair<std::string, int>> ranking(results.begin(), results.end());
    
    std::sort(ranking.begin(), ranking.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    return ranking;
}