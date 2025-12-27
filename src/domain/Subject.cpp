#include "domain/Subject.h"
#include "domain/Teacher.h"

Subject::Subject(const std::string& id, const std::string& name,
                 const std::string& description, std::shared_ptr<Teacher> teacher)
    : id(id), name(name), description(description), teacher(teacher) {}

std::string Subject::getId() const {
    return id;
}

std::string Subject::getName() const {
    return name;
}

std::string Subject::getDescription() const {
    return description;
}

std::shared_ptr<Teacher> Subject::getTeacher() const {
    return teacher;
}

std::string Subject::getInfo() const {
    return "Subject: " + name + " (ID: " + id + ")";
}