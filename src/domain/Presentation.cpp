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

bool Presentation::isFull() const {
    return static_cast<int>(registeredStudents.size()) >= maxCapacity;
}

time_t Presentation::getScheduledDate() const {
    return scheduledDate;
}

// Обновить методы:
bool Presentation::registerStudent(std::shared_ptr<Student> student) {
    // Проверить, нет ли уже этого студента
    for (auto& weak : registeredStudents) {
        if (auto s = weak.lock()) {
            if (s->getId() == student->getId()) return false;
        }
    }
    if (isFull()) return false;
    registeredStudents.push_back(student); // weak_ptr автоматически
    student->registerForPresentation(shared_from_this()); 
    return true;
}

bool Presentation::unregisterStudent(const std::string& studentId) {
    auto it = std::remove_if(registeredStudents.begin(), registeredStudents.end(),
        [&studentId](std::weak_ptr<Student>& weak) {
            auto s = weak.lock();
            return !s || s->getId() == studentId;
        });
    if (it == registeredStudents.end()) return false;
    registeredStudents.erase(it, registeredStudents.end());
    return true;
}

int Presentation::getRegisteredCount() const {
    // Фильтровать expired weak_ptr
    int count = 0;
    for (const auto& weak : registeredStudents) {
        if (!weak.expired()) count++;
    }
    return count;
}

bool Presentation::isStudentRegistered(const std::string& studentId) const {
    return std::any_of(registeredStudents.begin(), registeredStudents.end(),
                      [&studentId](const std::weak_ptr<Student>& weak) {
                          auto s = weak.lock();
                          return s && s->getId() == studentId;
                      });
}

std::string Presentation::getInfo() const {
    return "Presentation: " + title + " (ID: " + id + ", Capacity: " +
           std::to_string(getRegisteredCount()) + "/" + std::to_string(maxCapacity) + ")";
}