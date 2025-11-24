# Course Console (C++)

Proyecto de consola para que un docente registre evaluaciones y vea notas finales.

Reglas:
- Hasta 10 evaluaciones por estudiante
- Nota por evaluación: 0..20
- Suma de pesos = 100 (última evaluación recibe el peso restante)
- allYearsTeachers (global): si true añade +1 punto a todas las notas
- Si estudiante NO alcanzó asistencia mínima => nota final = 0
- Nota final acotada entre 0 y 20

Compilar:
```bash
make
./course_console
