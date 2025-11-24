#include "StudentService.h"
#include <stdexcept>
#include <algorithm>

StudentService::StudentService(CourseConfig& cfg) : config(cfg) { }

const std::vector<Student>& StudentService::getStudents() const { return students; }

std::optional<std::reference_wrapper<Student>> StudentService::findStudentByName(const std::string& name) {
    for (auto &s : students) {
        if (s.getName() == name) return std::ref(s);
    }
    return std::nullopt;
}

void StudentService::addStudent(const Student& s) {
    // avoid duplicate names
    if (findStudentByName(s.getName())) return;
    students.push_back(s);
}

void StudentService::registerEvaluations(const std::string& studentName,
                                         const std::vector<Evaluation>& evals,
                                         bool attendance) {
    if (evals.size() > 10) throw std::runtime_error("Maximum 10 evaluations allowed");

    double totalWeight = 0.0;
    for (size_t i = 0; i < evals.size(); ++i) {
        double w = evals[i].getWeight();
        double sc = evals[i].getScore();
        if (sc < 0.0 || sc > 20.0) throw std::runtime_error("Score must be between 0 and 20");
        if (w < 0.0 || w > 100.0) throw std::runtime_error("Each weight must be between 0 and 100");
        totalWeight += w;
    }
    // weights must sum exactly 100. Because last weight might be 0 if caller set so,
    // this checking expects caller to pass correct weights (we'll handle 'auto last' in UI).
    if (std::abs(totalWeight - 100.0) > 1e-6) {
        throw std::runtime_error("Sum of weights must be 100");
    }

    // find or create student
    auto opt = findStudentByName(studentName);
    if (opt) {
        Student& s = opt->get();
        s.setEvaluations(evals);
        s.setAttendance(attendance);
    } else {
        Student s(studentName);
        s.setEvaluations(evals);
        s.setAttendance(attendance);
        addStudent(s);
    }
}

double StudentService::computeFinalGrade(const Student& s) const {
    if (!s.getAttendance()) return 0.0;
    double base = s.computeWeightedScore();
    if (config.getExtraPoints()) base += 1.0;
    if (base < 0.0) base = 0.0;
    if (base > 20.0) base = 20.0;
    return base;
}
