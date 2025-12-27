#include "../../include/services/RegistrationService.h"
#include "../../include/domain/Student.h"
#include "../../include/domain/Presentation.h"

void RegistrationService::attach(std::shared_ptr<IRegistrationObserver> observer) {
    observers.push_back(observer);
}

void RegistrationService:: detach(std::shared_ptr<IRegistrationObserver> observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end());
}

bool RegistrationService::registerStudentForPresentation(
    std::shared_ptr<Student> student,
    std::shared_ptr<Presentation> presentation) {
    if (! presentation->registerStudent(student)) {
        return false;
    }
    notifyRegistration(student, presentation);
    return true;
}

bool RegistrationService::unregisterStudentFromPresentation(
    std::shared_ptr<Student> student,
    std::shared_ptr<Presentation> presentation) {
    if (!presentation->unregisterStudent(student->getId())) {
        return false;
    }
    student->unregisterFromPresentation(presentation->getId());
    notifyUnregistration(student, presentation);
    return true;
}

void RegistrationService::notifyRegistration(std::shared_ptr<Student> student,
                                            std::shared_ptr<Presentation> presentation) {
    for (const auto& observer : observers) {
        observer->onStudentRegistered(student, presentation);
    }
}

void RegistrationService::notifyUnregistration(std::shared_ptr<Student> student,
                                              std::shared_ptr<Presentation> presentation) {
    for (const auto& observer : observers) {
        observer->onStudentUnregistered(student, presentation);
    }
}