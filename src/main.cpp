#include <iostream>
#include <memory>
#include <vector>
#include "domain/Teacher.h"
#include "domain/Student.h"
#include "domain/Subject.h"
#include "domain/Presentation.h"
#include "domain/Grade.h"
#include "domain/SubmissionRecord.h"
#include "factories/UserFactory.h"
#include "services/TeacherService.h"
#include "services/GradeService.h"
#include "services/RegistrationService.h"
#include "services/SubmissionService.h"
#include "services/ReportService.h"
#include "strategies/GradeCalculationStrategy.h"
#include "strategies/ReportFormatters.h"
#include "repositories/DataRepository.h"

// Observer реализация для демонстрации паттерна Observer
class ConsoleNotificationObserver : public IRegistrationObserver {
public: 
    void onStudentRegistered(std::shared_ptr<Student> student,
                            std::shared_ptr<Presentation> presentation) override {
        std::cout << "Student " << student->getName() << " registered for "
                  << presentation->getTitle() << std::endl;
    }

    void onStudentUnregistered(std::shared_ptr<Student> student,
                              std::shared_ptr<Presentation> presentation) override {
        std::cout << "Student " << student->getName() << " unregistered from "
                  << presentation->getTitle() << std::endl;
    }
};

int main() {
    std::cout << "Grade Management System" << std::endl << std::endl;

    // 1. Создание пользователей через Factory Pattern
    std::cout << "1 Creating users.. .\n" << std::endl;
    
    auto teacher1 = UserFactory::createTeacher("T001", "Dr. Smith", "smith@university.edu");
    auto teacher2 = UserFactory::createTeacher("T002", "Dr. Johnson", "johnson@university.edu");
    
    auto student1 = UserFactory::createStudent("S001", "Alice", "alice@student.edu");
    auto student2 = UserFactory::createStudent("S002", "Bob", "bob@student.edu");
    auto student3 = UserFactory::createStudent("S003", "Carol", "carol@student.edu");

    std::cout << teacher1->getInfo() << std::endl;
    std::cout << student1->getInfo() << std::endl << std::endl;

    // 2. Создание предметов
    std::cout << "2 Creating subjects.. .\n" << std::endl;
    
    TeacherService teacherService;
    auto subject1 = teacherService.createSubject("SUB001", "C++ Advanced",
                                                  "Advanced C++ programming", teacher1);
    auto subject2 = teacherService.createSubject("SUB002", "Data Structures",
                                                  "Algorithms and Data Structures", teacher2);

    std::cout << subject1->getInfo() << std::endl;
    std::cout << subject2->getInfo() << std::endl << std::endl;

    // 3. Регистрация студентов на предметы
    std::cout << "3 Registering students for subjects...\n" << std:: endl;
    
    teacherService.registerStudent(teacher1, student1);
    teacherService. registerStudent(teacher1, student2);
    teacherService.registerStudent(teacher1, student3);
    teacherService.registerStudent(teacher2, student1);

    std::cout << "Registered " << teacher1->getRegisteredStudents().size()
              << " students for " << subject1->getName() << std::endl << std::endl;

    // 4. Создание докладов
    std::cout << "4 Creating presentations...\n" << std:: endl;
    
    time_t now = std::time(nullptr);
    auto presentation1 = teacherService. createPresentation("PRES001", "Modern C++ Features",
                                                           subject1, 2, now + 86400);
    auto presentation2 = teacherService.createPresentation("PRES002", "Smart Pointers",
                                                           subject1, 2, now + 172800);

    std::cout << presentation1->getInfo() << std::endl;
    std::cout << presentation2->getInfo() << std::endl << std::endl;

    // 5. Регистрация студентов на доклады (Observer Pattern)
    std::cout << "5 Students registering for presentations (Observer Pattern)...\n" << std::endl;
    
    RegistrationService regService;
    auto notificationObserver = std::make_shared<ConsoleNotificationObserver>();
    regService.attach(notificationObserver);

    regService.registerStudentForPresentation(student1, presentation1);
    regService.registerStudentForPresentation(student2, presentation1);
    regService.registerStudentForPresentation(student3, presentation2);

    std::cout << "\nPresentation 1 capacity: " << presentation1->getRegisteredCount()
              << "/" << presentation1->getCapacity() << std::endl;
    std::cout << "Presentation 2 capacity: " << presentation2->getRegisteredCount()
              << "/" << presentation2->getCapacity() << std::endl << std:: endl;

    // 6. Попытка зарегистрировать ещё одного студента на полный доклад
    std::cout << "6 Attempting to register student for full presentation...\n" << std::endl;
    
    bool registered = regService.registerStudentForPresentation(student2, presentation2);
    if (! registered) {
        std::cout << "Presentation 2 is full!" << std::endl << std::endl;
    }

    // 7. Студент спрыгивает с доклада
    std::cout << "7 Student unregistering from presentation...\n" << std::endl;
    
    regService.unregisterStudentFromPresentation(student1, presentation1);
    std::cout << "After unregistration, Presentation 1 capacity: "
              << presentation1->getRegisteredCount() << "/" << presentation1->getCapacity()
              << std::endl << std::endl;

    // 8. Создание записей о сдаче (Submission)
    std::cout << "8 Students submitting work...\n" << std::endl;
    
    SubmissionService submissionService;
    auto submission1 = submissionService. createSubmission(student1, subject1, "presentation",
                                                         "Presented on Modern C++ Features");
    auto submission2 = submissionService.createSubmission(student2, subject1, "lab",
                                                         "Completed Lab 1: Smart Pointers");

    std::cout << submission1->getInfo() << std::endl;
    std::cout << submission2->getInfo() << std::endl << std::endl;

    // 9. Преподаватель утверждает сдачу
    std::cout << "9 Teacher approving/rejecting submissions...\n" << std::endl;
    
    submissionService.approveSubmission(submission1, "Great presentation!");
    submissionService.rejectSubmission(submission2, "Please redo the lab");

    std::cout << submission1->getInfo() << " - " << submission1->getStatusString() << std::endl;
    std::cout << submission2->getInfo() << " - " << submission2->getStatusString() << std::endl << std::endl;

    // 10. Выставление оценок (Strategy Pattern)
    std::cout << "10 Issuing grades (Strategy Pattern)...\n" << std::endl;
    
    GradeService gradeService;
    
    // Используем взвешенный алгоритм
    auto weightedStrategy = std::make_shared<WeightedAverageStrategy>(0.3, 0.3, 0.4);
    gradeService.setCalculationStrategy(weightedStrategy);

    auto grade1 = gradeService.createGrade(student1, subject1, 85, GradeType:: PRESENTATION, "Good");
    auto grade2 = gradeService.createGrade(student1, subject1, 90, GradeType::LAB, "Excellent");
    auto grade3 = gradeService.createGrade(student1, subject1, 88, GradeType::EXAM, "Very good");

    gradeService.issueGrade(grade1, student1);
    gradeService.issueGrade(grade2, student1);
    gradeService.issueGrade(grade3, student1);

    std::cout << grade1->getInfo() << std::endl;
    std::cout << grade2->getInfo() << std::endl;
    std::cout << grade3->getInfo() << std::endl << std::endl;

    // 11. Расчёт итоговой оценки
    std::cout << "11 Calculating final grade...\n" << std::endl;
    
    int finalGrade = gradeService.calculateFinalGrade(student1, subject1);
    std::cout << "Final grade for " << student1->getName() << " in " << subject1->getName()
              << ": " << finalGrade << std::endl << std::endl;

    // 12. Сохранение данных в репозиторий (Singleton + Repository Pattern)
    std::cout << "12 Saving data to repository (Singleton Pattern)...\n" << std::endl;
    
    auto repo = DataRepository::getInstance();
    repo->saveUser(teacher1);
    repo->saveUser(teacher2);
    repo->saveUser(student1);
    repo->saveUser(student2);
    repo->saveUser(student3);
    repo->saveSubject(subject1);
    repo->saveSubject(subject2);
    repo->saveGrade(grade1);
    repo->saveGrade(grade2);
    repo->saveGrade(grade3);
    repo->savePresentation(presentation1);
    repo->savePresentation(presentation2);
    repo->saveSubmission(submission1);
    repo->saveSubmission(submission2);

    std::cout << "Saved " << repo->getAllUsers().size() << " users" << std::endl;
    std::cout << "Saved " << repo->getAllSubjects().size() << " subjects" << std::endl;
    std:: cout << "Saved " << repo->getAllGrades().size() << " grades" << std::endl;
    std::cout << "Saved " << repo->getAllSubmissions().size() << " submissions" << std::endl << std::endl;

    // 13. Добавление коллеги
    std::cout << "13 Adding colleague (Teacher cooperation)...\n" << std::endl;
    
    teacherService.addColleague(teacher1, teacher2);
    std::cout << teacher1->getName() << " now has " << teacher1->getColleagues().size()
              << " colleague(s)" << std::endl << std::endl;

    // 14. Выгрузка отчёта (Strategy Pattern для форматирования)
    std::cout << "14 Generating reports (Report Formatter Strategy)...\n" << std::endl;
    
    // CSV формат
    auto csvFormatter = std::make_shared<CSVFormatter>();
    ReportService reportServiceCSV(csvFormatter);
    std::cout << "CSV Report:\n" << reportServiceCSV.exportSubjectResults(subject1) << std::endl;

    // JSON формат
    auto jsonFormatter = std::make_shared<JSONFormatter>();
    reportServiceCSV.setFormatter(jsonFormatter);
    std::cout << "JSON Report:\n" << reportServiceCSV.exportSubjectResults(subject1) << std::endl;

    // Plain Text формат
    auto textFormatter = std::make_shared<PlainTextFormatter>();
    reportServiceCSV.setFormatter(textFormatter);
    std::cout << "Plain Text Report:\n" << reportServiceCSV.exportSubjectResults(subject1) << std::endl;

    // 15. Демонстрация других стратегий расчёта оценок
    std::cout << "\n15 Testing different grade calculation strategies...\n" << std::endl;

    auto simpleStrategy = std::make_shared<SimpleAverageStrategy>();
    gradeService.setCalculationStrategy(simpleStrategy);
    int simpleAverage = gradeService.calculateFinalGrade(student1, subject1);
    std::cout << "Simple Average: " << simpleAverage << std::endl;

    auto maxStrategy = std::make_shared<MaximumGradeStrategy>();
    gradeService.setCalculationStrategy(maxStrategy);
    int maxGrade = gradeService. calculateFinalGrade(student1, subject1);
    std::cout << "Maximum Grade: " << maxGrade << std::endl;

    std::cout << "\nProgram completed successfully!" << std::endl;

    return 0;
}