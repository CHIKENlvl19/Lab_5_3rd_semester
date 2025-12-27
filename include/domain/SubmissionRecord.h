#pragma once

#include <string>
#include <memory>
#include <ctime>

enum class SubmissionStatus { PENDING, APPROVED, REJECTED };

class Student;
class Subject;

class SubmissionRecord {
private:
    std::string id;
    std::shared_ptr<Student> student;
    std:: shared_ptr<Subject> subject;
    std::string workType; // "presentation", "lab", etc.
    std::string description;
    SubmissionStatus status;
    time_t submittedDate;
    time_t reviewedDate;
    std::string reviewerComment;

public:
    SubmissionRecord(const std::string& id, std::shared_ptr<Student> student,
                     std::shared_ptr<Subject> subject, const std::string& workType,
                     const std::string& description);

    std::string getId() const;
    std::shared_ptr<Student> getStudent() const;
    std::shared_ptr<Subject> getSubject() const;
    std::string getWorkType() const;
    std::string getDescription() const;
    SubmissionStatus getStatus() const;
    time_t getSubmittedDate() const;
    time_t getReviewedDate() const;
    std::string getReviewerComment() const;

    void approve(const std::string& comment = "");
    void reject(const std::string& comment = "");
    
    bool isPending() const;
    std::string getStatusString() const;
    std::string getInfo() const;
};