#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>

class Student;
class Subject;

class Presentation : public std::enable_shared_from_this<Presentation> {
private:
    std::string id;
    std::string title;
    std::shared_ptr<Subject> subject;
    std::vector<std::weak_ptr<Student>> registeredStudents;
    int maxCapacity;
    time_t scheduledDate;

public:
    Presentation(const std::string& id, const std::string& title,
                 std::shared_ptr<Subject> subject, int maxCapacity,
                 time_t scheduledDate);

    std::string getId() const;
    std::string getTitle() const;
    std::shared_ptr<Subject> getSubject() const;
    int getCapacity() const;
    int getRegisteredCount() const;
    bool isFull() const;
    time_t getScheduledDate() const;

    bool registerStudent(std::shared_ptr<Student> student);
    bool unregisterStudent(const std:: string& studentId);
    std::vector<std::shared_ptr<Student>> getRegisteredStudents() const;
    bool isStudentRegistered(const std::string& studentId) const;

    std::string getInfo() const;
};