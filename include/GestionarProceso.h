// GestionarProceso.h
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include "AlumnosArchivo.h"
#include "GestionarAlumno.h"
#include "GestionarPago.h"
#include "GestionarHorario.h"

class GestionarProceso {
private:
    ArchivoAlumnos archivoAlumnos;
    GestionarAlumno gestorAlumnos;
    GestionarPago gestorPagos;
    GestionarHorario gestorHorarios;

public:
    GestionarProceso();
    void iniciarProceso();
};