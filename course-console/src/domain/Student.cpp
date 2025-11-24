#include "Student.h"
#include <numeric>

Student::Student(const std::string& name) : name(name), hasReachedMinimumClasses(false) { }

const std::string& Student::getName() const { return name; }

void Student::setEvaluations(const std::vector<Evaluation>& evals) {
    evaluations = evals;
}

const std::vector<Evaluation>& Student::getEvaluations() const {
    return evaluations;
}

void Student::setAttendance(bool v) { hasReachedMinimumClasses = v; }
bool Student::getAttendance() const { return hasReachedMinimumClasses; }

double Student::computeWeightedScore() const {
    // Weighted sum: sum(score * weight/100)
    double sum = 0.0;
    for (const auto& e : evaluations) {
        sum += e.getScore() * (e.getWeight() / 100.0);
    }
    // Clamp to 0..20 just in case
    if (sum < 0.0) sum = 0.0;
    if (sum > 20.0) sum = 20.0;
    return sum;
}
