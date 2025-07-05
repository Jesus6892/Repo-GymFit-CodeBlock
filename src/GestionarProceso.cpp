#include "GestionarProceso.h"
using namespace std;

GestionarProceso::GestionarProceso()
    : archivoAlumnos(sizeof(Alumno)),
      gestorAlumnos(),
      gestorPagos(),
      gestorHorarios() {}

void GestionarProceso::iniciarProceso() {
    system("cls");
    cout << "\n===== PROCESO DE INSCRIPCION =====\n";

    // 1) Verificar o crear alumno
    string dni;
    int idAlumno = -1;
    char respuesta;

    cout << " El alumno ya esta registrado? (S/N): ";
    cin >> respuesta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (toupper(respuesta) == 'S') {
        do {
            cout << "Ingrese DNI del alumno: ";
            cin >> dni;
            idAlumno = archivoAlumnos.buscarPorDni(dni);
            if (idAlumno < 0)
                cout << "Alumno no encontrado.\n";
        } while (idAlumno < 0);
        cout << "Alumno encontrado (ID " << idAlumno << ").\n";
    } else {
        cout << "\n--- Registro de nuevo alumno ---\n";
        gestorAlumnos.altaAlumno();
        cout << "Ingrese DNI del alumno recien registrado: ";
        cin >> dni;
        idAlumno = archivoAlumnos.buscarPorDni(dni);
    }

    // 3) Preguntar a que actividad desea anotarse (Traerse registros de 'Actividad')


    // 4)


    // 2) Registrar pago para la inscripcion
    cout << "\n--- Registro de Pago ---\n";
    Pago pago = gestorPagos.cargarPago(idAlumno);
    if (pago.getId() < 0) {
        cout << "Proceso cancelado en paso de pago.\n";
        system("pause");
        return;
    }

    // 3) Guardar pago sin volver a pedir DNI
    if (gestorPagos.guardarPago(pago))
        cout << "Pago registrado con exito.\n";
    else {
        cout << "ERROR: No se pudo guardar el pago.\n";
        system("pause");
        return;
    }

    cout << "\nProceso de inscripcion completado con exito!\n";
    system("pause");
}
