#pragma once
#include "Actividad.h"
#include "ActividadesArchivo.h" // Clase de archivo que maneja la persistencia de Actividad
#include "Utilidades.h"

class GestionarActividad
{
public:
    GestionarActividad();

    Actividad cargarActividad();
    void altaActividad();
    void bajaActividad();
    void listarActividades();
    void buscarActividad();
    void listarActividadesSinHorarios();
    void modificarActividad();

private:
    ActividadesArchivo archivoActividades;
    int obtenerIdNuevo();
};
