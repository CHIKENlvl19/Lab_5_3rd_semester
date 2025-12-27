#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "../domain/Student.h"
#include "../domain/Presentation.h"

class Student;
class Presentation;
class Subject;

// Observer Pattern - интерфейс наблюдателя
class IRegistrationObserver {
public: 
    virtual ~IRegistrationObserver() = default;
    virtual void onStudentRegistered(std::shared_ptr<Student> student,
                                    std::shared_ptr<Presentation> presentation) = 0;
    virtual void onStudentUnregistered(std::shared_ptr<Student> student,
                                      std::shared_ptr<Presentation> presentation) = 0;
};

class RegistrationService {
private: 
    std::vector<std::shared_ptr<IRegistrationObserver>> observers;

public:
    void attach(std::shared_ptr<IRegistrationObserver> observer);
    void detach(std::shared_ptr<IRegistrationObserver> observer);

    bool registerStudentForPresentation(std::shared_ptr<Student> student,
                                        std::shared_ptr<Presentation> presentation);

    bool unregisterStudentFromPresentation(std::shared_ptr<Student> student,
                                          std::shared_ptr<Presentation> presentation);

private:
    void notifyRegistration(std::shared_ptr<Student> student,
                           std:: shared_ptr<Presentation> presentation);
    void notifyUnregistration(std::shared_ptr<Student> student,
                             std::shared_ptr<Presentation> presentation);
};