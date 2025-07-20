#include "GestionarProceso.h"
#include "Inscripcion.h"
#include "Fecha.h"
#include <iostream>
#include <limits>
#include <string>
#include "Validaciones.h"

using namespace std;

GestionarProceso::GestionarProceso()
    : _archivoAlumnos(sizeof(Alumno)),
      _archivoClases(sizeof(Clase)),
      _archivoInscripciones(sizeof(Inscripcion)),
      _gestorClase(){}

void GestionarProceso::realizarInscripcion() {
    cout << "\n--- Proceso de Nueva Inscripcion ---" << endl;

    // 1. Validar Alumno
    string dniAlumno;
    int idAlumno = -1;
    int posAlumno = -1;
        do {
            cout << "Ingrese el DNI del Alumno (8 digitos) o 0 para cancelar: ";
            cin >> dniAlumno;

            if (dniAlumno == "0") {
                cout << "Operacion cancelada." << endl;
                return;
            }

            if (!Validaciones::esDNIValido(dniAlumno)) {
                cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
                continue;
            }

            posAlumno = _archivoAlumnos.buscarPosPorDni(dniAlumno);
            if (posAlumno < 0) {
                cout << "Error: No se encontro un alumno con el DNI " << dniAlumno << ".\n";
            }

        } while (!Validaciones::esDNIValido(dniAlumno) || posAlumno < 0);

    idAlumno = _archivoAlumnos.leerRegistro(posAlumno).getId();
    if (posAlumno < 0) {
        cout << "Error: No se encontro un alumno con el DNI " << dniAlumno << "." << endl;
        return;
    }
    idAlumno = _archivoAlumnos.leerRegistro(posAlumno).getId();

    // 2. Seleccionar Clase
    _gestorClase.listarClases();

    int idClase = -1;
    int posClase = -1;

    do {
        idClase = Validaciones::pedirEntero("\nIngrese el ID de la Clase a la que desea inscribir (0 para cancelar): ");

        if (idClase == 0) {
            cout << "Operacion cancelada." << endl;
            return;
        }

        posClase = _archivoClases.buscar(idClase);
        if (posClase < 0) {
            cout << "Error: No se encontro una clase con el ID " << idClase << "." << endl;
        }

} while (idClase != 0 && posClase < 0);

    // 3. Validar si ya está inscripto
    if (_archivoInscripciones.yaEstaInscripto(idAlumno, idClase)) {
        cout << "\nError: El alumno ya se encuentra inscripto en esta clase." << endl;
        return;
    }

    // 4. Crear y guardar la inscripción
    int idInscripcion = Utilidades::obtenerIdNuevo<InscripcionArchivo, Inscripcion>(_archivoInscripciones);
    Fecha fechaActual; // El constructor por defecto usa la fecha actual si lo configuramos, o una fecha default.

    Inscripcion nuevaInscripcion(idInscripcion, idAlumno, idClase, fechaActual, true);

    if (_archivoInscripciones.guardar(nuevaInscripcion)) {
        cout << "\n>> ¡Inscripcion realizada con exito!" << endl;
    } else {
        cout << "\nError: No se pudo guardar la inscripcion en el archivo." << endl;
    }
}


void GestionarProceso::realizarBajaInscripcion() {
    cout << "Esta funcion aun no ha sido implementada." << endl;
}
