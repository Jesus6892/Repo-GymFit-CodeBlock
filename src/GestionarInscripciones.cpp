#include "GestionarInscripciones.h"
#include <iostream>
using namespace std;

GestionarInscripciones::GestionarInscripciones()
    : archivoInscripciones(sizeof(Inscripciones))
{}

Inscripciones GestionarInscripciones::cargarInscripcion() {
    int idHorario, idAlumno;

    cout << "Ingrese el ID del horario: ";
    cin >> idHorario;

    cout << "Ingrese el ID del alumno: ";
    cin >> idAlumno;

    Inscripciones nuevaInscripcion(idHorario, idAlumno);
    return nuevaInscripcion;
}

void GestionarInscripciones::altaInscripcion() {
    Inscripciones nuevaInscripcion = cargarInscripcion();

    if (archivoInscripciones.guardar(nuevaInscripcion)) {
        cout << "Inscripción agregada exitosamente.\n";
    }
    else {
        cout << "Error al guardar la inscripción.\n";
    }
}

void GestionarInscripciones::bajaInscripcion() {
    int idHorario, idAlumno;
    cout << "Ingrese el ID del horario de la inscripción a dar de baja: ";
    cin >> idHorario;
    cout << "Ingrese el ID del alumno de la inscripción a dar de baja: ";
    cin >> idAlumno;

    int pos = archivoInscripciones.buscar(idHorario, idAlumno);
    if (pos >= 0) {
        Inscripciones inscripcion = archivoInscripciones.leerRegistro(pos);


        if (archivoInscripciones.eliminarRegistro(pos)) {
            cout << "Inscripción dada de baja exitosamente.\n";
        }
        else {
            cout << "Error al dar de baja la inscripción.\n";
        }
    }
    else {
        cout << "Inscripción no encontrada.\n";
    }

}

void GestionarInscripciones::listarInscripciones() {
    if (!archivoInscripciones.listarRegistro()) {
        cout << "No hay inscripciones registradas o no se pudo leer el archivo.\n";
    }
}

void GestionarInscripciones::buscarInscripcion() {
    int idHorario, idAlumno;
    cout << "Ingrese el ID del horario de la inscripción a buscar: ";
    cin >> idHorario;
    cout << "Ingrese el ID del alumno de la inscripción a buscar: ";
    cin >> idAlumno;


    int pos = archivoInscripciones.buscar(idHorario, idAlumno);
    if (pos >= 0) {
        Inscripciones inscripcion = archivoInscripciones.leerRegistro(pos);
        inscripcion.mostrar();
    }
    else {
        cout << "Inscripción no encontrada.\n";
    }

}
