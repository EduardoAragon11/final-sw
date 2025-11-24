#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdexcept>

class Evaluation {
private:
    double score; // 0..20
    double weight; // 0..100 (percentage)

public:
    Evaluation(double score = 0.0, double weight = 0.0);

    double getScore() const;
    double getWeight() const;

    void setScore(double s);
    void setWeight(double w);
};

#endif // EVALUATION_H
