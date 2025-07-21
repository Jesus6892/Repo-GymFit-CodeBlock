#include "Menu.h"
#include <iostream>
#include <limits> // Necesario para numeric_limits
#include "Validaciones.h"

using namespace std;

void Menu::mostrarMenu() {
    system("cls");
    cout << "\n========================================\n";
    cout << "            SISTEMA GYM FIT            \n";
    cout << "========================================\n";
    cout << "  1) Realizar Inscripcion a Clase      \n";
    cout << "  2) Realizar Baja de Clase            \n";
    cout << "  3) Gestionar Pagos                   \n";
    cout << "  4) Administracion y Gestion          \n";
    cout << "----------------------------------------\n";
    cout << "  0) Salir                             \n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
}

void Menu::procesarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            gestionarProceso();
            break;
        case 2:
            gestionarBajaDeClase();
            break;
        case 3:
            gestionarPago();
            break;
        case 4:
            gestionarAdministracion();
            break;
        case 0:
            cout << " Saliendo... Hasta luego!\n";
            break;
        default:
            cout << " Opcion no valida.\n";
            system("pause");
            system("cls");
    }
}

void GestionarProceso::mostrarMenu() {
    system("cls");
    cout << "\n--- PROCESOS COMPLETOS ---" << endl;
    cout << "1. Realizar una Inscripcion" << endl;
    cout << "2. Dar de baja una Inscripcion" << endl;
    cout << "3. Ver listado de Inscripciones Activas" << endl;
    cout << "0. Volver al Menu Principal" << endl;
}

void GestionarProceso::iniciar() {
    int opcion;
    do {
        mostrarMenu();
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 3);
        switch (opcion) {
            case 1:
                realizarInscripcion();
                break;
            case 2:
                realizarBajaInscripcion();
                break;
            case 3:
                listarInscripciones();
                system("pause");
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                system("pause");
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
        if (opcion != 0) {
            system("pause");
            system("cls");
        }
    } while (opcion != 0);
}

void Menu::gestionarAdministracion() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== ADMINISTRACION Y GESTION =====\n";
        cout << "1. Gestionar Alumnos\n";
        cout << "2. Gestionar Profesores\n";
        cout << "3. Gestionar Actividades\n";
        cout << "4. Gestionar Clases\n";
        cout << "5. Gestionar Horarios\n";
        cout << "0. Volver al Menu Principal\n";
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
            case 1: gestionarAlumnos(); break;
            case 2: gestionarProfes(); break;
            case 3: gestionarActividades(); break;
            case 4: gestionarClases(); break;
            case 5: gestionarHorarios(); break;
            case 0: cout << "Volviendo al menu principal...\n"; system("pause"); break;
            default: cout << "Opcion no valida, intente nuevamente.\n"; system("pause");
        }
    } while (opcion != 0);
}

void Menu::gestionarBajaDeClase()
{
    system("cls");
    cout << "\n--- Baja de Clase ---\n";
    gestorClase.bajaClase();
    system("pause");
    system("cls");
}

void Menu::gestionarProceso() {
    GestionarProceso proceso;
    proceso.iniciar();
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
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
            case 1:
                gestorAlumnos.altaAlumno();
                break;
            case 2:
                gestorAlumnos.bajaAlumno();
                break;
            case 3:
                gestorAlumnos.modificarAlumno();
                break;
            case 4:
                gestorAlumnos.buscarAlumno();
                break;
            case 5:
                gestorAlumnos.listarAlumnos();
                system("pause");
                break;
            case 0:
                cout << "Volviendo al menu principal...\n";
                system("pause");
                break;
            default:
                cout << "Opcion no valida, intente nuevamente.\n";
                system("pause");
        }

    } while (opcion != 0);
}

void Menu::gestionarProfes() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== GESTION DE PROFESORES =====\n";
        cout << "1. Alta de Profesor\n";
        cout << "2. Baja de Profesor\n";
        cout << "3. Modificar Profesor\n";
        cout << "4. Buscar Profesor\n";
        cout << "5. Listar Profesores\n";
        cout << "0. Volver al Menu Principal\n";
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
        case 1:
            gestorProfe.altaProfesor();
            break;
        case 2:
            gestorProfe.bajaProfesor();
            break;
        case 3:
            gestorProfe.modificarProfesor();
            break;
        case 4:
            gestorProfe.buscarProfesor();
            break;
        case 5:
            gestorProfe.listarProfesores();
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
            system("pause");
        }

    } while (opcion != 0);
}

void Menu::gestionarActividades() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== GESTION DE ACTIVIDADES =====\n";
        cout << "1. Alta de Actividad\n";
        cout << "2. Baja de Actividad\n";
        cout << "3. Modificar Actividad\n";
        cout << "4. Buscar Actividad\n";
        cout << "5. Listar Actividades\n";
        cout << "0. Volver al Menu Principal\n";
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
        case 1:
            gestorActividades.altaActividad();
            break;
        case 2:
            gestorActividades.bajaActividad();
            break;
        case 3:
            gestorActividades.modificarActividad();
            break;
        case 4:
            gestorActividades.buscarActividad();
            break;
        case 5:
            gestorActividades.listarActividades();
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
            system("pause");
        }

    } while (opcion != 0);
}

void Menu::gestionarClases() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== GESTION DE CLASES =====\n";
        cout << "1. Alta de Clase\n";
        cout << "2. Baja de Clase\n";
        cout << "3. Listar Clases\n";
        cout << "4. Listar Alumnos por Clase\n";
        cout << "0. Volver al Menu Principal\n";
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
        case 1:
            gestorClase.altaClase();
            break;
        case 2:
            gestorClase.bajaClase();
            break;
        case 3:
            gestorClase.listarClases();
            system("pause");
            break;
        case 4:
            gestorClase.listarAlumnosPorClase();
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
            system("pause");
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
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 3);

        switch (opcion) {
        case 1:
            gestorPagos.altaPago();
            break;
        case 2:
            gestorPagos.bajaPago();
            break;
        case 3:
            gestorPagos.listarPagos();
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
            system("cls");
        }

    } while (opcion != 0);
}

void Menu::gestionarHorarios() {
    int opcion;
    do {
        system("cls");
        cout << "\n===== GESTION DE HORARIOS =====\n";
        cout << "1. Alta de Horario\n";
        cout << "2. Baja de Horario\n";
        cout << "3. Modificar Horario\n";
        cout << "4. Buscar Horario\n";
        cout << "5. Listar Horarios\n";
        cout << "0. Volver al Menu Principal\n";
        opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
        case 1:
            {
                cout << "\n--- Alta de Horario en Clase Existente ---" << endl;
                gestorClase.listarClases();
                int idClase;
                cout << "\nIngrese el ID de la clase para agregar el horario (0 para cancelar): ";
                cin >> idClase;
                if (idClase > 0) {
                    gestorHorarios.altaHorarioParaClase(idClase);
                } else {
                    cout << "Operacion cancelada.\n";
                }
            }
            break;
        case 2:
            gestorHorarios.bajaHorario();
            break;
        case 3:
            cout << "No implementado\n";
            break;
        case 4:
            gestorHorarios.buscarHorario();
            break;
        case 5:
            gestorHorarios.listarHorarios();
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente nuevamente.\n";
            system("pause");
        }
    } while (opcion != 0);
}



