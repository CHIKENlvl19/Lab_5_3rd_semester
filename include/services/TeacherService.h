#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../domain/Teacher.h"
#include "../domain/Student.h"
#include "../domain/Subject.h"
#include "../domain/Presentation.h"

class Teacher;
class Student;
class Subject;
class Presentation;

class TeacherService {
public:
    // Factory Pattern - создание сущностей
    std::shared_ptr<Subject> createSubject(const std:: string& id,
                                           const std::string& name,
                                           const std::string& description,
                                           std:: shared_ptr<Teacher> teacher);

    std::shared_ptr<Presentation> createPresentation(
        const std::string& id,
        const std::string& title,
        std::shared_ptr<Subject> subject,
        int maxCapacity,
        time_t scheduledDate);

    void registerStudent(std::shared_ptr<Teacher> teacher,
                        std::shared_ptr<Student> student);

    void unregisterStudent(std::shared_ptr<Teacher> teacher,
                          const std::string& studentId);

    void addColleague(std::shared_ptr<Teacher> teacher,
                     std::shared_ptr<Teacher> colleague);
};