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
        cout << "Inscripci�n agregada exitosamente.\n";
    }
    else {
        cout << "Error al guardar la inscripci�n.\n";
    }
}

void GestionarInscripciones::bajaInscripcion() {
    int idHorario, idAlumno;
    cout << "Ingrese el ID del horario de la inscripci�n a dar de baja: ";
    cin >> idHorario;
    cout << "Ingrese el ID del alumno de la inscripci�n a dar de baja: ";
    cin >> idAlumno;

    int pos = archivoInscripciones.buscar(idHorario, idAlumno);
    if (pos >= 0) {
        Inscripciones inscripcion = archivoInscripciones.leerRegistro(pos);


        if (archivoInscripciones.eliminarRegistro(pos)) {
            cout << "Inscripci�n dada de baja exitosamente.\n";
        }
        else {
            cout << "Error al dar de baja la inscripci�n.\n";
        }
    }
    else {
        cout << "Inscripci�n no encontrada.\n";
    }

}

void GestionarInscripciones::listarInscripciones() {
    if (!archivoInscripciones.listarRegistro()) {
        cout << "No hay inscripciones registradas o no se pudo leer el archivo.\n";
    }
}

void GestionarInscripciones::buscarInscripcion() {
    int idHorario, idAlumno;
    cout << "Ingrese el ID del horario de la inscripci�n a buscar: ";
    cin >> idHorario;
    cout << "Ingrese el ID del alumno de la inscripci�n a buscar: ";
    cin >> idAlumno;


    int pos = archivoInscripciones.buscar(idHorario, idAlumno);
    if (pos >= 0) {
        Inscripciones inscripcion = archivoInscripciones.leerRegistro(pos);
        inscripcion.mostrar();
    }
    else {
        cout << "Inscripci�n no encontrada.\n";
    }

}
