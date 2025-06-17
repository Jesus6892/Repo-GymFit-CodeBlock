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
    //void gestionarProfes();
    void gestionarActividades();
    void gestionarPago(); // <--- NUEVA LÍNEA


    /*
    void gestionarHorarios();
    void gestionarInscripciones();
    */
private:

    GestionarAlumno gestorAlumnos;
    //GestionarProfesor gestorProfe;
    GestionarActividad gestorActividades;
    GestionarPago gestorPagos; // <--- NUEVA LÍNEA


    /*
    GestionarHorario gestorHorarios;
    */
};
