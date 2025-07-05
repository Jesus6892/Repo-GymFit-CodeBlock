#pragma once
#include "GestionarAlumno.h"
#include "GestionarProfe.h"
#include "GestionarActividad.h"
#include "GestionarClase.h"
#include "GestionarHorario.h"
#include "GestionarPago.h"
#include "GestionarProceso.h"

class Menu {
public:
    void mostrarMenu();
    void procesarOpcion(int opcion);


    void gestionarProceso();
    void gestionarAlumnos();
    void gestionarProfes();
    void gestionarActividades();
    void gestionarClases();
    void gestionarPago();
    void gestionarHorarios();

private:

    // Clases de gestión
    GestionarProceso gestorProceso;
    GestionarAlumno gestorAlumnos;
    GestionarProfesor gestorProfe;
    GestionarActividad gestorActividades;
    GestionarClase gestorClase;
    GestionarPago gestorPagos;
    GestionarHorario gestorHorarios;
};
