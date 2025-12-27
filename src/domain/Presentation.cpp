#include "domain/Presentation.h"
#include "domain/Student.h"
#include "domain/Subject.h"
#include <algorithm>
#include <ctime>

Presentation::Presentation(const std::string& id, const std::string& title,
                          std::shared_ptr<Subject> subject, int maxCapacity,
                          time_t scheduledDate)
    : id(id), title(title), subject(subject), maxCapacity(maxCapacity),
      scheduledDate(scheduledDate) {}

std::string Presentation::getId() const {
    return id;
}

std::string Presentation::getTitle() const {
    return title;
}

std::shared_ptr<Subject> Presentation::getSubject() const {
    return subject;
}

int Presentation:: getCapacity() const {
    return maxCapacity;
}

int Presentation::getRegisteredCount() const {
    return static_cast<int>(registeredStudents.size());
}

bool Presentation::isFull() const {
    return static_cast<int>(registeredStudents.size()) >= maxCapacity;
}

time_t Presentation::getScheduledDate() const {
    return scheduledDate;
}

bool Presentation::registerStudent(std::shared_ptr<Student> student) {
    if (isFull()) {
        return false;
    }
    if (isStudentRegistered(student->getId())) {
        return false;
    }
    registeredStudents.push_back(student);
    student->registerForPresentation(std::make_shared<Presentation>(*this));
    return true;
}

bool Presentation::unregisterStudent(const std::string& studentId) {
    auto it = std::find_if(registeredStudents. begin(), registeredStudents.end(),
                          [&studentId](const std::shared_ptr<Student>& s) {
                              return s->getId() == studentId;
                          });
    if (it != registeredStudents.end()) {
        registeredStudents.erase(it);
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Student>> Presentation::getRegisteredStudents() const {
    return registeredStudents;
}

bool Presentation::isStudentRegistered(const std::string& studentId) const {
    return std::any_of(registeredStudents. begin(), registeredStudents.end(),
                      [&studentId](const std::shared_ptr<Student>& s) {
                          return s->getId() == studentId;
                      });
}

std::string Presentation::getInfo() const {
    return "Presentation: " + title + " (ID: " + id + ", Capacity: " +
           std::to_string(getRegisteredCount()) + "/" + std::to_string(maxCapacity) + ")";
}