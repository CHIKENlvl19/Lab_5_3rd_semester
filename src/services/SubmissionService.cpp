#include "services/SubmissionService.h"
#include "repositories/DataRepository.h"
#include "domain/SubmissionRecord.h"
#include "domain/Student.h"
#include "domain/Subject.h"
#include "utils/IDGenerator.h"
#include <algorithm>
#include <ctime>
#include <stdexcept>

std::shared_ptr<SubmissionRecord> SubmissionService::createSubmission(
    std::shared_ptr<Student> student,
    std::shared_ptr<Subject> subject,
    const std::string& workType,
    const std::string& description) {
    
    if (!student) {
        throw std::invalid_argument("Student cannot be null");
    } 
    if (!subject) {
        throw std::invalid_argument("Subject cannot be null");
    } 
    if (workType.empty()) {
        throw std::invalid_argument("Work type cannot be empty");
    }
    
    std::string submissionId = IDGenerator::generateSubmissionID(student->getId(), subject->getId());

    auto submission = std::make_shared<SubmissionRecord>(
        submissionId, student, subject, workType, description);
    student->addSubmission(submission);
    
    return submission;
}

bool SubmissionService::approveSubmission(std::shared_ptr<SubmissionRecord> submission,
                                         const std::string& comment) {
    if (!submission->isPending()) {
        return false;
    }
    submission->approve(comment);
    return true;
}

bool SubmissionService::rejectSubmission(std:: shared_ptr<SubmissionRecord> submission,
                                        const std::string& comment) {
    if (!submission->isPending()) {
        return false;
    }
    submission->reject(comment);
    return true;
}

std::vector<std::shared_ptr<SubmissionRecord>> SubmissionService::getPendingSubmissions(
    std::shared_ptr<Subject> subject) {
    auto repo = DataRepository::getInstance();
    auto allSubmissions = repo->getAllSubmissions();
    
    std::vector<std::shared_ptr<SubmissionRecord>> result;
    for (const auto& submission : allSubmissions) {
        if (submission->getSubject()->getId() == subject->getId() && 
            submission->isPending()) {
            result.push_back(submission);
        }
    }
    
    return result;
}

std::vector<std::shared_ptr<SubmissionRecord>> SubmissionService::getStudentSubmissions(
    std:: shared_ptr<Student> student) {
    return student->getSubmissions();
}