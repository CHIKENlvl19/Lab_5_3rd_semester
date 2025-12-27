#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "../domain/User.h"
#include "../domain/Teacher.h"
#include "../domain/Student.h"
#include "../domain/Subject.h"
#include "../domain/Grade.h"
#include "../domain/Presentation.h"
#include "../domain/SubmissionRecord.h"

class User;
class Teacher;
class Student;
class Subject;
class Grade;
class Presentation;
class SubmissionRecord;

// Singleton + Repository Pattern
class DataRepository {
private: 
    static std::shared_ptr<DataRepository> instance;
    
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<std::string, std::shared_ptr<Subject>> subjects;
    std::map<std::string, std::shared_ptr<Grade>> grades;
    std::map<std::string, std::shared_ptr<Presentation>> presentations;
    std::map<std:: string, std::shared_ptr<SubmissionRecord>> submissions;

    DataRepository() = default;

public: 
    static std::shared_ptr<DataRepository> getInstance();

    // Users
    void saveUser(std::shared_ptr<User> user);
    std::shared_ptr<User> getUser(const std::string& id);
    std::vector<std:: shared_ptr<User>> getAllUsers();
    void deleteUser(const std::string& id);

    // Subjects
    void saveSubject(std::shared_ptr<Subject> subject);
    std::shared_ptr<Subject> getSubject(const std::string& id);
    std::vector<std::shared_ptr<Subject>> getAllSubjects();

    // Grades
    void saveGrade(std::shared_ptr<Grade> grade);
    std::shared_ptr<Grade> getGrade(const std::string& id);
    std::vector<std::shared_ptr<Grade>> getAllGrades();
    std::vector<std::shared_ptr<Grade>> getGradesBySubject(const std::string& subjectId);

    // Presentations
    void savePresentation(std::shared_ptr<Presentation> presentation);
    std::shared_ptr<Presentation> getPresentation(const std:: string& id);
    std::vector<std::shared_ptr<Presentation>> getPresentationsBySubject(const std::string& subjectId);

    // Submissions
    void saveSubmission(std::shared_ptr<SubmissionRecord> submission);
    std::shared_ptr<SubmissionRecord> getSubmission(const std::string& id);
    std::vector<std::shared_ptr<SubmissionRecord>> getAllSubmissions();
};