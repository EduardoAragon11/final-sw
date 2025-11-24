#include "domain/CourseConfig.h"
#include "service/StudentService.h"
#include "ui/Menu.h"
#include <iostream>

int main() {
    CourseConfig cfg;
    StudentService service(cfg);

    // Optionally, we could add some hardcoded student names but empty evals:
    // service.addStudent(Student("Ana"));
    // service.addStudent(Student("Luis"));
    // but per your requirement, start empty.

    Menu menu(service, cfg);
    menu.run();

    return 0;
}
