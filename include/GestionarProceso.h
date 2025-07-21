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
#include "ActividadesArchivo.h"
#include "Actividad.h";
#include "ProfesArchivo.h";
#include "Profe.h";


class GestionarProceso {
public:
    GestionarProceso();
    void iniciar();

private:
    void mostrarMenu();
    void realizarInscripcion();
    void realizarBajaInscripcion();
    void listarInscripciones();

    ArchivoAlumnos _archivoAlumnos;
    ClaseArchivo _archivoClases;
    InscripcionArchivo _archivoInscripciones;
    ActividadesArchivo _archivoActividades;
    ProfesArchivo _archivoProfesores;
    GestionarClase _gestorClase;
    GestionarAlumno _gestorAlumno;
};
