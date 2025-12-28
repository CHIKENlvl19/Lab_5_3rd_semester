#include "../../include/domain/Teacher.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"

Teacher::Teacher(const std::string& id, const std::string& name,
                 const std::string& email)
    : User(id, name, email, UserRole::TEACHER) {}

void Teacher::addSubject(std:: shared_ptr<Subject> subject) {
    subjects. push_back(subject);
}

void Teacher::removeSubject(const std::string& subjectId) {
    subjects.erase(
        std::remove_if(subjects.begin(), subjects.end(),
                      [&subjectId](const std::shared_ptr<Subject>& s) {
                          return s->getId() == subjectId;
                      }),
        subjects.end());
}

std::vector<std::shared_ptr<Subject>> Teacher::getSubjects() const {
    return subjects;
}

void Teacher::registerStudent(std::shared_ptr<Student> student) {
    registeredStudents.push_back(student);
}

void Teacher::removeStudent(const std::string& studentId) {
    registeredStudents.erase(
        std::remove_if(registeredStudents.begin(), registeredStudents.end(),
                      [&studentId](const std::weak_ptr<Student>& weak) {
                          auto s = weak.lock();
                          return !s || s->getId() == studentId;
                      }),
        registeredStudents.end());
}

std::vector<std::shared_ptr<Student>> Teacher::getRegisteredStudents() const {
    std::vector<std::shared_ptr<Student>> result;
    for (const auto& weak : registeredStudents) {
        if (auto s = weak.lock()) {
            result.push_back(s);
        }
    }
    return result;
}

void Teacher::addColleague(std::shared_ptr<Teacher> teacher) {
    colleagues.push_back(teacher);
}

std::vector<std::shared_ptr<Teacher>> Teacher::getColleagues() const {
    std::vector<std::shared_ptr<Teacher>> result;
    for (const auto& weak : colleagues) {
        if (auto t = weak.lock()) {
            result.push_back(t);
        }
    }
    return result;
}

std::string Teacher::getInfo() const {
    return "Teacher: " + name + " (ID: " + id + ", Email: " + email + ")";
}