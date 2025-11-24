#include "CourseConfig.h"

CourseConfig::CourseConfig() : allYearsTeachers(false) { }

void CourseConfig::setExtraPoints(bool v) { allYearsTeachers = v; }
bool CourseConfig::getExtraPoints() const { return allYearsTeachers; }
