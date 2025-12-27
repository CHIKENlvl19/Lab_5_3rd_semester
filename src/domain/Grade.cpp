#include "../../include/domain/Grade.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"
#include <ctime>

Grade::Grade(const std::string& id, std::shared_ptr<Student> student,
             std::shared_ptr<Subject> subject, int score, GradeType type,
             const std::string& comment)
    : id(id), student(student), subject(subject), score(score), type(type),
      comment(comment), dateIssued(std::time(nullptr)) {}

std::string Grade::getId() const {
    return id;
}

std::shared_ptr<Student> Grade::getStudent() const {
    return student;
}

std::shared_ptr<Subject> Grade::getSubject() const {
    return subject;
}

int Grade::getScore() const {
    return score;
}

GradeType Grade::getType() const {
    return type;
}

std::string Grade::getComment() const {
    return comment;
}

time_t Grade::getDateIssued() const {
    return dateIssued;
}

void Grade::setComment(const std::string& newComment) {
    comment = newComment;
}

std::string Grade::getGradeTypeString() const {
    switch (type) {
        case GradeType::PRESENTATION:
            return "Presentation";
        case GradeType:: LAB:
            return "Lab";
        case GradeType:: EXAM:
            return "Exam";
        default:
            return "Unknown";
    }
}

std::string Grade::getInfo() const {
    return "Grade: " + std::to_string(score) + " for " + getGradeTypeString() +
           " (" + student->getName() + " in " + subject->getName() + ")";
}