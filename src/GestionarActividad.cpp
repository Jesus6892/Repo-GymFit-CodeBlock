#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "ProfesArchivo.h"
#include "Profe.h"
#include <iomanip>
#include <iostream>
using namespace std;

// Inicializa el archivo con el tamano de Actividad
GestionarActividad::GestionarActividad()
    : archivoActividades(sizeof(Actividad))
{
}

Actividad GestionarActividad::cargarActividad()
{
    int idProfe = 0, cantMax;
    string nombreActividad, descripcion, dniProfe;
    float costo;
    char asignar;

    cout << "Ingrese el nombre de la actividad: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreActividad);

    cout << "Desea asignar un profesor a esta actividad? (S/N): ";
    cin >> asignar;

    if (toupper(asignar) == 'S') {
        ProfesArchivo archivoProfes(sizeof(Profe));
        // Bucle de validacion del DNI del profesor
        do {
            cout << "Ingrese el DNI del profesor (8 digitos) o 0 para cancelar: ";
            cin >> dniProfe;
            if (dniProfe == "0") {
                return Actividad();  // cancelacion completa
            }
            idProfe = archivoProfes.buscarIdPorDni(dniProfe);
            if (idProfe <= 0) {
                cout << "ERROR: No se encontro un profesor activo con DNI "
                     << dniProfe << ". Intente de nuevo.\n";
            }
        } while (idProfe <= 0);

        cout << ">> Profesor valido encontrado (ID: " << idProfe << ").\n";
    }
    else {
        cout << ">> No se asignara profesor a esta actividad.\n";
    }

    cout << "Ingrese la cantidad maxima de inscriptos: ";
    cin >> cantMax;

    cout << "Ingrese el costo de la actividad: ";
    cin >> costo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese la descripcion de la actividad: ";
    getline(cin, descripcion);

    int idActividad = obtenerIdNuevo();
    // idProfe = 0 significa "sin asignar"
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

        do
        {
            cout << "\nDesea agregar un horario para esta actividad? (S/N): ";
            cin >> continuar;

            if (toupper(continuar) == 'S')
            {
                GestionarHorario gestorHorario;
                gestorHorario.altaHorarioParaActividad(nuevaActividad.getId());
            }
        } while (toupper(continuar) == 'S');

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
                << "ID | Nombre       | Descripcion           | Estado\n"
                << "--------------------------------------------------------\n";
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
