// GestionarHorario.cpp
#include "GestionarHorario.h"
#include <iostream>
#include <cctype>

GestionarHorario::GestionarHorario()
    : archivoHorarios(sizeof(Horario))
{}

// 1) Cargar datos de un horario (opcionalmente pidiendo idActividad)
Horario GestionarHorario::cargarHorario(int idActividad)
{
    if (idActividad < 0) {
        char resp;
        std::cout << "Desea asignar una actividad a este horario? (S/N): ";
        std::cin >> resp;
        if (std::toupper(resp) == 'S') {
            std::cout << "Ingrese ID de la actividad: ";
            std::cin >> idActividad;
        } else {
            idActividad = 0;
        }
    }

    std::string diaSemana;
    std::cout << "Ingrese dia de la semana (lunes, martes...): ";
    std::cin >> diaSemana;

    int horaInicio, horaFin;
    std::cout << "Ingrese hora inicio (24h, sin minutos): ";
    std::cin >> horaInicio;
    std::cout << "Ingrese hora fin   (24h, sin minutos): ";
    std::cin >> horaFin;

    int idHorario = obtenerIdNuevo();

    return Horario(
        idHorario,
        idActividad,
        diaSemana,
        horaInicio,
        horaFin,
        true
    );
}

// 2) Alta de horario
void GestionarHorario::altaHorarioParaActividad(int idActividad)
{
    Horario nuevo = cargarHorario(idActividad);
    if (archivoHorarios.guardar(nuevo))
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

    int pos = archivoHorarios.buscar(id);
    if (pos >= 0) {
        Horario h = archivoHorarios.leerRegistro(pos);
        h.setEstado(false);
        if (archivoHorarios.modificarRegistro(h, pos))
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
    if (!archivoHorarios.listarRegistro())
        std::cout << "No hay horarios registrados o no se pudo leer el archivo.\n";
}

// 5) Buscar un horario por ID
void GestionarHorario::buscarHorario()
{
    int id;
    std::cout << "Ingrese el ID del horario a buscar: ";
    std::cin >> id;

    int pos = archivoHorarios.buscar(id);
    if (pos >= 0) {
        Horario h = archivoHorarios.leerRegistro(pos);
        h.mostrarHorario();
    } else {
        std::cout << "Horario no encontrado.\n";
    }
}

// 6) Obtener nuevo ID
int GestionarHorario::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<HorarioArchivo, Horario>(archivoHorarios);
}
