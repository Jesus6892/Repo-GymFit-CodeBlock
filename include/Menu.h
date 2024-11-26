#pragma once
#include "GestionarAlumno.h"
#include "GestionarProfe.h"
#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "GestionarInscripciones.h"

class Menu {
public:
    void mostrarMenu();
    void procesarOpcion(int opcion);

    void gestionarAlumnos();
    void gestionarProfes();
    void gestionarActividades();
    void gestionarHorarios();
    void gestionarInscripciones();
private:
    GestionarAlumno gestorAlumnos;
    GestionarProfesor gestorProfe;
    GestionarActividad gestorActividades;
    GestionarHorario gestorHorarios;
    GestionarInscripciones gestorInscripciones;
};
