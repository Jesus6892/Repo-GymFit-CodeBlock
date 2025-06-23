#include "GestionarHorario.h"
#include "Horario.h"
#include <iostream>
using namespace std;

GestionarHorario::GestionarHorario()
    : archivoHorarios(sizeof(Horario))
{
}

Horario GestionarHorario::cargarHorario(int idActividad)
{
    if (idActividad < 0)
    {
        char resp;
        cout << "Desea asignar una actividad a este horario? (S/N): ";
        cin >> resp;
        if (toupper(resp) == 'S')
        {
            cout << "Ingrese ID de la actividad: ";
            cin >> idActividad;
        }
        else
        {
            idActividad = 0; 
        }
    }

    // 1) Día de la semana
    string diaSemana;
    cout << "Ingrese dia de la semana (lunes, martes...): ";
    cin >> diaSemana;

    // 2) Hora inicio y fin
    int horaInicio, horaFin;
    cout << "Ingrese hora inicio (24h, sin minutos): ";
    cin >> horaInicio;
    cout << "Ingrese hora fin   (24h, sin minutos): ";
    cin >> horaFin;

    // 3) Genero nuevo ID
    int idHorario = obtenerIdNuevo();

    // 4) Construyo y devuelvo
    return Horario(idHorario,
                   idActividad,
                   diaSemana,
                   horaInicio,
                   horaFin,
                   true);
}

void GestionarHorario::altaHorarioParaActividad(int idActividad)
{
    Horario nuevoHorario = cargarHorario(idActividad);

    if (archivoHorarios.guardar(nuevoHorario))
    {
        std::cout << ">> Horario guardado correctamente.\n";
    }
    else
    {
        std::cout << "ERROR: No se pudo guardar el horario.\n";
    }
}

bool HorarioArchivo::tieneHorariosAsignados(int idActividad) const
{
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == nullptr)
    {
        return false;
    }

    Horario reg;
    while (fread(&reg, _tamReg, 1, p) == 1)
    {
        if (reg.getIdActividad() == idActividad && reg.getEstado())
        {
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}

void GestionarHorario::bajaHorario()
{
    int id;
    cout << "Ingrese el ID del horario a dar de baja: ";
    cin >> id;

    int pos = archivoHorarios.buscar(id);
    if (pos >= 0)
    {
        Horario horario = archivoHorarios.leerRegistro(pos);
        horario.setEstado(false);

        if (archivoHorarios.modificarRegistro(horario, pos))
        {
            cout << "Horario dado de baja exitosamente.\n";
        }
        else
        {
            cout << "Error al dar de baja el horario.\n";
        }
    }
    else
    {
        cout << "Horario no encontrado.\n";
    }
}

void GestionarHorario::listarHorarios()
{
    if (!archivoHorarios.listarRegistro())
    {
        cout << "No hay horarios registrados o no se pudo leer el archivo.\n";
    }
}

void GestionarHorario::buscarHorario()
{
    int id;
    cout << "Ingrese el ID del horario a buscar: ";
    cin >> id;

    int pos = archivoHorarios.buscar(id);
    if (pos >= 0)
    {
        Horario horario = archivoHorarios.leerRegistro(pos);
        horario.mostrarHorario();
    }
    else
    {
        cout << "Horario no encontrado.\n";
    }
}

int GestionarHorario::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<HorarioArchivo, Horario>(archivoHorarios);
}
