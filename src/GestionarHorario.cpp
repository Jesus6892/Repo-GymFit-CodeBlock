// GestionarHorario.cpp
#include "GestionarHorario.h"
#include <iostream>
#include <cctype>

GestionarHorario::GestionarHorario()
    : archivoHorarioPorClase(sizeof(HorarioPorClase))
{}


HorarioPorClase GestionarHorario::cargarHorario(int idActividad)
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
        idActividad,
        diaSemana,
        horaInicio,
        horaFin
    );
}

// 2) Alta de horario
void GestionarHorario::altaHorarioParaActividad(int idActividad)
{
    HorarioPorClase nuevo = cargarHorario(idActividad);
    if (archivoHorarioPorClase.guardar(nuevo))
        std::cout << ">> Horario guardado correctamente.\n";
    else
        std::cout << "ERROR: No se pudo guardar el horario.\n";
}

// 3) Baja lógica de horario
void GestionarHorario::bajaHorario()
{
    int id;
    std::cout << "Ingrese el ID del horario a dar de baja: ";
    std::cin >> id;

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
    if (!archivoHorarioPorClase.listarRegistro())
        std::cout << "No hay horarios registrados o no se pudo leer el archivo.\n";
}

// 5) Buscar un horario por ID
void GestionarHorario::buscarHorario()
{
    int id;
    std::cout << "Ingrese el ID del horario a buscar: ";
    std::cin >> id;

    int pos = archivoHorarioPorClase.buscar(id);
    if (pos >= 0) {
        HorarioPorClase h = archivoHorarioPorClase.leerRegistro(pos);
        h.mostrar();
    } else {
        std::cout << "Horario no encontrado.\n";
    }
}

// 6) Obtener nuevo ID
int GestionarHorario::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<HorarioPorClaseArchivo, HorarioPorClase>(archivoHorarioPorClase);
}
