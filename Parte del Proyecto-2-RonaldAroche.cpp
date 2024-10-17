#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Curso {
    string codigoCurso;
    string nombreCurso;
    string carrera; 
    int semestre;
    int creditos;
};

class SistemaRegistro {
private:
    vector<Curso> cursos; 

public:
    
    void asignarCurso() {
        Curso curso; 

        cout <<"Ingrese el nombre de la carrera: ";
        cin.ignore(); 
        getline(cin, curso.carrera); 

        cout << "Ingrese el codigo del curso: ";
        cin >> curso.codigoCurso;
        cout << "Ingrese el nombre del curso: ";
        cin.ignore(); 
        getline(cin, curso.nombreCurso); 
        cout << "Ingrese el semestre: ";
        cin >> curso.semestre;
        cout << "Ingrese los creditos: ";
        cin >> curso.creditos;

        cursos.push_back(curso);
        cout << "*CURSO ASIGNADO CON EXITO*" << endl;
        cout << "Total de cursos asignados: " << cursos.size() << endl; 
    }

    void mostrarCursos() const {
        if (cursos.empty()) {
            cout << "No hay cursos asignados." << endl;
            return;
        }
        
        cout << "*DATOS DEL CURSO ASIGNADO*:" << endl;
        for (size_t i = 0; i < cursos.size(); ++i) {
            cout << "Carrera: " << cursos[i].carrera
                 << ", Codigo del Curso: " << cursos[i].codigoCurso 
                 << ", Nombre del Curso: " << cursos[i].nombreCurso 
                 << ", Semestre: " << cursos[i].semestre 
                 << ", Creditos: " << cursos[i].creditos << endl;
        }
    }
};

int main() {
    SistemaRegistro sistema; 

    char continuar;
    do {
        sistema.asignarCurso(); 
        sistema.mostrarCursos(); 

        cout << "*DESEA ASIGNAR OTROS CURSOS* (s/n): ";
        cin >> continuar;
        
        while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N') {
            cout << "Opción invalida. Por favor ingrese 's' para si o 'n' para no: ";
            cin >> continuar;
        }

    } while (continuar == 's' || continuar == 'S');

    return 0;
}

