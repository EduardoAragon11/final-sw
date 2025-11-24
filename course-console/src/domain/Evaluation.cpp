#include "Evaluation.h"

Evaluation::Evaluation(double score, double weight) {
    setScore(score);
    setWeight(weight);
}

double Evaluation::getScore() const { return score; }
double Evaluation::getWeight() const { return weight; }

void Evaluation::setScore(double s) {
    if (s < 0.0 || s > 20.0) throw std::out_of_range("Score must be between 0 and 20");
    score = s;
}

void Evaluation::setWeight(double w) {
    if (w < 0.0 || w > 100.0) throw std::out_of_range("Weight must be between 0 and 100");
    weight = w;
}
