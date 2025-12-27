#include "../../include/services/GradeService.h"
#include "../../include/domain/Grade.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"
#include "../../include/strategies/GradeCalculationStrategy.h"
#include <algorithm>

GradeService::GradeService()
    : calculationStrategy(std::make_shared<WeightedAverageStrategy>()) {}

void GradeService::setCalculationStrategy(std::shared_ptr<IGradeCalculationStrategy> strategy) {
    calculationStrategy = strategy;
}

std::shared_ptr<Grade> GradeService::createGrade(std::shared_ptr<Student> student,
                                                  std::shared_ptr<Subject> subject,
                                                  int score, GradeType type,
                                                  const std:: string& comment) {
    std::string gradeId = "GRADE_" + student->getId() + "_" + subject->getId() +
                         "_" + std:: to_string(std::time(nullptr));
    return std::make_shared<Grade>(gradeId, student, subject, score, type, comment);
}

void GradeService::issueGrade(std::shared_ptr<Grade> grade, std::shared_ptr<Student> student) {
    student->addGrade(grade);
}

int GradeService::calculateFinalGrade(std::shared_ptr<Student> student,
                                     std::shared_ptr<Subject> subject) {
    auto gradesBySubject = student->getGradesBySubject(subject->getId());
    if (gradesBySubject.empty()) {
        return 0;
    }
    return calculationStrategy->calculateFinalGrade(gradesBySubject);
}

std::vector<std:: shared_ptr<Grade>> GradeService::getStudentGradesBySubject(
    std:: shared_ptr<Student> student,
    std::shared_ptr<Subject> subject) {
    return student->getGradesBySubject(subject->getId());
}