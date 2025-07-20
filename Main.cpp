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
#include "Validaciones.h"
#include <string>


int main() {

    Menu menu;
    int opcion;
    std::string opcionStr;


    //Bucle para que el usuario pueda elegir una opcion
    do {
        menu.mostrarMenu();
        std::cin >> opcionStr;

        if (Validaciones::esSoloNumeros(opcionStr)) {
            opcion = std::stoi(opcionStr);
            menu.procesarOpcion(opcion);
        } else {
            std::cout << "Opcion no valida. Por favor, ingrese un numero." << std::endl;
            system("pause");
            opcion = -1;
        }

    } while (opcion != 0);

    return 0;

}
