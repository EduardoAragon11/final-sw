#include "Menu.h"
#include <limits>
#include <iomanip>
#include <sstream>

Menu::Menu(StudentService& svc, CourseConfig& cfg) : service(svc), config(cfg) {}

void Menu::run() {
    while (true) {
        showMainMenu();
        int opt = readIntInRange("Selecciona una opcion: ", 1, 4);
        switch (opt) {
            case 1: handleRegister(); break;
            case 2: handleReview(); break;
            case 3: handleConfig(); break;
            case 4: std::cout << "Saliendo...\n"; return;
            default: break;
        }
    }
}

void Menu::showMainMenu() {
    std::cout << "\n==== Menu Principal ====\n";
    std::cout << "1) Registrar / Actualizar evaluaciones\n";
    std::cout << "2) Revisar estudiantes (tabla)\n";
    std::cout << "3) Configurar puntos extra global (allYearsTeachers)\n";
    std::cout << "4) Salir\n";
}

int Menu::readIntInRange(const std::string& prompt, int minVal, int maxVal) {
    int v;
    while (true) {
        std::cout << prompt;
        if ((std::cin >> v) && v >= minVal && v <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cout << "Entrada invalida. Intenta de nuevo.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double Menu::readDoubleInRange(const std::string& prompt, double minVal, double maxVal) {
    double v;
    while (true) {
        std::cout << prompt;
        if ((std::cin >> v) && v >= minVal && v <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cout << "Entrada invalida. Intenta de nuevo.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool Menu::askYesNo(const std::string& prompt) {
    while (true) {
        std::string s;
        std::cout << prompt << " (s/n): ";
        std::getline(std::cin, s);
        if (s == "s" || s == "S" || s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "Respuesta invalida.\n";
    }
}

std::string Menu::readNonEmptyLine(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, s);
        if (!s.empty()) return s;
        std::cout << "No puede estar vacio.\n";
    }
}

void Menu::handleRegister() {
    std::cout << "\n-- Registrar / Actualizar evaluaciones --\n";
    std::string studentName = readNonEmptyLine("Nombre del estudiante: ");

    // Number of evaluations
    int n = readIntInRange("Numero de evaluaciones (1-10): ", 1, 10);

    std::vector<Evaluation> evals;
    evals.reserve(n);

    double accumulatedWeight = 0.0;
    for (int i = 1; i <= n; ++i) {
        double remaining = 100.0 - accumulatedWeight;
        if (i == n) {
            // last one gets remaining automatically
            std::cout << "ultima evaluacion: se asignara automaticamente el peso restante: " << remaining << "%\n";
            double score = readDoubleInRange("Nota (0-20): ", 0.0, 20.0);
            evals.emplace_back(score, remaining);
            accumulatedWeight += remaining;
        } else {
            double score = readDoubleInRange("Nota (0-20): ", 0.0, 20.0);
            // ask weight but ensure not exceeding 100
            double maxAllowed = remaining;
            std::ostringstream oss;
            oss << "Peso en % para esta evaluacion (0 - " << maxAllowed << "): ";
            double w = readDoubleInRange(oss.str(), 0.0, maxAllowed);
            evals.emplace_back(score, w);
            accumulatedWeight += w;
        }
    }

    // After collection, accumulatedWeight should be 100
    if (std::abs(accumulatedWeight - 100.0) > 1e-6) {
        std::cout << "Error: la suma de pesos no es 100. Operacion cancelada.\n";
        return;
    }

    bool attendance = askYesNo("¿Alcanzo asistencia minima?");

    try {
        service.registerEvaluations(studentName, evals, attendance);
        std::cout << "Evaluaciones registradas para " << studentName << ".\n";
    } catch (const std::exception& ex) {
        std::cout << "Error al registrar: " << ex.what() << "\n";
    }
}

void Menu::handleReview() {
    std::cout << "\n-- Tabla de estudiantes --\n";
    const auto& students = service.getStudents();
    if (students.empty()) {
        std::cout << "No hay estudiantes registrados.\n";
        return;
    }

    // Print header
    std::cout << std::left << std::setw(20) << "Nombre"
              << std::setw(20) << "Asistencia"
              << std::setw(15) << "PuntosExtra"
              << std::setw(10) << "Final"
              << "Evaluaciones (nota|peso)\n";
    std::cout << std::string(90, '-') << "\n";

    for (const auto& s : students) {
        bool extra = config.getExtraPoints();
        double finalGrade = service.computeFinalGrade(s);
        std::cout << std::left << std::setw(20) << s.getName()
                  << std::setw(20) << (s.getAttendance() ? "Si" : "No")
                  << std::setw(15) << (extra ? "Si (+1)" : "No")
                  << std::setw(10) << std::fixed << std::setprecision(2) << finalGrade;

        // evaluations list
        const auto& evs = s.getEvaluations();
        for (const auto& e : evs) {
            std::cout << " " << e.getScore() << "|" << e.getWeight() << "%";
        }
        std::cout << "\n";
    }
}

void Menu::handleConfig() {
    std::cout << "\n-- Configurar puntos extra global --\n";
    bool cur = config.getExtraPoints();
    std::cout << "Valor actual allYearsTeachers: " << (cur ? "True" : "False") << "\n";
    bool val = askYesNo("Establecer allYearsTeachers = True ?");
    config.setExtraPoints(val);
    std::cout << "Configuracion actualizada.\n";
}
