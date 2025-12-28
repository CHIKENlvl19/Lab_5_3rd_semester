#pragma once
#include <string>
#include <ctime>

class IDGenerator {
public:
    static std::string generateGradeID(const std::string& studentId, 
                                       const std::string& subjectId) {
        return "GRADE_" + studentId + "_" + subjectId + "_" + 
               std::to_string(std::time(nullptr));
    }
    
    static std::string generateSubmissionID(const std::string& studentId,
                                            const std::string& subjectId) {
        return "SUB_" + studentId + "_" + subjectId + "_" + 
               std::to_string(std::time(nullptr));
    }
};
