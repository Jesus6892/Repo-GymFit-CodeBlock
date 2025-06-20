#pragma once
#include "Horario.h" 
#include "HorarioArchivo.h" 
#include "Utilidades.h"

class GestionarHorario
{
public:
    GestionarHorario();
    //Horario cargarHorario();
    void bajaHorario();
    void listarHorarios();
    void buscarHorario();
    Horario cargarHorario(int idActividad);
    void altaHorarioParaActividad(int idActividad);

private:
    HorarioArchivo archivoHorarios;
    int obtenerIdNuevo();
};
