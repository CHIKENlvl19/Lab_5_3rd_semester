#include "../../include/domain/SubmissionRecord.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Subject.h"
#include <ctime>

SubmissionRecord:: SubmissionRecord(const std:: string& id, std::shared_ptr<Student> student,
                                   std::shared_ptr<Subject> subject, const std::string& workType,
                                   const std::string& description)
    : id(id), student(student), subject(subject), workType(workType),
      description(description), status(SubmissionStatus::PENDING),
      submittedDate(std::time(nullptr)), reviewedDate(0) {}

std::string SubmissionRecord::getId() const {
    return id;
}

std:: shared_ptr<Student> SubmissionRecord::getStudent() const {
    return student;
}

std::shared_ptr<Subject> SubmissionRecord::getSubject() const {
    return subject;
}

std::string SubmissionRecord::getWorkType() const {
    return workType;
}

std::string SubmissionRecord::getDescription() const {
    return description;
}

SubmissionStatus SubmissionRecord:: getStatus() const {
    return status;
}

time_t SubmissionRecord::getSubmittedDate() const {
    return submittedDate;
}

time_t SubmissionRecord:: getReviewedDate() const {
    return reviewedDate;
}

std::string SubmissionRecord::getReviewerComment() const {
    return reviewerComment;
}

void SubmissionRecord::approve(const std::string& comment) {
    status = SubmissionStatus::APPROVED;
    reviewedDate = std::time(nullptr);
    reviewerComment = comment;
}

void SubmissionRecord::reject(const std::string& comment) {
    status = SubmissionStatus::REJECTED;
    reviewedDate = std::time(nullptr);
    reviewerComment = comment;
}

bool SubmissionRecord::isPending() const {
    return status == SubmissionStatus::PENDING;
}

std::string SubmissionRecord::getStatusString() const {
    switch (status) {
        case SubmissionStatus::PENDING:
            return "Pending";
        case SubmissionStatus::APPROVED: 
            return "Approved";
        case SubmissionStatus:: REJECTED:
            return "Rejected";
        default:
            return "Unknown";
    }
}

std::string SubmissionRecord::getInfo() const {
    return "Submission: " + workType + " (" + getStatusString() + ") - " +
           student->getName() + " in " + subject->getName();
}