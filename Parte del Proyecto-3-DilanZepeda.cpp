#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


struct Curso {
    string codigoCurso;
    string nombreCurso;
    string carrera;
    int semestre;
    int creditos;
    vector<float> notas_parciales; // 
    float nota_final;              // 
    string estado;                 
};

struct Estudiante {
    int codigo;
    string nombres;
    string apellidos;
    string carrera;
    string direccion;
    string municipio;
    string aldea; 
    string telefonoPersonal;
    string telefonoCasa;
    string telefonoEmergencia;
    string fechaNacimiento;
    int edad;
    int anioIngreso;
    string correo;
    vector<Curso> cursosAsignados; // 
};

vector<Estudiante> estudiantes;
vector<Curso> cursos;

void registrarEstudiante();
void asignarCurso();
void mostrarCursos();
void controlNotas(Estudiante& estudiante);
void mostrarReportesAcademicos();
int calcularEdad(const string& fechaNacimiento);
float calcularPromedio(const vector<float>& notas);
string determinarEstado(float nota_final);
void mostrarMenu();
float calcularPromedioGeneral(Estudiante& estudiante);

int main() {
    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarEstudiante(); break;
            case 2: asignarCurso(); break;
            case 3: {
                int codigoEstudiante;
                cout << "Ingrese el código del estudiante: ";
                cin >> codigoEstudiante;
                for (size_t i = 0; i < estudiantes.size(); ++i) {
                    if (estudiantes[i].codigo == codigoEstudiante) {
                        controlNotas(estudiantes[i]);
                        break;
                    }
                }
                break;
            }
            case 4: mostrarReportesAcademicos(); break;
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
    return 0;
}

void mostrarMenu() {
    cout << "\n--- Sistema de Registro Universitario ---\n";
    cout << "1. Registro de Estudiantes\n";
    cout << "2. Asignacion de Cursos\n";
    cout << "3. Control de Notas\n";
    cout << "4. Reportes Academicos\n";
    cout << "5. Salir\n";
}

int calcularEdad(const string& fechaNacimiento) {
    time_t t = time(0);
    tm* now = localtime(&t);
    int anioActual = now->tm_year + 1900;
    int mesActual = now->tm_mon + 1;
    int diaActual = now->tm_mday;

    int diaNacimiento, mesNacimiento, anioNacimiento;
    sscanf(fechaNacimiento.c_str(), "%d %d %d", &diaNacimiento, &mesNacimiento, &anioNacimiento);

    int edad = anioActual - anioNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--;
    }
    return edad;
}

void registrarEstudiante() {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.codigo = estudiantes.size() + 1;

    cin.ignore();
    cout << "Ingrese nombres: ";
    getline(cin, nuevoEstudiante.nombres);

    cout << "Ingrese apellidos: ";
    getline(cin, nuevoEstudiante.apellidos);

    cout << "Ingrese carrera: ";
    getline(cin, nuevoEstudiante.carrera);

    cout << "Ingrese direccion (departamento): ";
    getline(cin, nuevoEstudiante.direccion);

    cout << "Ingrese municipio: ";
    getline(cin, nuevoEstudiante.municipio);

    cout << "Ingrese aldea (dejar en blanco si no aplica): ";
    getline(cin, nuevoEstudiante.aldea);

    cout << "Ingrese telefono personal: ";
    getline(cin, nuevoEstudiante.telefonoPersonal);
    cout << "Ingrese telefono de casa: ";
    getline(cin, nuevoEstudiante.telefonoCasa);
    cout << "Ingrese telefono de emergencia: ";
    getline(cin, nuevoEstudiante.telefonoEmergencia);

    cout << "Ingrese fecha de nacimiento (dd mm aaaa): ";
    getline(cin, nuevoEstudiante.fechaNacimiento);

    cout << "Ingrese anio de ingreso: ";
    cin >> nuevoEstudiante.anioIngreso;

    cout << "Ingrese correo electronico: ";
    cin >> nuevoEstudiante.correo;

    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.fechaNacimiento);
    estudiantes.push_back(nuevoEstudiante);
    cout << "Estudiante registrado con exito. Codigo: " << nuevoEstudiante.codigo << endl;

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void asignarCurso() {
    int codigoEstudiante;
    cout << "Ingrese el código del estudiante: ";
    cin >> codigoEstudiante;

    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].codigo == codigoEstudiante) {
            Curso nuevoCurso;
            cout << "Ingrese el codigo del curso: ";
            cin >> nuevoCurso.codigoCurso;
            cout << "Ingrese el nombre del curso: ";
            cin.ignore();
            getline(cin, nuevoCurso.nombreCurso);
            cout << "Ingrese el semestre: ";
            cin >> nuevoCurso.semestre;
            cout << "Ingrese los creditos: ";
            cin >> nuevoCurso.creditos;

            estudiantes[i].cursosAsignados.push_back(nuevoCurso);
            cout << "*CURSO ASIGNADO CON EXITO*" << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}

float calcularPromedio(const vector<float>& notas) {
    float suma = 0;
    for (size_t i = 0; i < notas.size(); ++i) {
        suma += notas[i];
    }
    return suma / notas.size();
}

string determinarEstado(float nota_final) {
    return (nota_final >= 60) ? "Aprobado" : "Reprobado";
}

void controlNotas(Estudiante& estudiante) {
    for (size_t i = 0; i < estudiante.cursosAsignados.size(); ++i) {
        int numNotas;
        cout << "Ingrese el número de notas parciales para el curso " << estudiante.cursosAsignados[i].nombreCurso << ": ";
        cin >> numNotas;

        for (int j = 0; j < numNotas; ++j) {
            float nota;
            cout << "Nota " << j + 1 << ": ";
            cin >> nota;
            estudiante.cursosAsignados[i].notas_parciales.push_back(nota);
        }

        estudiante.cursosAsignados[i].nota_final = calcularPromedio(estudiante.cursosAsignados[i].notas_parciales);
        estudiante.cursosAsignados[i].estado = determinarEstado(estudiante.cursosAsignados[i].nota_final);

        cout << "Curso: " << estudiante.cursosAsignados[i].nombreCurso << " - Nota Final: " << estudiante.cursosAsignados[i].nota_final << " - Estado: " << estudiante.cursosAsignados[i].estado << endl;
    }
}

float calcularPromedioGeneral(Estudiante& estudiante) {//
    float sumaNotas = 0;
    for (size_t i = 0; i < estudiante.cursosAsignados.size(); ++i) {
        sumaNotas += estudiante.cursosAsignados[i].nota_final;
    }
    return sumaNotas / estudiante.cursosAsignados.size();
}

void mostrarReportesAcademicos() {
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        cout << "Estudiante: " << estudiantes[i].nombres << " " << estudiantes[i].apellidos << endl;
        cout << "Carrera: " << estudiantes[i].carrera << endl;
        cout << "Cursos Asignados:\n";

        for (size_t j = 0; j < estudiantes[i].cursosAsignados.size(); ++j) {
            cout << estudiantes[i].cursosAsignados[j].nombreCurso << " - Nota Final: " << estudiantes[i].cursosAsignados[j].nota_final << " - Estado: " << estudiantes[i].cursosAsignados[j].estado << endl;
        }

        cout << "Promedio General: " << calcularPromedioGeneral(estudiantes[i]) << endl;
    }
}

