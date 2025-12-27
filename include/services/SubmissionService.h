#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../domain/Student.h"
#include "../domain/Subject.h"
#include "../domain/SubmissionRecord.h"
#include "../domain/Grade.h"

class Student;
class Subject;
class SubmissionRecord;
class Grade;

class SubmissionService {
public:
    std::shared_ptr<SubmissionRecord> createSubmission(
        std::shared_ptr<Student> student,
        std::shared_ptr<Subject> subject,
        const std::string& workType,
        const std::string& description);

    bool approveSubmission(std::shared_ptr<SubmissionRecord> submission,
                          const std::string& comment = "");

    bool rejectSubmission(std::shared_ptr<SubmissionRecord> submission,
                         const std::string& comment = "");

    std::vector<std::shared_ptr<SubmissionRecord>> getPendingSubmissions(
        std::shared_ptr<Subject> subject);

    std::vector<std::shared_ptr<SubmissionRecord>> getStudentSubmissions(
        std:: shared_ptr<Student> student);
};