#include "Menu.h"
#include <iostream>
using namespace std;


void Menu::mostrarMenu() {
    cout << "\n========================================\n";
    cout << "            SISTEMA GYM FIT            \n";
    cout << "========================================\n";
    cout << "  1) Proceso de Inscripcion            \n";
    cout << "  2) Gestionar Pagos                   \n";
    cout << "  3) Gestionar Alumnos                 \n";
    cout << "  4) Gestionar Profesores              \n";
    cout << "  5) Gestionar Actividades             \n";
    cout << "  6) Gestionar Horarios                \n";
    cout << "----------------------------------------\n";
    cout << "  0) Salir                             \n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
}


void Menu::procesarOpcion(int opcion) {
    cout << "\n----------------------------------------\n";
    switch (opcion) {
        case 1:
            gestionarProceso();
            break;
        case 2:
            gestionarPago();  
            break;
        case 3:
            gestionarAlumnos();
            break;
        case 4:
            gestionarProfes(); 
            break;
        case 5:
            gestionarActividades(); // o submenú
            break;
        case 6:
            gestionarHorarios(); 
            break;
        case 0:
            cout << " Saliendo... ¡Hasta luego!\n";
            break;
        default:
            cout << " Opción no válida.\n";
            system("pause");
    }
    cout << "----------------------------------------\n";
}

void Menu::gestionarProceso() {
    GestionarProceso proceso;
    proceso.iniciarProceso();
}

void Menu::gestionarAlumnos() {
    int opcion;
    do {
        system("cls");  
        cout << "\n===== GESTION DE ALUMNOS =====\n";
        cout << "1. Alta de Alumno\n";
        cout << "2. Baja de Alumno\n";
        cout << "3. Modificar Alumno\n";
        cout << "4. Buscar Alumno\n";
        cout << "5. Listar Alumnos\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                gestorAlumnos.altaAlumno();
                break;
            case 2:
                gestorAlumnos.bajaAlumno();
                break;
            case 3:
                //gestorAlumnos.modificarAlumno();
                cout << "Módulo 'Modificar Alumno' no implementado.\n";
                system("pause");
                break;
            case 4:
                gestorAlumnos.buscarAlumno();
                break;
            case 5:
                gestorAlumnos.listarAlumnos();
                break;
            case 0:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción no válida, intente nuevamente.\n";
                system("pause");
        }

        if (opcion != 0 && opcion >= 1 && opcion <= 5) {
            system("pause");  
        }
    } while (opcion != 0);
}

void Menu::gestionarProfes() {
    int opcion;
    do {
        cout << "\n===== GESTION DE PROFESORES =====\n";
        cout << "1. Alta de Profesor\n";
        cout << "2. Baja de Profesor\n";
        cout << "3. Modificar Profesor\n";
        cout << "4. Buscar Profesor\n";
        cout << "5. Listar Profesores\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestorProfe.altaProfesor();
            break;
        case 2:
            gestorProfe.bajaProfesor();
            break;
        case 3:
            //gestorProfe.modificarProfesor();
            cout << "No implementado\n";
            break;
        case 4:
            gestorProfe.buscarProfesor();
            break;
        case 5:
            gestorProfe.listarProfesores();
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Menu::gestionarActividades() {
    int opcion;
    do {
        cout << "\n===== GESTION DE ACTIVIDADES =====\n";
        cout << "1. Alta de Actividad\n";
        cout << "2. Baja de Actividad\n";
        cout << "3. Modificar Actividad\n";
        cout << "4. Buscar Actividad\n";
        cout << "5. Listar Actividades\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestorActividades.altaActividad();
            break;
        case 2:
            gestorActividades.bajaActividad();
            break;
        case 3:
            //gestorActividades.modificarActividad();
            cout << "No implementado\n";
            break;
        case 4:
            gestorActividades.buscarActividad();
            break;
        case 5:
            gestorActividades.listarActividades();
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Menu::gestionarPago() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== GESTION DE PAGOS =====\n";
        cout << "1. Registrar Pago\n";
        cout << "2. Anular Pago\n";
        cout << "3. Listar Pagos\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Limpiar buffer de entrada para evitar problemas con std::getline o futuras entradas
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (opcion) {
        case 1:
            gestorPagos.altaPago();
            break;
        case 2:
            gestorPagos.bajaPago(); // En GestionarPago.h se llama bajaPago para anular
            break;
        case 3:
            gestorPagos.listarPagos();
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
        }
        if (opcion != 0) {
            system("pause");
        }
    } while (opcion != 0);
}

void Menu::gestionarHorarios() {
    int opcion;
    do {
        cout << "\n===== GESTION DE HORARIOS =====\n";
        cout << "1. Alta de Horario\n";
        cout << "2. Baja de Horario\n";
        cout << "3. Modificar Horario\n";
        cout << "4. Buscar Horario\n";
        cout << "5. Listar Horarios\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            //gestorHorarios.altaHorario();
            break;
        case 2:
            gestorHorarios.bajaHorario();
            break;
        case 3:
            //gestorHorarios.modificarHorario();
            cout << "No implementado\n";
            break;
        case 4:
            gestorHorarios.buscarHorario();
            break;
        case 5:
            gestorHorarios.listarHorarios();
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
        }
    } while (opcion != 0);
}



