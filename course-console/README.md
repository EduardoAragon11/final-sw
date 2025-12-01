# Course Console (C++)

Proyecto de consola para que un docente registre evaluaciones y vea notas finales.

Reglas:
- Hasta 10 evaluaciones por estudiante
- Nota por evaluacion: 0..20
- Suma de pesos = 100 (ultima evaluacion recibe el peso restante)
- allYearsTeachers (global): si true añade +1 punto a todas las notas
- Si estudiante NO alcanzo asistencia minima => nota final = 0
- Nota final acotada entre 0 y 20

## Compilación

```bash
make
./course_console
```

## Tests

```bash
make tests
./run_tests.exe
```

## Cobertura de Código

Para generar el reporte de cobertura y análisis estático:

```bash
./coverage.sh
```

### Reporte de Cobertura y Análisis

#### Reporte de Coverage en Terminal

```
========================================
   REPORTE DE COVERAGE EN TERMINAL
========================================

RESUMEN DE COBERTURA:

------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/domain/CourseConfig.cpp                    3       2    66%   5
src/domain/Evaluation.cpp                     14      14   100%
src/domain/Student.cpp                        16      16   100%
src/domain/Student.h                           1       1   100%
src/service/StudentService.cpp                43      42    97%   38
src/service/StudentService.h                   0       0    --%
src/ui/Menu.cpp                              121       0     0%   6,8-17,20,22-28,30,32-36,38-40,44,46-50,52-54,58-67,69-75,77,79-81,84,86-87,89-92,94-99,101-108,111-113,116,119-124,126-131,135-140,142-148,151-153,155,157,159-166
------------------------------------------------------------------------------
TOTAL                                        198      75    37%
------------------------------------------------------------------------------
```

#### Análisis Estático (Code Smells)

```
========================================
   ANÁLISIS ESTÁTICO (CODE SMELLS)
========================================

Ejecutando cppcheck...

Resultados de cppcheck:

  Errores encontrados: 8

  Errores críticos:
    [style] src/domain/Evaluation.cpp: Class 'Evaluation' has a constructor with 1 argument that is not explicit.
    [style] src/domain/Student.cpp: Class 'Student' has a constructor with 1 argument that is not explicit.
    [style] src/domain/Student.cpp: Consider using std::accumulate algorithm instead of a raw loop.
    [style] src/main.cpp: Class 'StudentService' has a constructor with 1 argument that is not explicit.

  Reporte completo guardado en: cppcheck_report.xml
```

#### Estadísticas del Código

```
========================================
   ESTADÍSTICAS DEL CÓDIGO
========================================

Metricas basicas:

  Archivos fuente:
     - Archivos .cpp: 6
     - Archivos .h: 5
     - Total lineas: 430

  Estructura del codigo:
     - Clases: 5
     - Funciones (aprox): 69

  Tests:
     - Archivos de test: 1
```

#### Resumen Final de Cobertura

```
========================================
   RESUMEN FINAL DE COBERTURA
========================================

COBERTURA TOTAL: 37%
  - Líneas ejecutadas: 75
  - Líneas totales: 198
```

**Nota:** Para obtener reportes más detallados, instala gcovr:
- macOS: `brew install gcovr`
- Linux: `pip install gcovr` o `apt-get install gcovr`