// GestionarProceso.h
#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "Alumno.h"
#include "GestionarAlumno.h"
#include "AlumnosArchivo.h"
#include "Clase.h"
#include "GestionarClase.h"
#include "ClaseArchivo.h"
#include "Inscripcion.h"
#include "InscripcionArchivo.h"
#include "Fecha.h"
#include "Validaciones.h"


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
