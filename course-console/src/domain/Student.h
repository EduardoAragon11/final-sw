#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Evaluation.h"

class Student {
private:
    std::string name;
    std::vector<Evaluation> evaluations;
    bool hasReachedMinimumClasses;

public:
    Student(const std::string& name = "");

    const std::string& getName() const;

    void setEvaluations(const std::vector<Evaluation>& evals);
    const std::vector<Evaluation>& getEvaluations() const;

    void setAttendance(bool v);
    bool getAttendance() const;

    // compute weighted score (without extra or attendance penalty)
    double computeWeightedScore() const;
};

#endif // STUDENT_H
