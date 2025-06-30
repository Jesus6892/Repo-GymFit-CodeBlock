#pragma once
#include "Horario.h"
#include "HorarioPorClase.h"
#include "HorarioPorClaseArchivo.h"
#include "Utilidades.h"

class GestionarHorario
{
public:
    GestionarHorario();
    //Horario cargarHorario();
    void bajaHorario();
    void listarHorarios();
    void buscarHorario();
    HorarioPorClase cargarHorario(int idActividad = -1);
    void altaHorarioParaActividad(int idActividad);

private:
    HorarioPorClaseArchivo archivoHorarioPorClase;
    int obtenerIdNuevo();
};
