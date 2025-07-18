#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "ProfesArchivo.h"
#include "Profe.h"
#include "Validaciones.h"
#include <iomanip>
#include <iostream>
using namespace std;

GestionarActividad::GestionarActividad()
    : archivoActividades(sizeof(Actividad))
{
}

Actividad GestionarActividad::cargarActividad()
{
    int cantMax;
    string nombreActividad, descripcion;
    float costo;

    cout << "Ingrese el nombre de la actividad: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreActividad);

    cout << "Ingrese la cantidad maxima de inscriptos: ";
    cin >> cantMax;

    cout << "Ingrese el costo de la actividad: ";
    cin >> costo;

    if (!Validaciones::esCostoValido(costo)) {
    cout << "ERROR: El costo no puede ser negativo.\n";
    return Actividad(-1, "", 0, 0, "");
}

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese la descripcion de la actividad: ";
    getline(cin, descripcion);

    int idActividad = obtenerIdNuevo();
    Actividad nuevaActividad(idActividad, nombreActividad, cantMax, costo, descripcion);
    return nuevaActividad;
}


void GestionarActividad::listarActividadesSinHorarios()
{
    int totalActividades = archivoActividades.contarRegistros();
    bool seMostroAlguna = false;

    HorarioPorClaseArchivo archivoHorarios(sizeof(Horario));

    for (int i = 0; i < totalActividades; i++)
    {
        Actividad actividad = archivoActividades.leerRegistro(i);

        if (actividad.getEstado())
        {
            bool tieneHorarios = archivoHorarios.tieneHorariosAsignados(actividad.getId());

            if (!tieneHorarios)
            {
                if (!seMostroAlguna)
                {
                    cout << "\n--- Actividades que necesitan Horarios ---\n";
                    seMostroAlguna = true;
                }
                actividad.mostrar();
            }
        }
    }

    if (!seMostroAlguna)
    {
        cout << "\n+------------------------------------------+\n";
        cout << "| (i) Todas las actividades ya tienen      |\n";
        cout << "|     al menos un horario asignado.        |\n";
        cout << "+------------------------------------------+\n";
    }
}

void GestionarActividad::altaActividad()
{
    cout << "--- Creando nueva actividad ---\n";
    Actividad nuevaActividad = cargarActividad();

    if(nuevaActividad.getId() == -1)
    {
        cout << "Operacion cancelada por el usuario.\n";
        return;
    }

    if (archivoActividades.guardar(nuevaActividad))
    {
        cout << "\n>> Actividad '" << nuevaActividad.getNombreActividad() << "' guardada con exito.\n";

        char continuar;

        cout << "\nProceso de alta finalizado.\n";
    }
    else
    {
        cout << "ERROR: No se pudo guardar la actividad principal. Proceso cancelado.\n";
    }
}

void GestionarActividad::bajaActividad()
{
    int id;
    cout << "Ingrese el ID de la actividad a dar de baja: ";
    cin >> id;

    int pos = archivoActividades.buscar(id);
    if (pos >= 0)
    {
        Actividad actividad = archivoActividades.leerRegistro(pos);
        actividad.setEstado(false);

        if (archivoActividades.modificarRegistro(actividad, pos))
        {
            cout << "Actividad dada de baja exitosamente.\n";
        }
        else
        {
            cout << "Error al dar de baja la actividad.\n";
        }
    }
    else
    {
        cout << "Actividad no encontrada.\n";
    }
}


void GestionarActividad::listarActividades() {
    int total = archivoActividades.contarRegistros();
    if (total == 0) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "|   No hay actividades registradas.             |\n"
            << "+-----------------------------------------------+\n\n";
        return;
    }

    bool huboActivas = false;
    for (int i = 0; i < total; ++i) {
        Actividad a = archivoActividades.leerRegistro(i);
        if (!a.getEstado()) continue;

        if (!huboActivas) {
            cout
                << "=== LISTA DE ACTIVIDADES ACTIVAS ===\n\n"
                << "ID | Nombre       | Descripcion           | Costo   | Estado\n"
                << "---------------------------------------------------------------\n";
            huboActivas = true;
        }

        // Ajustar ancho y truncar si es necesario
        string nombre = a.getNombreActividad();
        if (nombre.length() > 12) nombre = nombre.substr(0, 12);
        string desc = a.getDescripcion();
        if (desc.length() > 20) desc = desc.substr(0, 20);

        cout << setw(2)  << a.getId()  << " | "
             << setw(12) << nombre    << " | "
             << setw(20) << desc      << " | "
             << "$" << setw(7)  << fixed << setprecision(2) << a.getCosto() << " | "
             << setw(6)  << "Activa"
             << "\n";
    }

    if (!huboActivas) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "| AVISO: No se encontraron actividades activas.|\n"
            << "+-----------------------------------------------+\n\n";
    } else {
        cout << "\n";
    }
}

void GestionarActividad::buscarActividad()
{
    int id;
    cout << "Ingrese el ID de la actividad a buscar: ";
    cin >> id;

    int pos = archivoActividades.buscar(id);
    if (pos >= 0)
    {
        Actividad actividad = archivoActividades.leerRegistro(pos);
        actividad.mostrar();
    }
    else
    {
        cout << "Actividad no encontrada.\n";
    }
}

int GestionarActividad::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ActividadesArchivo, Actividad>(archivoActividades);
}
