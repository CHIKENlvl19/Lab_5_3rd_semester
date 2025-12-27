#include "../../include/domain/Student.h"
#include "../../include/domain/Grade.h"
#include "../../include/domain/Subject.h"
#include "../../include/domain/Presentation.h"
#include "../../include/domain/SubmissionRecord.h"

Student::Student(const std::string& id, const std::string& name,
                 const std::string& email)
    : User(id, name, email, UserRole:: STUDENT) {}

void Student::enrollSubject(std::shared_ptr<Subject> subject) {
    enrolledSubjects.push_back(subject);
}

void Student::withdrawSubject(const std::string& subjectId) {
    enrolledSubjects.erase(
        std::remove_if(enrolledSubjects.begin(), enrolledSubjects.end(),
                      [&subjectId](const std::shared_ptr<Subject>& s) {
                          return s->getId() == subjectId;
                      }),
        enrolledSubjects.end());
}

std::vector<std::shared_ptr<Subject>> Student::getEnrolledSubjects() const {
    return enrolledSubjects;
}

void Student::addGrade(std::shared_ptr<Grade> grade) {
    grades.push_back(grade);
}

std::vector<std::shared_ptr<Grade>> Student::getGrades() const {
    return grades;
}

std::vector<std::shared_ptr<Grade>> Student::getGradesBySubject(
    const std::string& subjectId) const {
    std::vector<std::shared_ptr<Grade>> result;
    for (const auto& grade : grades) {
        if (grade->getSubject()->getId() == subjectId) {
            result.push_back(grade);
        }
    }
    return result;
}

void Student::registerForPresentation(std::shared_ptr<Presentation> presentation) {
    registeredPresentations[presentation->getId()] = presentation;
}

void Student::unregisterFromPresentation(const std:: string& presentationId) {
    registeredPresentations.erase(presentationId);
}

bool Student::isRegisteredForPresentation(const std::string& presentationId) const {
    return registeredPresentations.find(presentationId) != registeredPresentations.end();
}

std::vector<std::shared_ptr<Presentation>> Student::getRegisteredPresentations() const {
    std::vector<std::shared_ptr<Presentation>> result;
    for (const auto& pair : registeredPresentations) {
        result.push_back(pair. second);
    }
    return result;
}

void Student:: addSubmission(std::shared_ptr<SubmissionRecord> submission) {
    submissions.push_back(submission);
}

std::vector<std::shared_ptr<SubmissionRecord>> Student:: getSubmissions() const {
    return submissions;
}

std:: vector<std::shared_ptr<SubmissionRecord>> Student::getPendingSubmissions() const {
    std::vector<std::shared_ptr<SubmissionRecord>> result;
    for (const auto& submission : submissions) {
        if (submission->isPending()) {
            result.push_back(submission);
        }
    }
    return result;
}

std::string Student:: getInfo() const {
    return "Student: " + name + " (ID: " + id + ", Email: " + email + ")";
}