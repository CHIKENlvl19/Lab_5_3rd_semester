#include "../../include/services/TeacherService.h"
#include "../../include/domain/Teacher.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"
#include "../../include/domain/Presentation.h"
#include <stdexcept>

std::shared_ptr<Subject> TeacherService::createSubject(
    const std::string& id,
    const std::string& name,
    const std::string& description,
    std::shared_ptr<Teacher> teacher) {
    
    if (id.empty()) {
        throw std::invalid_argument("Subject ID cannot be empty");
    }
    if (name.empty()) {
        throw std::invalid_argument("Subject name cannot be empty");
    }
    if (!teacher) {
        throw std::invalid_argument("Teacher cannot be null");
    }
    
    auto subject = std::make_shared<Subject>(id, name, description, teacher);
    teacher->addSubject(subject);
    
    return subject;
}

std:: shared_ptr<Presentation> TeacherService::createPresentation(
    const std:: string& id,
    const std::string& title,
    std::shared_ptr<Subject> subject,
    int maxCapacity,
    time_t scheduledDate) {
    return std::make_shared<Presentation>(id, title, subject, maxCapacity, scheduledDate);
}

void TeacherService::registerStudent(std::shared_ptr<Teacher> teacher,
                                     std::shared_ptr<Student> student) {
    if (!teacher) {
        throw std::invalid_argument("Teacher cannot be null");
    }
    if (!student) {
        throw std::invalid_argument("Student cannot be null");
    }

    teacher->registerStudent(student);
}

void TeacherService::unregisterStudent(std::shared_ptr<Teacher> teacher,
                                      const std::string& studentId) {
    teacher->removeStudent(studentId);
}

void TeacherService::addColleague(std::shared_ptr<Teacher> teacher,
                                 std::shared_ptr<Teacher> colleague) {
    teacher->addColleague(colleague);
    colleague->addColleague(teacher);
}