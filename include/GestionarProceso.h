// GestionarProceso.h
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include "AlumnosArchivo.h"
#include "ClaseArchivo.h"
#include "InscripcionArchivo.h"
#include "GestionarClase.h"
#include "GestionarAlumno.h"


class GestionarProceso {
public:
    GestionarProceso();
    void iniciar();

private:
    void mostrarMenu();
    void realizarInscripcion();
    void realizarBajaInscripcion();

    ArchivoAlumnos _archivoAlumnos;
    ClaseArchivo _archivoClases;
    InscripcionArchivo _archivoInscripciones;
    GestionarClase _gestorClase;
    GestionarAlumno _gestorAlumno; 
};
