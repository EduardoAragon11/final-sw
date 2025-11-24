#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/domain/Evaluation.h"
#include "../src/domain/Student.h"
#include "../src/domain/CourseConfig.h"
#include "../src/service/StudentService.h"

TEST_CASE("Registrar evaluaciones y obtener ponderado correcto") {
    CourseConfig cfg;
    StudentService svc(cfg);

    std::vector<Evaluation> evals = {
        Evaluation(15, 50),
        Evaluation(10, 50)
    };

    svc.registerEvaluations("Carlos", evals, true);

    auto& s = svc.getStudents().at(0);

    REQUIRE(s.getName() == "Carlos");
    REQUIRE(s.getEvaluations().size() == 2);

    double expected = 15*0.5 + 10*0.5; // 12.5
    REQUIRE(s.computeWeightedScore() == Approx(expected));
}

TEST_CASE("Nota final es 0 si no cumple asistencia") {
    CourseConfig cfg;
    StudentService svc(cfg);

    std::vector<Evaluation> evals = {
        Evaluation(18, 100)
    };

    svc.registerEvaluations("Luis", evals, false);

    auto& s = svc.getStudents().at(0);
    double final = svc.computeFinalGrade(s);

    REQUIRE(final == 0);
}

TEST_CASE("Se aplican puntos extra si allYearsTeachers = true") {
    CourseConfig cfg;
    cfg.setExtraPoints(true);  // activa punto extra

    StudentService svc(cfg);

    std::vector<Evaluation> evals = {
        Evaluation(20, 100),
    };

    svc.registerEvaluations("Ana", evals, true);

    auto& s = svc.getStudents().at(0);

    double expected = 20 + 1; // +1 punto extra
    REQUIRE(svc.computeFinalGrade(s) == Approx(expected));
}

TEST_CASE("Reemplazo completo de evaluaciones") {
    CourseConfig cfg;
    StudentService svc(cfg);

    std::vector<Evaluation> first = {
        Evaluation(10, 100)
    };

    svc.registerEvaluations("Miguel", first, true);
    REQUIRE(svc.getStudents().at(0).getEvaluations().size() == 1);

    // reemplazo
    std::vector<Evaluation> second = {
        Evaluation(20, 40),
        Evaluation(15, 60)
    };

    svc.registerEvaluations("Miguel", second, true);
    REQUIRE(svc.getStudents().at(0).getEvaluations().size() == 2);

    double expected = 20*0.4 + 15*0.6;
    REQUIRE(svc.computeFinalGrade(svc.getStudents().at(0)) == Approx(expected));
}
