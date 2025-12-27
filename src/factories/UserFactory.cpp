#include "../../include/factories/UserFactory.h"
#include "../../include/domain/Teacher.h"
#include "../../include/domain/Student.h"

std::shared_ptr<Teacher> UserFactory::createTeacher(const std::string& id,
                                                     const std::string& name,
                                                     const std::string& email) {
    return std::make_shared<Teacher>(id, name, email);
}

std::shared_ptr<Student> UserFactory::createStudent(const std::string& id,
                                                     const std::string& name,
                                                     const std::string& email) {
    return std::make_shared<Student>(id, name, email);
}