#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "ProfesArchivo.h"
#include "Profe.h"
#include "Validaciones.h"
#include <iomanip>
#include <iostream>
#include <limits>

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

    // nombre
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        cout << "Ingrese el nombre de la actividad: ";
        getline(cin, nombreActividad);
        if (!Validaciones::esSoloLetras(nombreActividad))
            std::cout << "Nombre de la actividad invalido. Solo letras y espacios.\n";
    }while (!Validaciones::esSoloLetras(nombreActividad));

    // Inscriptos
    cantMax = Validaciones::pedirEntero("Ingrese la cantidad maxima de inscriptos: ", 1);

    // Costo
    do {
        costo = Validaciones::pedirFlotante("Ingrese el costo de la actividad: ");

        if (!Validaciones::esCostoValido(costo)) {
            cout << "ERROR: El costo no puede ser negativo.\n";
        } else {
            break;
        }
    } while (true);

    // Descripcion
    do {
        cout << "Ingrese la descripcion de la actividad: ";
        getline(cin, descripcion);

        if (!Validaciones::esObservacionValida(descripcion)) {
            cout << "Descripcion invalida. Debe contener al menos una letra.\n";
        }
    } while (!Validaciones::esObservacionValida(descripcion));

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
        system("pause");
        return;
    }

    if (archivoActividades.guardar(nuevaActividad))
    {
        cout << "\n>> Actividad '" << nuevaActividad.getNombreActividad() << "' guardada con exito.\n";

        char continuar;

        cout << "\nProceso de alta finalizado.\n";
        system("pause");
    }
    else
    {
        cout << "ERROR: No se pudo guardar la actividad principal. Proceso cancelado.\n";
        system("pause");
    }
}

void GestionarActividad::bajaActividad()
{
    int id;
    int pos;

    do
    {
        id = Validaciones::pedirEntero("Ingrese el ID de la actividad a dar de baja (0 para cancelar): ");

        if (id == 0)
        {
            cout << "Operacion cancelada por el usuario.\n";
            system("pause");
            return;
        }

        pos = archivoActividades.buscar(id);

        if (pos < 0)
        {
            cout << "No se encontro ninguna actividad con ese ID. Proba otra vez.\n";
        }

    } while (pos < 0);

    Actividad actividad = archivoActividades.leerRegistro(pos);
    actividad.setEstado(false);

    if (archivoActividades.modificarRegistro(actividad, pos))
    {
        cout << "Actividad dada de baja exitosamente.\n";
        system("pause");
    }
    else
    {
        cout << "Error al dar de baja la actividad.\n";
        system("pause");
    }
}

void GestionarActividad::modificarActividad() {
    int id;
    int pos;

    do {
        id = Validaciones::pedirEntero("Ingrese el ID de la actividad a modificar (0 para cancelar): ", 0);

        if (id == 0) {
            std::cout << "Operacion cancelada por el usuario.\n";
            system("pause");
            return;
        }

        pos = archivoActividades.buscar(id);

        if (pos < 0) {
            std::cout << "No se encontro ninguna actividad con ese ID. Proba otra vez.\n";
            system("pause");
        }
    } while (pos < 0);

    Actividad actividad = archivoActividades.leerRegistro(pos);

    std::cout << "Datos actuales de la actividad:\n";
    actividad.mostrar();

    std::string nuevoValor;
    float nuevoPrecio;

    int opcion = Validaciones::pedirEntero(
        "\nQue campo desea modificar?\n"
        "1. Nombre\n"
        "2. Descripcion\n"
        "3. Costo\n"
        "0. Cancelar\n"
        "Seleccione una opcion: ", 0, 3);

    switch (opcion) {
    case 1:
        do {
            std::cout << "Ingrese el nuevo nombre: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esSoloLetras(nuevoValor))
                std::cout << "Nombre de la actividad invalido. Solo letras y espacios.\n";
        } while (!Validaciones::esSoloLetras(nuevoValor));
        actividad.setNombreActividad(nuevoValor);
        break;

    case 2:
        do {
            std::cout << "Ingrese la descripcion: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esObservacionValida(nuevoValor))
                std::cout << "Descripcion invalida. Debe contener al menos una letra.\n";
        } while (!Validaciones::esObservacionValida(nuevoValor));
        actividad.setDescripcion(nuevoValor);
        break;

    case 3:
        do {
            nuevoPrecio = Validaciones::pedirFlotante("Ingrese el nuevo costo de la actividad: ");
            if (!Validaciones::esCostoValido(nuevoPrecio))
                std::cout << "ERROR: El costo no puede ser negativo.\n";
        } while (!Validaciones::esCostoValido(nuevoPrecio));
        actividad.setCosto(nuevoPrecio);
        break;

    case 0:
        std::cout << "Modificacion cancelada.\n";
        system("pause");
        return;

    default:
        std::cout << "Opcion no valida.\n";
        system("pause");
        return;
    }

    if (archivoActividades.modificarRegistro(actividad, pos)) {
        std::cout << "Actividad modificada exitosamente.\n";
        system("pause");
    } else {
        std::cout << "Error al modificar la actividad.\n";
        system("pause");
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
    int pos;

    do
    {
         id = Validaciones::pedirEntero("Ingrese el ID de la actividad a modificar (0 para cancelar): ", 0);

        if (id == 0) {
            std::cout << "Operacion cancelada por el usuario.\n";
            system("pause");
            return;
        }

        pos = archivoActividades.buscar(id);

        if (pos < 0) {
            std::cout << "No se encontro ninguna actividad con ese ID. Proba otra vez.\n";
            system("pause");
        }
    } while (pos < 0);

    Actividad actividad = archivoActividades.leerRegistro(pos);
    actividad.mostrar();
    system("pause");
}

int GestionarActividad::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ActividadesArchivo, Actividad>(archivoActividades);
}
