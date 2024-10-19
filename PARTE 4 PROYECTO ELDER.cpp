#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Estudiante {
    string nombre;
    string apellido;
    string carrera;
    vector<string> cursos;
    vector<double> notas;
};

void ReporteDatosGenerales(const vector<Estudiante>& estudiantes) {
    cout << "Reporte de datos generales de estudiantes\n";
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const Estudiante& estudiante = estudiantes[i];
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Carrera: " << estudiante.carrera << endl;
    }
    cout << endl;
}

void ReporteAsignacionCursos(const vector<Estudiante>& estudiantes) {
    cout << "Reporte de asignación de cursos\n";
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const Estudiante& estudiante = estudiantes[i];
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Cursos: ";
        for (size_t j = 0; j < estudiante.cursos.size(); ++j) {
            cout << estudiante.cursos[j] << " ";
        }
        cout << endl;
    } 
}

void ReporteNotas(const vector<Estudiante>& estudiantes) {
    cout << "Reporte de notas\n"; 
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const Estudiante& estudiante = estudiantes[i];
        cout << "Nombre: " << estudiante.nombre << endl; 
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Notas: ";
        for (size_t j = 0; j < estudiante.notas.size(); ++j) {
            cout << estudiante.notas[j] << " ";
        }
        cout << endl;
    }
}

void ReporteRendimientoAcademico(const vector<Estudiante>& estudiantes) {
    cout << "Reporte de rendimiento académico\n"; 
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const Estudiante& estudiante = estudiantes[i];
        double suma = 0;
        int aprobadas = 0, reprobadas = 0;

        for (size_t j = 0; j < estudiante.notas.size(); ++j) {
            suma += estudiante.notas[j];
            if (estudiante.notas[j] >= 60) {
                aprobadas++;
            } else {
                reprobadas++;
            }
        }
        
        double promedio = (estudiante.notas.size() > 0) ? (suma / estudiante.notas.size()) : 0; 
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Promedio: " << fixed << setprecision(2) << promedio << endl;
        cout << "Aprobadas: " << aprobadas << endl;
        cout << "Reprobadas: " << reprobadas << endl;
        cout << endl;
    }
}

int main() {

    return 0;
}
