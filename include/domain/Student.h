#pragma once

#include "User.h"
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

class Subject;
class Grade;
class Presentation;
class SubmissionRecord;

class Student :  public User {
private:
    std::vector<std::shared_ptr<Subject>> enrolledSubjects;
    std:: vector<std::shared_ptr<Grade>> grades;
    std::map<std::string, std::shared_ptr<Presentation>> registeredPresentations;
    std::vector<std::shared_ptr<SubmissionRecord>> submissions;

public:
    Student(const std:: string& id, const std::string& name, 
            const std::string& email);

    void enrollSubject(std:: shared_ptr<Subject> subject);
    void withdrawSubject(const std::string& subjectId);
    std::vector<std::shared_ptr<Subject>> getEnrolledSubjects() const;

    void addGrade(std::shared_ptr<Grade> grade);
    std::vector<std::shared_ptr<Grade>> getGrades() const;
    std::vector<std::shared_ptr<Grade>> getGradesBySubject(const std:: string& subjectId) const;

    void registerForPresentation(std::shared_ptr<Presentation> presentation);
    void unregisterFromPresentation(const std::string& presentationId);
    bool isRegisteredForPresentation(const std::string& presentationId) const;
    std::vector<std::shared_ptr<Presentation>> getRegisteredPresentations() const;

    void addSubmission(std:: shared_ptr<SubmissionRecord> submission);
    std::vector<std::shared_ptr<SubmissionRecord>> getSubmissions() const;
    std::vector<std::shared_ptr<SubmissionRecord>> getPendingSubmissions() const;

    std::string getInfo() const override;
};