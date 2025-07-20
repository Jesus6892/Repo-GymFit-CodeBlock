// GestionarHorario.cpp
#include "GestionarHorario.h"
#include "ClaseArchivo.h"
#include "ActividadesArchivo.h"
#include <iostream>
#include <cctype>
#include <iomanip>
#include <limits>

GestionarHorario::GestionarHorario()
    : archivoHorarioPorClase(sizeof(HorarioPorClase))
{}


HorarioPorClase GestionarHorario::cargarHorario(int idClase)
{
    std::string diaSemana;
    std::cout << "Ingrese dia de la semana (lunes, martes...): ";
    std::cin >> diaSemana;

    int horaInicio, horaFin;
    std::cout << "Ingrese hora inicio (24h, sin minutos): ";
    std::cin >> horaInicio;
    std::cout << "Ingrese hora fin   (24h, sin minutos): ";
    std::cin >> horaFin;

    int idHorario = obtenerIdNuevo();


    return HorarioPorClase(
        idHorario,
        idClase,
        diaSemana,
        horaInicio,
        horaFin
    );
}

// 2) Alta de horario
void GestionarHorario::altaHorarioParaClase(int idClase)
{
    HorarioPorClase nuevo = cargarHorario(idClase);
    if (archivoHorarioPorClase.guardar(nuevo))
        std::cout << ">> Horario guardado correctamente.\n";
    else
        std::cout << "ERROR: No se pudo guardar el horario.\n";
}

// 3) Baja lógica de horario
void GestionarHorario::bajaHorario()
{
    int id;
    std::cout << "Ingrese el ID del horario a dar de baja (0 para cancelar): ";
    std::cin >> id;

    if (id == 0) {
        std::cout << "Operacion cancelada por el usuario.\n";
        return;
    }

    int pos = archivoHorarioPorClase.buscar(id);
    if (pos >= 0) {
        HorarioPorClase h = archivoHorarioPorClase.leerRegistro(pos);
        h.setEstado(false);
        if (archivoHorarioPorClase.modificarRegistro(h, pos))
            std::cout << "Horario dado de baja exitosamente.\n";
        else
            std::cout << "Error al dar de baja el horario.\n";
    } else {
        std::cout << "Horario no encontrado.\n";
    }
}

// 4) Listar todos los horarios
void GestionarHorario::listarHorarios()
{
    int total = archivoHorarioPorClase.contarRegistros();
    if (total == 0) {
        std::cout << "\n+----------------------------------------------+\n";
        std::cout << "|   No hay horarios registrados.               |\n";
        std::cout << "+----------------------------------------------+\n";
        return;
    }

    ClaseArchivo archivoClases(sizeof(Clase));
    ActividadesArchivo archivoActividades(sizeof(Actividad));

    std::cout << "\n=== LISTA DE HORARIOS REGISTRADOS ===\n\n";
    std::cout << "ID | Dia Semana | Hora Inicio | Hora Fin | ID Clase | Nombre Actividad\n";
    std::cout << "--------------------------------------------------------------------------\n";

    bool huboActivos = false;

    for (int i = 0; i < total; ++i) {
        HorarioPorClase h = archivoHorarioPorClase.leerRegistro(i);
        if (!h.getEstado()) continue;

        Horario horario = h.getHorario();
        int idClase = h.getIdClase();

        int posClase = archivoClases.buscar(idClase);
        std::string nombreActividad = "(Desconocida)";
        if (posClase >= 0) {
            Clase clase = archivoClases.leerRegistro(posClase);


            int idActividad = clase.getIdActividad();

            int posActividad = archivoActividades.buscar(idActividad);
            if (posActividad >= 0) {
                Actividad actividad = archivoActividades.leerRegistro(posActividad);
                nombreActividad = actividad.getNombreActividad();
            }
        }

        std::cout << std::left
                  << std::setw(3)  << h.getId() << " | "
                  << std::setw(10) << horario.getDiaSemana() << " | "
                  << std::setw(11) << horario.getHoraInicio() << " | "
                  << std::setw(8)  << horario.getHoraFin() << " | "
                  << std::setw(8)  << idClase << " | "
                  << nombreActividad
                  << "\n";
        huboActivos = true;
    }

    if (!huboActivos) {
        std::cout << "\n+----------------------------------------------+\n";
        std::cout << "| AVISO: No se encontraron horarios activos.  |\n";
        std::cout << "+----------------------------------------------+\n";
    }
    else {
        std::cout << "\n";
    }
}

// 5) Buscar un horario por ID
void GestionarHorario::buscarHorario()
{
    int id;
    int pos;

    do
    {
        std::cout << "Ingrese el ID del horario a buscar (0 para cancelar): ";
        std::cin >> id;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, ingrese un numero.\n";
            pos = -1;
            continue;
        }

        if (id == 0)
        {
            std::cout << "Operacion cancelada por el usuario.\n";
            return;
        }

        pos = archivoHorarioPorClase.buscar(id);

        if (pos < 0)
        {
            std::cout << "No se encontro ningun horario con ese ID. Proba otra vez.\n";
        }

    } while (pos < 0);

    HorarioPorClase h = archivoHorarioPorClase.leerRegistro(pos);

    if (!h.getEstado()) {
        std::cout << "El horario existe pero esta inactivo.\n";
        return;
    }

    // Instanciamos para buscar clase y actividad
    ClaseArchivo archivoClases(sizeof(Clase));
    ActividadesArchivo archivoActividades(sizeof(Actividad));

    int idClase = h.getIdClase();
    std::string nombreActividad = "(Desconocida)";

    int posClase = archivoClases.buscar(idClase);
    if (posClase >= 0) {
        Clase clase = archivoClases.leerRegistro(posClase);
        int idActividad = clase.getIdActividad();

        int posActividad = archivoActividades.buscar(idActividad);
        if (posActividad >= 0) {
            Actividad actividad = archivoActividades.leerRegistro(posActividad);
            nombreActividad = actividad.getNombreActividad();
        }
    }

    Horario horario = h.getHorario();

    std::cout << "\n=== DETALLE DEL HORARIO ENCONTRADO ===\n\n";
    std::cout << "ID | Dia Semana | Hora Inicio | Hora Fin | ID Clase | Nombre Actividad\n";
    std::cout << "--------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(3)  << h.getId() << " | "
              << std::setw(10) << horario.getDiaSemana() << " | "
              << std::setw(11) << horario.getHoraInicio() << " | "
              << std::setw(8)  << horario.getHoraFin() << " | "
              << std::setw(8)  << idClase << " | "
              << nombreActividad
              << "\n\n";
}

// 6) Obtener nuevo ID
int GestionarHorario::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<HorarioPorClaseArchivo, HorarioPorClase>(archivoHorarioPorClase);
}
