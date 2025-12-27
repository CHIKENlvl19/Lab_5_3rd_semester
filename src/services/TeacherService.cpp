#include "../../include/services/TeacherService.h"
#include "../../include/domain/Teacher.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"
#include "../../include/domain/Presentation.h"

std::shared_ptr<Subject> TeacherService::createSubject(
    const std::string& id,
    const std::string& name,
    const std::string& description,
    std::shared_ptr<Teacher> teacher) {
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