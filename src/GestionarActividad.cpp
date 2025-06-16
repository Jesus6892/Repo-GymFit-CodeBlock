#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "ProfesArchivo.h"
#include "Profe.h"
#include <iostream>
using namespace std;

// Inicializa el archivo con el tama�o de Actividad
GestionarActividad::GestionarActividad()
    : archivoActividades(sizeof(Actividad))
{
}

Actividad GestionarActividad::cargarActividad()
{
    int idProfe = -1, cantMax;
    string nombreActividad, descripcion, dniProfe;
    float costo;

    cout << "Ingrese el nombre de la actividad: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, nombreActividad);

    ProfesArchivo archivoProfes(sizeof(Profe));

    // Bucle de validacion del ID del profesor
    do
    {
        cout << "Ingrese el DNI del profesor (8 digitos) o 0 para cancelar: ";
        cin >> dniProfe;

        if (dniProfe == "0")
        {
            return Actividad();
        }

        idProfe = archivoProfes.buscarIdPorDni(dniProfe);
        if (idProfe == -1)
        {
            cout << "ERROR: No se encontró un profesor activo con el DNI, recuerde crear el profesor con el DNI '"
                 << dniProfe << "'. Intente de nuevo.\n";
        }
    } while (idProfe == -1);

    std::cout << ">> Profesor valido encontrado (ID: " << idProfe << ").\n";

    cout << "Ingrese la cantidad maxima de inscriptos: ";
    cin >> cantMax;

    cout << "Ingrese el costo de la actividad: ";
    cin >> costo;

    cout << "Ingrese la descripcion de la actividad: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, descripcion);

    int idActividad = obtenerIdNuevo();
    Actividad nuevaActividad(idActividad, nombreActividad, idProfe, cantMax, costo, descripcion, true);
    return nuevaActividad;
}

void GestionarActividad::listarActividadesSinHorarios()
{
    int totalActividades = archivoActividades.contarRegistros();
    bool seMostroAlguna = false;

    HorarioArchivo archivoHorarios(sizeof(Horario));

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
                    std::cout << "\n--- Actividades que necesitan Horarios ---\n";
                    seMostroAlguna = true;
                }
                actividad.mostrar();
            }
        }
    }

    if (!seMostroAlguna)
    {
        std::cout << "\n+------------------------------------------+\n";
        std::cout << "| (i) Todas las actividades ya tienen      |\n";
        std::cout << "|     al menos un horario asignado.        |\n";
        std::cout << "+------------------------------------------+\n";
    }
}

void GestionarActividad::altaActividad()
{

    std::cout << "--- Creando nueva actividad ---\n";
    Actividad nuevaActividad = cargarActividad();

    if(nuevaActividad.getId() == -1)
    {
        std::cout << "Operación cancelada por el usuario.\n";
        return;
    }

    if (archivoActividades.guardar(nuevaActividad))
    {
        std::cout << "\n>> Actividad '" << nuevaActividad.getNombreActividad() << "' guardada con exito.\n";

        char continuar;

        do
        {
            std::cout << "\n¿Desea agregar un horario para esta actividad? (S/N): ";
            std::cin >> continuar;

            if (toupper(continuar) == 'S')
            {
                GestionarHorario gestorHorario;
                gestorHorario.altaHorarioParaActividad(nuevaActividad.getId());
            }
        } while (toupper(continuar) == 'S');

        std::cout << "\nProceso de alta finalizado.\n";
    }
    else
    {
        std::cout << "ERROR: No se pudo guardar la actividad principal. Proceso cancelado.\n";
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

void GestionarActividad::listarActividades()
{
    if (!archivoActividades.listarRegistro())
    {
        cout << "No hay actividades registradas o no se pudo leer el archivo.\n";
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
