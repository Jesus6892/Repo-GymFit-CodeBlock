#include <iostream>
#include "Fecha.h"
#include "Actividad.h"
#include "ActividadesArchivo.h"
#include "Empleado.h"
#include "IArchivable.h"
#include "Alumno.h"
#include "AlumnosArchivo.h"
#include "Profe.h"
#include "ProfesArchivo.h"
#include "Horario.h"
#include "HorarioPorClaseArchivo.h"
#include "Menu.h"


int main() {

    Menu menu;
    int opcion;

    do {
        menu.mostrarMenu();
        cin >> opcion;
        menu.procesarOpcion(opcion);
    } while (opcion != 0);

    return 0;

}

























