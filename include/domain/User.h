#pragma once

#include <string>
#include <memory>

enum class UserRole { TEACHER, STUDENT };

class User {
protected:
    std::string id;
    std::string name;
    std::string email;
    UserRole role;

public:
    User(const std::string& id, const std::string& name, 
         const std::string& email, UserRole role);
    virtual ~User() = default;

    virtual std::string getId() const;
    virtual std:: string getName() const;
    virtual std::string getEmail() const;
    virtual UserRole getRole() const;
    virtual std::string getInfo() const = 0;
};