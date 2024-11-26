#pragma once
#include "Inscripciones.h"
#include "InscripcionesArchivo.h"
#include "Utilidades.h"

class GestionarInscripciones
{
public:
    GestionarInscripciones();
    Inscripciones cargarInscripcion();
    void altaInscripcion();
    void bajaInscripcion();
    void listarInscripciones();
    void buscarInscripcion();

private:
    InscripcionesArchivo archivoInscripciones;
    int obtenerIdNuevo();
};
