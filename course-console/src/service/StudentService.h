#ifndef STUDENTSERVICE_H
#define STUDENTSERVICE_H

#include "../domain/Student.h"
#include "../domain/CourseConfig.h"
#include <vector>
#include <optional>

class StudentService {
private:
    CourseConfig& config;
    std::vector<Student> students;

public:
    StudentService(CourseConfig& cfg);

    // Student management
    const std::vector<Student>& getStudents() const;
    std::optional<std::reference_wrapper<Student>> findStudentByName(const std::string& name);
    void addStudent(const Student& s);

    // Register/sobrescribir evaluaciones para un estudiante (crea si no existe)
    // Throws runtime_error on invalid input
    void registerEvaluations(const std::string& studentName,
                             const std::vector<Evaluation>& evals,
                             bool attendance);

    // Compute final grade applying rules:
    // if attendance == false -> 0
    // else final = weighted + (allYearsTeachers ? +1 : 0)
    // final clamped to [0,20]
    double computeFinalGrade(const Student& s) const;
};

#endif // STUDENTSERVICE_H
