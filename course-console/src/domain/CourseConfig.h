#ifndef COURSECONFIG_H
#define COURSECONFIG_H

class CourseConfig {
private:
    bool allYearsTeachers; // default false

public:
    CourseConfig();

    void setExtraPoints(bool v);
    bool getExtraPoints() const;
};

#endif // COURSECONFIG_H
