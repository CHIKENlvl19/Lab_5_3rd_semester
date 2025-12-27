#pragma once

#include <memory>
#include <string>
#include "../domain/Teacher.h"
#include "../domain/Student.h"

class User;
class Teacher;
class Student;

// Factory Pattern
class UserFactory {
public: 
    static std::shared_ptr<Teacher> createTeacher(const std:: string& id,
                                                   const std::string& name,
                                                   const std:: string& email);

    static std::shared_ptr<Student> createStudent(const std::string& id,
                                                   const std::string& name,
                                                   const std::string& email);
};