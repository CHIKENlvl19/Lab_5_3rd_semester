#include "../../include/repositories/DataRepository.h"
#include "../../include/domain/User.h"
#include "../../include/domain/Subject.h"
#include "../../include/domain/Grade.h"
#include "../../include/domain/Presentation.h"
#include "../../include/domain/SubmissionRecord.h"

std::shared_ptr<DataRepository> DataRepository::instance = nullptr;

std::shared_ptr<DataRepository> DataRepository::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<DataRepository>(new DataRepository());
    }
    return instance;
}

void DataRepository::saveUser(std::shared_ptr<User> user) {
    users[user->getId()] = user;
}

std::shared_ptr<User> DataRepository::getUser(const std::string& id) {
    auto it = users. find(id);
    return (it != users.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<User>> DataRepository::getAllUsers() {
    std::vector<std::shared_ptr<User>> result;
    for (const auto& pair : users) {
        result.push_back(pair.second);
    }
    return result;
}

void DataRepository::deleteUser(const std::string& id) {
    users.erase(id);
}

void DataRepository::saveSubject(std::shared_ptr<Subject> subject) {
    subjects[subject->getId()] = subject;
}

std::shared_ptr<Subject> DataRepository::getSubject(const std::string& id) {
    auto it = subjects.find(id);
    return (it != subjects.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Subject>> DataRepository::getAllSubjects() {
    std::vector<std::shared_ptr<Subject>> result;
    for (const auto& pair : subjects) {
        result.push_back(pair.second);
    }
    return result;
}

void DataRepository::saveGrade(std::shared_ptr<Grade> grade) {
    grades[grade->getId()] = grade;
}

std::shared_ptr<Grade> DataRepository:: getGrade(const std::string& id) {
    auto it = grades.find(id);
    return (it != grades.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Grade>> DataRepository::getAllGrades() {
    std::vector<std::shared_ptr<Grade>> result;
    for (const auto& pair :  grades) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<std::shared_ptr<Grade>> DataRepository::getGradesBySubject(
    const std::string& subjectId) {
    std::vector<std::shared_ptr<Grade>> result;
    for (const auto& pair : grades) {
        if (pair.second->getSubject()->getId() == subjectId) {
            result.push_back(pair.second);
        }
    }
    return result;
}

void DataRepository::savePresentation(std::shared_ptr<Presentation> presentation) {
    presentations[presentation->getId()] = presentation;
}

std::shared_ptr<Presentation> DataRepository::getPresentation(const std::string& id) {
    auto it = presentations.find(id);
    return (it != presentations.end()) ? it->second : nullptr;
}

std:: vector<std::shared_ptr<Presentation>> DataRepository::getPresentationsBySubject(
    const std::string& subjectId) {
    std::vector<std::shared_ptr<Presentation>> result;
    for (const auto& pair : presentations) {
        if (pair.second->getSubject()->getId() == subjectId) {
            result.push_back(pair.second);
        }
    }
    return result;
}

void DataRepository::saveSubmission(std::shared_ptr<SubmissionRecord> submission) {
    submissions[submission->getId()] = submission;
}

std::shared_ptr<SubmissionRecord> DataRepository:: getSubmission(const std::string& id) {
    auto it = submissions.find(id);
    return (it != submissions.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<SubmissionRecord>> DataRepository::getAllSubmissions() {
    std::vector<std::shared_ptr<SubmissionRecord>> result;
    for (const auto& pair :  submissions) {
        result.push_back(pair.second);
    }
    return result;
}