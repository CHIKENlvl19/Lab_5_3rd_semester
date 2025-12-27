#pragma once

#include <string>
#include <memory>
#include <ctime>

enum class GradeType { PRESENTATION, LAB, EXAM };

class Student;
class Subject;

class Grade {
private:
    std::string id;
    std::shared_ptr<Student> student;
    std::shared_ptr<Subject> subject;
    int score; // 0-100
    GradeType type;
    std::string comment;
    time_t dateIssued;

public:
    Grade(const std::string& id, std::shared_ptr<Student> student,
          std::shared_ptr<Subject> subject, int score, GradeType type,
          const std::string& comment = "");

    std::string getId() const;
    std::shared_ptr<Student> getStudent() const;
    std::shared_ptr<Subject> getSubject() const;
    int getScore() const;
    GradeType getType() const;
    std::string getComment() const;
    time_t getDateIssued() const;

    void setComment(const std::string& newComment);
    std::string getGradeTypeString() const;
    std::string getInfo() const;
};