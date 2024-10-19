#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <windows.h>

using namespace std;

struct Curso {
    string codigoCurso;
    string nombreCurso;
    int semestre;
    int creditos;
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
    vector<Curso> cursosAsignados;
};

struct Nota {
    string codigoCurso;
    vector<float> notasParciales;
    float notaFinal;
    string estado;
};

vector<Estudiante> estudiantes;
vector<Nota> notas;

void registrarEstudiante();
void asignarCurso();
void registrarNotas();
void mostrarReportes();
void calcularNotaFinal(Nota& nota);
void mostrarMenu();
int calcularEdad(const string& fechaNacimiento);
void clearScreen();
void mostrarBienvenida(const string& titulo);
void cambiarColorFondo(int colorTexto, int colorFondo);
void mostrarTituloPrincipal();

int main() {
    cambiarColorFondo(10, 0);
    clearScreen();
    mostrarTituloPrincipal();
    
    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        
        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cout << "Al parecer acabas de poner un dato no valido para el sistema. "
                 << "Por favor elige un numero de los que hay en la lista para acceder a los diferentes apartados.\n";
            cout << "Seleccione una opcion: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (opcion) {
            case 1:
                cambiarColorFondo(15, 3);
                clearScreen();
                mostrarBienvenida("Registro de Estudiantes");
                registrarEstudiante();
                break;
            case 2:
                cambiarColorFondo(15, 4);
                clearScreen();
                mostrarBienvenida("Asignacion de Cursos");
                asignarCurso();
                break;
            case 3:
                cambiarColorFondo(15, 5);
                clearScreen();
                mostrarBienvenida("Control de Notas");
                registrarNotas();
                break;
            case 4:
                cambiarColorFondo(15, 6);
                clearScreen();
                mostrarBienvenida("Reportes Academicos");
                mostrarReportes();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }

        if (opcion != 5) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            clearScreen();
            mostrarTituloPrincipal();
        }
    } while (opcion != 5);
    return 0;
}

void mostrarTituloPrincipal() {
    cout << "*********************************************\n";
    cout << "      SISTEMA DE REGISTRO UNIVERSITARIO     \n";
    cout << "*********************************************\n";
}

void mostrarMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Registro de Estudiantes\n";
    cout << "2. Asignacion de Cursos\n";
    cout << "3. Control de Notas\n";
    cout << "4. Reportes Academicos\n";
    cout << "5. Salir\n";
}

void clearScreen() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

void mostrarBienvenida(const string& titulo) {
    cout << "\n***** " << titulo << " *****\n";
}

void cambiarColorFondo(int colorTexto, int colorFondo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (colorTexto | (colorFondo << 4)));
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

    cout << "Ingrese nombres: ";
    cin >> nuevoEstudiante.nombres;
    cout << "Ingrese apellidos: ";
    cin >> nuevoEstudiante.apellidos;

    // Lista de carreras
    string carreras[] = {
        "Ingenieria en Sistemas", "Medicina", "Arquitectura", "Derecho"
    };

    cout << "Seleccione su carrera:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << carreras[i] << endl;
    }

    int opcionCarrera;
    cout << "Seleccione su carrera: ";
    while (!(cin >> opcionCarrera) || opcionCarrera < 1 || opcionCarrera > 4) {
        cout << "Opcion invalida, seleccione nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevoEstudiante.carrera = carreras[opcionCarrera - 1];

    string departamentos[] = {
        "Guatemala", "Jalapa", "Chiquimula", "Jutiapa", "Zacapa"
    };

    cout << "Seleccione su direccion (Departamento):\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "6. Si no esta tu departamento, presiona 6 para escribirlo.\n";

    int opcionDepartamento;
    cout << "Seleccione su departamento: ";
    while (!(cin >> opcionDepartamento) || opcionDepartamento < 1 || opcionDepartamento > 6) {
        cout << "Opcion invalida, seleccione nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (opcionDepartamento == 6) {
        cout << "Ingrese el nombre de su departamento: ";
        cin.ignore();
        getline(cin, nuevoEstudiante.direccion);
    } else {
        nuevoEstudiante.direccion = departamentos[opcionDepartamento - 1];
    }

    string municipiosGuatemala[] = {"Ciudad de Guatemala", "Mixco", "Villa Nueva", "Santa Catarina Pinula", "San Miguel Petapa"};
    string municipiosJalapa[] = {"Jalapa", "San Pedro Pinula", "San Luis", "Mataquescuintla", "Monjas"};
    string municipiosChiquimula[] = {"Chiquimula", "Esquipulas", "San José La Arada", "Olopa", "Concepción Las Minas"};
    string municipiosJutiapa[] = {"Jutiapa", "El Progreso", "Jalpatagua", "Moyuta", "Quesada"};
    string municipiosZacapa[] = {"Zacapa", "La Unión", "Estanzuela", "Gualán", "Río Hondo"};

    string* municipiosSeleccionados;
    int numMunicipios;

    switch (opcionDepartamento) {
        case 1: 
            municipiosSeleccionados = municipiosGuatemala;
            numMunicipios = 5;
            break;
        case 2: 
            municipiosSeleccionados = municipiosJalapa;
            numMunicipios = 5;
            break;
        case 3: 
            municipiosSeleccionados = municipiosChiquimula;
            numMunicipios = 5;
            break;
        case 4: 
            municipiosSeleccionados = municipiosJutiapa;
            numMunicipios = 5;
            break;
        case 5: 
            municipiosSeleccionados = municipiosZacapa;
            numMunicipios = 5;
            break;
        default:
            municipiosSeleccionados = NULL;
            numMunicipios = 0;
            break;
    }

    cout << "Seleccione su municipio:\n";
    for (int i = 0; i < numMunicipios; i++) {
        cout << i + 1 << ". " << municipiosSeleccionados[i] << endl;
    }

    int opcionMunicipio;
    cout << "Seleccione su municipio: ";
    while (!(cin >> opcionMunicipio) || opcionMunicipio < 1 || opcionMunicipio > numMunicipios) {
        cout << "Opcion invalida, seleccione nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevoEstudiante.municipio = municipiosSeleccionados[opcionMunicipio - 1];

    cout << "Ingrese aldea (dejar en blanco si no aplica): ";
    cin.ignore();
    getline(cin, nuevoEstudiante.aldea);
    cout << "Ingrese telefono personal: ";
    getline(cin, nuevoEstudiante.telefonoPersonal);
    cout << "Ingrese telefono de casa: ";
    getline(cin, nuevoEstudiante.telefonoCasa);
    cout << "Ingrese telefono de emergencia: ";
    getline(cin, nuevoEstudiante.telefonoEmergencia);
    cout << "Ingrese fecha de nacimiento (dd mm aaaa): ";
    getline(cin, nuevoEstudiante.fechaNacimiento);
    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.fechaNacimiento);
    cout << "Ingrese anio de ingreso: ";
    cin >> nuevoEstudiante.anioIngreso;
    cout << "Ingrese correo electronico: ";
    cin >> nuevoEstudiante.correo;

    estudiantes.push_back(nuevoEstudiante);
    cout << "Estudiante registrado con exito. Codigo: " << nuevoEstudiante.codigo << endl;
}

void asignarCurso() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "Seleccione el codigo del estudiante para asignar curso: ";
    int codigoEstudiante;
    cin >> codigoEstudiante;

    Estudiante* estudianteSeleccionado = NULL;

    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].codigo == codigoEstudiante) {
            estudianteSeleccionado = &estudiantes[i];
            break;
        }
    }

    if (estudianteSeleccionado == NULL) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    Curso nuevoCurso;
    cout << "Ingrese el codigo del curso: ";
    cin >> nuevoCurso.codigoCurso;
    cout << "Ingrese el nombre del curso: ";
    cin.ignore();
    getline(cin, nuevoCurso.nombreCurso);
    cout << "Seleccione el semestre (1-10): ";
    cin >> nuevoCurso.semestre;
    cout << "Ingrese el numero de creditos: ";
    cin >> nuevoCurso.creditos;

    estudianteSeleccionado->cursosAsignados.push_back(nuevoCurso);

    char agregarOtro;
    do {
        cout << "¿Quieres registrar otro curso? (s/n): ";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            Curso nuevoCurso;
            cout << "Ingrese el codigo del curso: ";
            cin >> nuevoCurso.codigoCurso;
            cout << "Ingrese el nombre del curso: ";
            cin.ignore();
            getline(cin, nuevoCurso.nombreCurso);
            cout << "Seleccione el semestre (1-10): ";
            cin >> nuevoCurso.semestre;
            cout << "Ingrese el numero de creditos: ";
            cin >> nuevoCurso.creditos;

            estudianteSeleccionado->cursosAsignados.push_back(nuevoCurso);
        }

    } while (agregarOtro == 's' || agregarOtro == 'S');

    cout << "Cursos asignados con exito al estudiante con codigo: " << estudianteSeleccionado->codigo << endl;
}

void registrarNotas() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "Seleccione el codigo del estudiante para registrar notas: ";
    int codigoEstudiante;
    cin >> codigoEstudiante;

    Estudiante* estudianteSeleccionado = NULL;

    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].codigo == codigoEstudiante) {
            estudianteSeleccionado = &estudiantes[i];
            break;
        }
    }

    if (estudianteSeleccionado == NULL) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    cout << "Cursos asignados al estudiante " << estudianteSeleccionado->nombres << " " << estudianteSeleccionado->apellidos << ":\n";
    for (size_t i = 0; i < estudianteSeleccionado->cursosAsignados.size(); ++i) {
        Curso curso = estudianteSeleccionado->cursosAsignados[i];
        cout << i + 1 << ". " << curso.nombreCurso << " (Codigo: " << curso.codigoCurso << ")\n";
    }

    cout << "Ingrese el codigo del curso para registrar notas: ";
    string codigoCurso;
    cin >> codigoCurso;

    // Verificar si el curso está asignado
    bool cursoEncontrado = false;
    for (size_t i = 0; i < estudianteSeleccionado->cursosAsignados.size(); ++i) {
        Curso curso = estudianteSeleccionado->cursosAsignados[i];
        if (curso.codigoCurso == codigoCurso) {
            cursoEncontrado = true;
            break;
        }
    }

    if (!cursoEncontrado) {
        cout << "Curso no asignado a este estudiante.\n";
        return;
    }

    Nota nuevaNota;
    nuevaNota.codigoCurso = codigoCurso;

    int numNotas;
    cout << "Ingrese el numero de notas parciales: ";
    cin >> numNotas;

    nuevaNota.notasParciales.resize(numNotas);
    for (int i = 0; i < numNotas; i++) {
        cout << "Ingrese la nota parcial " << (i + 1) << ": ";
        cin >> nuevaNota.notasParciales[i];
    }

    calcularNotaFinal(nuevaNota);
    notas.push_back(nuevaNota);
    cout << "Notas registradas con exito para el curso " << codigoCurso << ".\n";
}

void calcularNotaFinal(Nota& nota) {
    float sumaNotas = 0;
    for (size_t i = 0; i < nota.notasParciales.size(); ++i) {
        sumaNotas += nota.notasParciales[i];
    }
    nota.notaFinal = sumaNotas / nota.notasParciales.size();
    nota.estado = (nota.notaFinal >= 60) ? "Aprobado" : "Reprobado";
    cout << "Nota final: " << nota.notaFinal << ", Estado: " << nota.estado << endl;
}

void mostrarReportes() {
    cout << "\n--- Reportes Academicos ---\n";
    
    // Reporte de Datos Generales de los Estudiantes
    cout << "\n--- Reporte de Estudiantes ---\n";
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
    } else {
        for (size_t i = 0; i < estudiantes.size(); i++) {  
            Estudiante estudiante = estudiantes[i];
            cout << "Codigo: " << estudiante.codigo << "\n"
                 << "Nombre: " << estudiante.nombres << " " << estudiante.apellidos << "\n"
                 << "Carrera: " << estudiante.carrera << "\n"
                 << "Edad: " << estudiante.edad << "\n"
                 << "------------------------------------------\n"; // Separador
        }
    }

    // Reporte de Asignacion de Cursos
    cout << "\n--- Reporte de Cursos Asignados ---\n";
    if (estudiantes.empty()) {
        cout << "No hay cursos asignados.\n";
    } else {
        for (size_t i = 0; i < estudiantes.size(); i++) {
            Estudiante estudiante = estudiantes[i];
            for (size_t j = 0; j < estudiante.cursosAsignados.size(); j++) {
                Curso curso = estudiante.cursosAsignados[j];
                cout << "Codigo Estudiante: " << estudiante.codigo << "\n"
                     << "Codigo Curso: " << curso.codigoCurso << "\n"
                     << "Nombre Curso: " << curso.nombreCurso << "\n"
                     << "Semestre: " << curso.semestre << "\n"
                     << "Creditos: " << curso.creditos << "\n"
                     << "------------------------------------------\n"; // Separador
            }
        }
    }

    // Reporte de Notas
    cout << "\n--- Reporte de Notas ---\n";
    if (notas.empty()) {
        cout << "No hay notas registradas.\n";
    } else {
        for (size_t i = 0; i < notas.size(); i++) {  
            Nota nota = notas[i];
            cout << "Codigo Curso: " << nota.codigoCurso << "\n"
                 << "Notas Parciales: ";
            for (size_t j = 0; j < nota.notasParciales.size(); j++) {
                cout << nota.notasParciales[j] << (j < nota.notasParciales.size() - 1 ? ", " : "");
            }
            cout << "\n"
                 << "Nota Final: " << nota.notaFinal << "\n"
                 << "Estado: " << nota.estado << "\n"
                 << "------------------------------------------\n"; // Separador
        }
    }
}

