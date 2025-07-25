#pragma once
#include "Profe.h"
#include "ProfesArchivo.h"
#include "Utilidades.h"

class GestionarProfesor
{
public:
    GestionarProfesor();
    Profe cargarProfesor();
    void altaProfesor();
    void bajaProfesor();
    void modificarProfesor();
    void listarProfesores();
    void buscarProfesor();

private:
    ProfesArchivo archivoProfesores;
    std::string solicitarDniProfesor();
    int obtenerIdNuevo();
};


