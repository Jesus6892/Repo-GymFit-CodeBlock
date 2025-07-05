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

    // Si cargarClase devolvió un objeto por defecto (ID 0), el usuario canceló.
    if (nuevaClase.getId() == 0) {
        cout << "Operacion cancelada por el usuario." << endl;
        return;
    }

    if (_archivoClases.guardar(nuevaClase)) {
        cout << "\n>> Clase creada exitosamente (ID: " << nuevaClase.getId() << ")." << endl;

        char continuar;
        do {
            cout << "\nDesea agregar un horario para esta clase? (S/N): ";
            cin >> continuar;

            if (toupper(continuar) == 'S') {
                GestionarHorario gestorHorario;
                gestorHorario.altaHorarioParaClase(nuevaClase.getId());
            }
        } while (toupper(continuar) == 'S');

        cout << "\nProceso de alta de clase finalizado." << endl;
    } else {
        cout << "ERROR: No se pudo guardar la clase." << endl;
    }
}

void GestionarClase::bajaClase() {
    cout << "Funcion para dar de baja una clase existente." << endl;
    // Lógica para buscar clase por ID y cambiar su estado a inactivo.
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

        // Obtener nombre de la actividad
        int posActividad = _archivoActividades.buscar(clase.getIdActividad());
        string nombreActividad = "Desconocida";
        if (posActividad >= 0) {
            nombreActividad = _archivoActividades.leerRegistro(posActividad).getNombreActividad();
        }

        // Obtener nombre del profesor
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

        // Listar horarios para esta clase
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
    // 1. Seleccionar Actividad
    cout << "\n--- Seleccion de Actividad ---" << endl;
    GestionarActividad gestorActividades; // Usamos el gestor para listar
    gestorActividades.listarActividades();

    int idActividad = -1;
    while (true) {
        cout << "Ingrese el ID de la actividad para la clase (0 para cancelar): ";
        cin >> idActividad;
        if (idActividad == 0) return Clase(); // Devuelve clase vacía para cancelar

        int pos = _archivoActividades.buscar(idActividad);
        if (pos >= 0) {
            Actividad act = _archivoActividades.leerRegistro(pos);
            if (act.getEstado()) {
                break; // Actividad válida y activa
            }
        }
        cout << "ID de actividad no valido o inactivo. Intente de nuevo." << endl;
    }

    // 2. Seleccionar Profesor
    cout << "\n--- Seleccion de Profesor ---" << endl;
    GestionarProfesor gestorProfes; // Usamos el gestor para listar
    gestorProfes.listarProfesores();

    int idProfe = -1;
    string dniProfe;
    while (true) {
        cout << "Ingrese el DNI del profesor para la clase (0 para cancelar): ";
        cin >> dniProfe;
        if (dniProfe == "0") return Clase(); // Devuelve clase vacía para cancelar

        int pos = _archivoProfes.buscarPosPorDni(dniProfe);
        if (pos >= 0) {
            Profe profe = _archivoProfes.leerRegistro(pos);
            if (profe.getEstado()) {
                idProfe = profe.getId();
                break; // Profesor válido y activo
            }
        }
        cout << "DNI de profesor no valido o inactivo. Intente de nuevo." << endl;
    }

    // 3. Crear y devolver la clase con los IDs seleccionados
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