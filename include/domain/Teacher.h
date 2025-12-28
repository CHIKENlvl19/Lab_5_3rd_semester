#pragma once

#include "User.h"
#include <vector>
#include <memory>

class Student;
class Subject;
class Presentation;

class Teacher : public User {
private:
    std::vector<std::shared_ptr<Subject>> subjects;
    std::vector<std::weak_ptr<Student>> registeredStudents;
    std::vector<std::weak_ptr<Teacher>> colleagues;

public:
    Teacher(const std::string& id, const std::string& name, 
            const std::string& email);

    void addSubject(std:: shared_ptr<Subject> subject);
    void removeSubject(const std::string& subjectId);
    std::vector<std:: shared_ptr<Subject>> getSubjects() const;

    void registerStudent(std::shared_ptr<Student> student);
    void removeStudent(const std::string& studentId);
    std::vector<std::shared_ptr<Student>> getRegisteredStudents() const;

    void addColleague(std::shared_ptr<Teacher> teacher);
    std::vector<std::shared_ptr<Teacher>> getColleagues() const;

    std::string getInfo() const override;
};