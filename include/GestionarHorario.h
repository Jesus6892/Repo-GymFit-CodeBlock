#pragma once
#include "Horario.h"
#include "HorarioPorClase.h"
#include "HorarioPorClaseArchivo.h"
#include "Utilidades.h"

class GestionarHorario
{
public:
    GestionarHorario();
    void bajaHorario();
    void listarHorarios();
    void buscarHorario();
    HorarioPorClase cargarHorario(int idClase);
    void altaHorarioParaClase(int idClase);

private:
    HorarioPorClaseArchivo archivoHorarioPorClase;
    int obtenerIdNuevo();
};
