#include "services/SubmissionService.h"
#include "domain/SubmissionRecord.h"
#include "domain/Student.h"
#include "domain/Subject.h"
#include <algorithm>
#include <ctime>

std::shared_ptr<SubmissionRecord> SubmissionService::createSubmission(
    std::shared_ptr<Student> student,
    std::shared_ptr<Subject> subject,
    const std::string& workType,
    const std::string& description) {
    std::string submissionId = "SUB_" + student->getId() + "_" + subject->getId() +
                               "_" + std::to_string(std::time(nullptr));
    auto submission = std::make_shared<SubmissionRecord>(submissionId, student, subject,
                                                         workType, description);
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
    std::shared_ptr<Subject> /*subject*/) {
    // В реальной реализации это должно быть в репозитории
    std::vector<std::shared_ptr<SubmissionRecord>> result;
    return result;
}

std::vector<std::shared_ptr<SubmissionRecord>> SubmissionService::getStudentSubmissions(
    std:: shared_ptr<Student> student) {
    return student->getSubmissions();
}