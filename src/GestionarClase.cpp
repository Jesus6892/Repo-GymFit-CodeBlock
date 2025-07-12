#include "GestionarClase.h"
#include "GestionarActividad.h"
#include "GestionarProfe.h"
#include "GestionarHorario.h"
#include "HorarioPorClaseArchivo.h"
#include <iostream>
#include <iomanip>

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

        char continuar;

        cout << "\nDesea agregar un horario para esta clase? (S/N): ";
        cin >> continuar;

        if (toupper(continuar) == 'S') {
            GestionarHorario gestorHorario;
            gestorHorario.altaHorarioParaClase(nuevaClase.getId());

            do {
                cout << "\n+----------------------------------------------+\n"
                     << "| Horario agregado exitosamente a la clase.    |\n"
                     << "+----------------------------------------------+\n\n";
                cout << "¿Desea agregar otro horario para esta clase? (S/N): ";
                cin >> continuar;

                if (toupper(continuar) == 'S') {
                    gestorHorario.altaHorarioParaClase(nuevaClase.getId());
                }

            } while (toupper(continuar) == 'S');
        }

        cout << "\nProceso de alta de clase finalizado." << endl;
    } else {
        cout << "ERROR: No se pudo guardar la clase." << endl;
    }
}

void GestionarClase::bajaClase(int idClase) {
    int pos = _archivoClases.buscar(idClase);

    if (pos >= 0) {
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

            cout << ">> También se dieron de baja " << cont << " horario(s) asociados a esta clase.\n";

        } else {
            cout << "Error: No se pudo modificar el registro en el archivo.\n";
        }
    } else {
        cout << "Error: No se encontro ninguna clase con el ID " << idClase << ".\n";
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
        cout << "Ingrese el ID de la actividad para la clase (0 para cancelar): ";
        cin >> idActividad;
        if (idActividad == 0) return Clase();

        int pos = _archivoActividades.buscar(idActividad);
        if (pos >= 0) {
            Actividad act = _archivoActividades.leerRegistro(pos);
            if (act.getEstado()) {
                break;
            }
        }
        cout << "ID de actividad no valido o inactivo. Intente de nuevo." << endl;
    }

    cout << "\n--- Seleccion de Profesor ---" << endl;
    GestionarProfesor gestorProfes;
    gestorProfes.listarProfesores();

    int idProfe = -1;
    string dniProfe;
    while (true) {
        cout << "Ingrese el DNI del profesor para la clase (0 para cancelar): ";
        cin >> dniProfe;
        if (dniProfe == "0") return Clase();

        int pos = _archivoProfes.buscarPosPorDni(dniProfe);
        if (pos >= 0) {
            Profe profe = _archivoProfes.leerRegistro(pos);
            if (profe.getEstado()) {
                idProfe = profe.getId();
                break;
            }
        }
        cout << "DNI de profesor no valido o inactivo. Intente de nuevo." << endl;
    }

    int nuevoIdClase = obtenerIdNuevo();
    return Clase(nuevoIdClase, idActividad, idProfe, true);
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
