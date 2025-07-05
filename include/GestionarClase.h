#ifndef GESTIONARCLASE_H
#define GESTIONARCLASE_H

#include "Clase.h"
#include "ClaseArchivo.h"
#include "ActividadesArchivo.h"
#include "ProfesArchivo.h"
#include "Utilidades.h"

class GestionarClase {
public:
    GestionarClase();
    void altaClase();
    void bajaClase();
    void listarClases();
    // A futuro podríamos añadir modificarClase()

private:
    Clase cargarClase();
    int obtenerIdNuevo();
    void mostrarEncabezadoListado() const;

    ClaseArchivo _archivoClases;
    ActividadesArchivo _archivoActividades;
    ProfesArchivo _archivoProfes;
};

#endif // GESTIONARCLASE_H 