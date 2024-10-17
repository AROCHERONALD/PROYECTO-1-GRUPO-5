#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Estudiante {
    int codigo;
    string nombres;
    string apellidos;
    string carrera;
    string direccion; 
    string municipio;
    string aldea; // opcional
    string telefonoPersonal;
    string telefonoCasa;
    string telefonoEmergencia;
    string fechaNacimiento;
    int edad;
    int anioIngreso;
    string correo;
};

vector<Estudiante> estudiantes;

void registrarEstudiante();
void mostrarMenu();

int main() {
    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarEstudiante(); break;
            case 2: cout << "Funcionalidad de asignacion de cursos aun no implementada.\n"; break;
            case 3: cout << "Funcionalidad de control de notas aun no implementada.\n"; break;
            case 4: cout << "Funcionalidad de reportes academicos aun no implementada.\n"; break;
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
    // Obtener la fecha actual
    time_t t = time(0);
    tm* now = localtime(&t);
    int anioActual = now->tm_year + 1900; // tm_year es el año desde 1900
    int mesActual = now->tm_mon + 1; // tm_mon va de 0 a 11
    int diaActual = now->tm_mday; // Día del mes

    // Extraer la fecha de nacimiento
    int diaNacimiento, mesNacimiento, anioNacimiento;
    sscanf(fechaNacimiento.c_str(), "%d %d %d", &diaNacimiento, &mesNacimiento, &anioNacimiento);

    // Calcular la edad
    int edad = anioActual - anioNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--; // Aún no ha cumplido años este año
    }
    return edad;
}

void registrarEstudiante() {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.codigo = estudiantes.size() + 1; // Código automático

    cin.ignore();  // Asegúrate de ignorar el salto de línea anterior
    cout << "Ingrese nombres: ";
    getline(cin, nuevoEstudiante.nombres);
    
    cout << "Ingrese apellidos: ";
    getline(cin, nuevoEstudiante.apellidos);
    
    cout << "Ingrese carrera: ";
    getline(cin, nuevoEstudiante.carrera); // Permitir espacios en la carrera

    // Selección de dirección (departamento)
    string departamentos[] = {"Guatemala", "Jutiapa", "Santa Ana", "Chiquimula", "Zacapa"};
    cout << "Seleccione su direccion (Departamento):\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "6. Si no esta tu departamento de origen, elige 6 para escribirlo: ";
    int opcionDepartamento;
    cin >> opcionDepartamento;

    if (opcionDepartamento >= 1 && opcionDepartamento <= 5) {
        nuevoEstudiante.direccion = departamentos[opcionDepartamento - 1];
    } else {
        cout << "Escriba su departamento: ";
        cin.ignore();  // Ignorar salto de línea
        getline(cin, nuevoEstudiante.direccion);
    }

    // Selección de municipio
    cout << "Ingrese municipio: ";
    cin.ignore();  // Ignorar salto de línea
    getline(cin, nuevoEstudiante.municipio);  // Usar getline

    // Aldea (opcional)
    cout << "Ingrese aldea (dejar en blanco si no aplica): ";
    getline(cin, nuevoEstudiante.aldea);

    // Teléfonos
    cout << "Ingrese telefono personal: ";
    getline(cin, nuevoEstudiante.telefonoPersonal);
    cout << "Ingrese telefono de casa: ";
    getline(cin, nuevoEstudiante.telefonoCasa);
    cout << "Ingrese telefono de emergencia: ";
    getline(cin, nuevoEstudiante.telefonoEmergencia);

    // Fecha de nacimiento
    cout << "Ingrese fecha de nacimiento (dd mm aaaa): ";
    getline(cin, nuevoEstudiante.fechaNacimiento);

    // Año de ingreso
    cout << "Ingrese anio de ingreso: ";
    cin >> nuevoEstudiante.anioIngreso;
    
    // Correo electrónico
    cout << "Ingrese correo electronico: ";
    cin >> nuevoEstudiante.correo;

    // Calcular edad
    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.fechaNacimiento);

    estudiantes.push_back(nuevoEstudiante);
    cout << "Estudiante registrado con exito. Codigo: " << nuevoEstudiante.codigo << endl;

    // Pausar antes de volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore();  // Ignorar salto de línea anterior
    cin.get();     // Esperar a que el usuario presione Enter
}

