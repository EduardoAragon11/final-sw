#ifndef MENU_H
#define MENU_H

#include "../service/StudentService.h"
#include "../domain/CourseConfig.h"
#include <iostream>

class Menu {
private:
    StudentService& service;
    CourseConfig& config;

public:
    Menu(StudentService& svc, CourseConfig& cfg);

    void run();

private:
    void showMainMenu();
    void handleRegister();
    void handleReview();
    void handleConfig();
    int readIntInRange(const std::string& prompt, int minVal, int maxVal);
    double readDoubleInRange(const std::string& prompt, double minVal, double maxVal);
    bool askYesNo(const std::string& prompt);
    std::string readNonEmptyLine(const std::string& prompt);
};

#endif // MENU_H
