#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../domain/Grade.h"
#include "../domain/Student.h"
#include "../domain/Subject.h"

class Grade;
class Student;
class Subject;
class Teacher;
class SubmissionRecord;

// Strategy Pattern - интерфейс для стратегий расчёта оценок
class IGradeCalculationStrategy {
public:
    virtual ~IGradeCalculationStrategy() = default;
    virtual int calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) = 0;
};

class GradeService {
private:
    std:: shared_ptr<IGradeCalculationStrategy> calculationStrategy;

public:
    GradeService();

    void setCalculationStrategy(std::shared_ptr<IGradeCalculationStrategy> strategy);

    std::shared_ptr<Grade> createGrade(std::shared_ptr<Student> student,
                                       std::shared_ptr<Subject> subject,
                                       int score, GradeType type,
                                       const std::string& comment = "");

    void issueGrade(std::shared_ptr<Grade> grade, std::shared_ptr<Student> student);

    int calculateFinalGrade(std::shared_ptr<Student> student,
                           std::shared_ptr<Subject> subject);

    std::vector<std:: shared_ptr<Grade>> getStudentGradesBySubject(
        std::shared_ptr<Student> student,
        std::shared_ptr<Subject> subject);
};