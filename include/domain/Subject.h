#pragma once

#include <string>
#include <vector>
#include <memory>

class Teacher;

class Subject {
private:
    std::string id;
    std::string name;
    std::string description;
    std::shared_ptr<Teacher> teacher;

public:
    Subject(const std::string& id, const std:: string& name,
            const std::string& description, std::shared_ptr<Teacher> teacher);

    std::string getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::shared_ptr<Teacher> getTeacher() const;

    std::string getInfo() const;
};