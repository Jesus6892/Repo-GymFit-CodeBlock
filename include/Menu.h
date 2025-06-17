#pragma once
#include "GestionarAlumno.h"
#include "GestionarProfe.h"
#include "GestionarActividad.h"
#include "GestionarHorario.h"
#include "GestionarPago.h"

class Menu {
public:
    void mostrarMenu();
    void procesarOpcion(int opcion);


    void gestionarAlumnos();
    void gestionarProfes();
    void gestionarActividades();
    void gestionarPago();


    /*
    void gestionarHorarios();
    */
private:

    GestionarAlumno gestorAlumnos;
    GestionarProfesor gestorProfe;
    GestionarActividad gestorActividades;
    GestionarPago gestorPagos;


    /*
    GestionarHorario gestorHorarios;
    */
};
