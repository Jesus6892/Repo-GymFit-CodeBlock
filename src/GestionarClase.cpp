#include "GestionarClase.h"
#include "GestionarActividad.h"
#include "GestionarProfe.h"
#include "GestionarHorario.h"
#include "HorarioPorClaseArchivo.h"
#include "InscripcionArchivo.h"
#include "AlumnosArchivo.h"
#include "Validaciones.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

GestionarClase::GestionarClase()
    : _archivoClases(sizeof(Clase)),
      _archivoActividades(sizeof(Actividad)),
      _archivoProfes(sizeof(Profe))
{}

void GestionarClase::altaClase() {
    cout << "\n--- Alta de Nueva Clase ---" << endl;
    Clase nuevaClase = cargarClase();

    if (nuevaClase.getId() == 0) {
        cout << "Operacion cancelada por el usuario." << endl;
        return;
    }

    if (_archivoClases.guardar(nuevaClase)) {
        cout << "\n>> Clase creada exitosamente (ID: " << nuevaClase.getId() << ")." << endl;

        GestionarHorario gestorHorario;

        int continuar = Validaciones::pedirEntero("\nDesea agregar un horario para esta clase? (1 = SI, 0 = NO): ", 0, 1);

        while (continuar == 1) {
            gestorHorario.altaHorarioParaClase(nuevaClase.getId());

            cout << "\n+----------------------------------------------+\n"
                 << "| Horario agregado exitosamente a la clase.    |\n"
                 << "+----------------------------------------------+\n\n";

            continuar = Validaciones::pedirEntero("Desea agregar otro horario para esta clase? (1 = SI, 0 = NO): ", 0, 1);
        }

        cout << "\nProceso de alta de clase finalizado." << endl;
        system("pause");
    } else {
        cout << "ERROR: No se pudo guardar la clase." << endl;
        system("pause");
    }
}

bool GestionarClase::bajaClase() {
    int idClase;
    int pos;

    do {
        idClase = Validaciones::pedirEntero("Ingrese el ID de la actividad a dar de baja (0 para cancelar): ", 0);

        if (idClase == 0)
        {
            cout << "Operacion cancelada por el usuario.\n";
            system("pause");
            return false;
        }

        pos = _archivoClases.buscar(idClase);

        if (pos < 0)
        {
            cout << "Error: No se encontro ninguna clase con el ID " << idClase << ".\n";
            system("pause");
        }

    } while (pos < 0);

    Clase clase = _archivoClases.leerRegistro(pos);
    clase.setEstado(false);

    if (_archivoClases.modificarRegistro(clase, pos)) {
        cout << "Clase con ID " << idClase << " dada de baja exitosamente.\n";

        HorarioPorClaseArchivo archivoHorarios(sizeof(HorarioPorClase));
        int total = archivoHorarios.contarRegistros();
        int cont = 0;

        for (int i = 0; i < total; ++i) {
            HorarioPorClase h = archivoHorarios.leerRegistro(i);
            if (h.getEstado() && h.getIdClase() == idClase) {
                h.setEstado(false);
                archivoHorarios.modificarRegistro(h, i);
                cont++;
            }
        }

        cout << ">> También se dieron de baja " << cont << " horarios asociados a esta clase.\n";
        return true;

    } else {
        cout << "Error: No se pudo modificar el registro en el archivo.\n";
        system("pause");
        return false;
    }
}

void GestionarClase::listarClases() {
    int totalClases = _archivoClases.contarRegistros();
    if (totalClases == 0) {
        cout << "\nNo hay clases registradas en el sistema.\n";
        return;
    }

    HorarioPorClaseArchivo archivoHorarios;
    bool huboActivas = false;

    cout << "\n--- Listado de Clases Activas ---\n";

    for (int i = 0; i < totalClases; ++i) {
        Clase clase = _archivoClases.leerRegistro(i);
        if (!clase.getEstado()) {
            continue;
        }

        huboActivas = true;

        int posActividad = _archivoActividades.buscar(clase.getIdActividad());
        string nombreActividad = "Desconocida";
        if (posActividad >= 0) {
            nombreActividad = _archivoActividades.leerRegistro(posActividad).getNombreActividad();
        }

        int posProfe = _archivoProfes.buscar(clase.getIdProfe());
        string nombreProfe = "Desconocido";
        if (posProfe >= 0) {
            Profe profe = _archivoProfes.leerRegistro(posProfe);
            nombreProfe = profe.getNombre() + string(" ") + profe.getApellido();
        }

        cout << "\n------------------------------------------------------------\n";
        cout << "Clase ID: " << clase.getId() << endl;
        cout << "  - Actividad: " << nombreActividad << endl;
        cout << "  - Profesor:  " << nombreProfe << endl;
        cout << "  - Horarios:" << endl;

        int totalHorarios = archivoHorarios.contarRegistros();
        bool huboHorarios = false;
        for (int j = 0; j < totalHorarios; ++j) {
            HorarioPorClase hpc = archivoHorarios.leerRegistro(j);
            if (hpc.getIdClase() == clase.getId() && hpc.getEstado()) {
                Horario h = hpc.getHorario();
                cout << "    > " << h.getDiaSemana()
                     << " de " << h.getHoraInicio() << ":00 a "
                     << h.getHoraFin() << ":00 (ID Horario: " << hpc.getId() << ")" << endl;
                huboHorarios = true;
            }
        }

        if (!huboHorarios) {
            cout << "    > Sin horarios asignados." << endl;
        }
    }

    if (!huboActivas) {
        cout << "\nNo se encontraron clases activas.\n";
    }
    cout << "\n------------------------------------------------------------\n";
}

Clase GestionarClase::cargarClase() {
    cout << "\n--- Seleccion de Actividad ---" << endl;
    GestionarActividad gestorActividades;
    gestorActividades.listarActividades();

    int idActividad = -1;
    while (true) {
        idActividad = Validaciones::pedirEntero("Ingrese el ID de la actividad para la clase (0 para cancelar): ", 0);

        if (idActividad == 0) {
            std::cout << "Operacion cancelada por el usuario.\n";
            system("pause");
            return Clase();
        }


        int pos = _archivoActividades.buscar(idActividad);
        if (pos >= 0) {
            Actividad act = _archivoActividades.leerRegistro(pos);
            if (act.getEstado()) {
                break;
            } else {
                cout << "La actividad esta inactiva. Intente con otra." << endl;
                system("pause");
            }
        } else {
            cout << "ID de actividad no valido. Intente de nuevo." << endl;
            system("pause");
        }
    }

    cout << "\n--- Seleccion de Profesor ---" << endl;
    GestionarProfesor gestorProfes;
    gestorProfes.listarProfesores();

    string dniProfe;
    int posProfe = -1;
    while (true) {
        cout << "Ingrese el DNI del profesor para la clase (0 para cancelar): ";
        getline(cin, dniProfe);

        if (dniProfe == "0") return Clase();

        if (!Validaciones::esDNIValido(dniProfe)) {
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
            continue;
        }

        posProfe = _archivoProfes.buscarPosPorDni(dniProfe);
        if (posProfe >= 0) {
            Profe profe = _archivoProfes.leerRegistro(posProfe);
            if (profe.getEstado()) {
                break;
            } else {
                cout << "El profesor esta inactivo. Intente con otro DNI." << endl;
                system("pause");
            }
        } else {
            cout << "DNI de profesor no valido o no encontrado. Intente de nuevo." << endl;
            system("pause");
        }
    }

    int nuevoIdClase = obtenerIdNuevo();
    return Clase(nuevoIdClase, idActividad, _archivoProfes.leerRegistro(posProfe).getId(), true);
}

int GestionarClase::obtenerIdNuevo() {
    return Utilidades::obtenerIdNuevo<ClaseArchivo, Clase>(_archivoClases);
}

void GestionarClase::mostrarEncabezadoListado() const {
    cout << setw(5) << "ID"
         << setw(20) << "Actividad"
         << setw(20) << "Profesor"
         << endl;
    cout << "------------------------------------------------------------" << endl;
}

void GestionarClase::listarAlumnosPorClase() {
    int idClase = Validaciones::pedirEntero("\nIngrese el ID de la clase (0 para cancelar): ", 0);

    if (idClase == 0) {
        std::cout << "Operacion cancelada por el usuario.\n";
        system("pause");
        return;
    }

    int posClase = _archivoClases.buscar(idClase);
    if (posClase < 0) {
        std::cout << "No se encontró una clase con ese ID.\n";
        system("pause");
        return;
    }

    Clase clase = _archivoClases.leerRegistro(posClase);
    if (!clase.getEstado()) {
        std::cout << "La clase está dada de baja.\n";
        system("pause");
        return;
    }

    string nombreActividad = "Desconocida";
    int posAct = _archivoActividades.buscar(clase.getIdActividad());
    if (posAct >= 0) {
        nombreActividad = _archivoActividades.leerRegistro(posAct).getNombreActividad();
    }

    string nombreProfe = "Desconocido";
    int posProfe = _archivoProfes.buscar(clase.getIdProfe());
    if (posProfe >= 0) {
        Profe p = _archivoProfes.leerRegistro(posProfe);
        nombreProfe = p.getNombre() + " " + p.getApellido();
    }

    cout << "\n------------------------------------------------------------\n";
    cout << "Clase ID: " << clase.getId() << endl;
    cout << "Actividad: " << nombreActividad << endl;
    cout << "Profesor: " << nombreProfe << endl;
    cout << "Alumnos:\n";

    InscripcionArchivo archivoInscripciones;
    ArchivoAlumnos archivoAlumnos;
    int totalInsc = archivoInscripciones.contarRegistros();
    bool hayAlumnos = false;

    for (int i = 0; i < totalInsc; ++i) {
        Inscripcion insc = archivoInscripciones.leerRegistro(i);
        if (insc.getEstado() && insc.getIdClase() == idClase) {
            int idAlumno = insc.getIdAlumno();
            int posAlumno = archivoAlumnos.buscar(idAlumno);
            if (posAlumno >= 0) {
                Alumno a = archivoAlumnos.leerRegistro(posAlumno);
                cout << "  - " << a.getNombre() << " " << a.getApellido()
                     << " (DNI: " << a.getDni() << ")" << endl;
                hayAlumnos = true;
            }
        }
    }

    if (!hayAlumnos) {
        cout << "  >> No hay alumnos inscriptos en esta clase.\n";
    }

    cout << "------------------------------------------------------------\n";
}
