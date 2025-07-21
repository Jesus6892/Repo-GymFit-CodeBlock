#include "GestionarProfe.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "Utilidades.h"
#include "Profe.h"
#include "Validaciones.h"
using namespace std;

GestionarProfesor::GestionarProfesor()
    : archivoProfesores(sizeof(Profe))
{
}

// Metodos Auxiliares
std::string GestionarProfesor::solicitarDniProfesor()
{
    string dniIngresado, dniNormalizado;
    while (true)
    {
        cout << "Ingrese el DNI del profesor: ";
        getline(cin, dniIngresado);

        dniNormalizado = Validaciones::normalizarDNI(dniIngresado);

        if (!Validaciones::esFormatoDniValido(dniNormalizado))
        {
            cout << "Error: El DNI debe contener 8 digitos. Intente de nuevo.\n";
            continue;
        }
        if (archivoProfesores.buscarIdPorDni(dniNormalizado) != -1)
        {
            cout << "Error: Ya existe un profesor con ese DNI. Intente de nuevo.\n";
            continue;
        }
        return dniNormalizado;
    }
}

// Métodos Principales
Profe GestionarProfesor::cargarProfesor()
{
    string nombre, apellido, correoElectronico, observaciones;
    string telefono, CUIT;
    int idProfe;
    // 1) nombre
    do {
        cout << "Ingrese el nombre del profesor (0 para cancelar): ";
        getline(cin, nombre);
            if (nombre == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
        if (!Validaciones::esSoloLetras(nombre)) {
            cout << "Nombre invalido. Solo letras y espacios.\n";
        }
    } while(!Validaciones::esSoloLetras(nombre));

    // 2) Apellido
    do {
        cout << "Ingrese el apellido del profesor (0 para cancelar): ";
        getline(cin, apellido);
            if (apellido == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
        if (!Validaciones::esSoloLetras(apellido)) {
            cout << "Apellido invalido. Solo letras y espacios.\n";
        }
    } while(!Validaciones::esSoloLetras(apellido));

    // 3) DNI
    string dni = solicitarDniProfesor();

    // 4) EMAIL
    cout << "Ingrese el correo electronico del profesor (0 para cancelar): ";
    getline(cin, correoElectronico);
             if (correoElectronico == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
    while(!Validaciones::esEmailValido(correoElectronico)) {
        cout << "Email invalido. Formato: usuario@dominio.ext\n";
        cout << "Ingrese nuevamente: ";
        getline(cin, correoElectronico);
    }

    // 5) CUIT
    do {
        cout << "Ingrese el CUIT del profesor (11 digitos) (0 para cancelar): ";
        getline(cin, CUIT);
            if (CUIT == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
        if (!Validaciones::esCUITValido(CUIT)) {
            cout << "CUIT invalido. Debe tener 11 digitos numericos.\n";
        }
    } while (!Validaciones::esCUITValido(CUIT));

    // 6) Observaciones
    do {
        cout << "Ingrese cualquier observacion sobre el profesor (0 para cancelar): ";
        getline(cin, observaciones);
            if (observaciones == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
        if (!Validaciones::esObservacionValida(observaciones)) {
            cout << "Observacion invalida. Debe contener al menos alguna letra.\n";
        }
    } while (!Validaciones::esObservacionValida(observaciones));

    // 7) Telefono
    do {
        cout << "Ingrese el telefono del profesor (0 para cancelar): ";
        getline(cin, telefono);
             if (telefono == "0") {
                std::cout << "\nCarga del profesor cancelada exitosamente.\n";
                system("pause");
                return Profe();
        }
        if (!Validaciones::esTelefonoValido(telefono)) {
            cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
        }
    } while(!Validaciones::esTelefonoValido(telefono));


    idProfe = obtenerIdNuevo();

    // Fecha de alta automática
    auto now = time(nullptr);
    auto *local = localtime(&now);
    int diaAlta = local->tm_mday;
    int mesAlta = local->tm_mon + 1;
    int anioAlta = local->tm_year + 1900;

    return Profe(
        nombre, apellido, dni,
        correoElectronico, telefono,
        CUIT,
        diaAlta, mesAlta, anioAlta,
        observaciones,
        idProfe);
}

void GestionarProfesor::altaProfesor()
{
    Profe nuevoProfesor = cargarProfesor();

    if (nuevoProfesor.getId() == -1) {
        std::cout << "Alta del profesor cancelada por el usuario.\n";
        return;
    }

    if (archivoProfesores.guardar(nuevoProfesor)) {
        cout << "Profesor agregado exitosamente.\n";
    } else
        cout << "Error al guardar el profesor.\n";
        system("pause");
}

void GestionarProfesor::listarProfesores()
{
    int total = archivoProfesores.contarRegistros();
    if (total == 0) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "|   No hay profesores registrados.              |\n"
            << "+-----------------------------------------------+\n\n";
        return;
    }

    bool huboActivos = false;
    for (int i = 0; i < total; ++i)
    {
        Profe p = archivoProfesores.leerRegistro(i);
        if (!p.getEstado())
            continue;

        if (!huboActivos) {
            cout << "=== GESTION DE PROFESORES ===\n\n";
            cout << "ID | Nombre       | Apellido     | DNI       | Estado\n";
            cout << "-------------------------------------------------------\n";
            huboActivos = true;
        }

        string rawDni = p.getDni();
        rawDni.erase(remove_if(rawDni.begin(), rawDni.end(),
                               [](char c)
                               { return !isdigit((unsigned char)c); }),
                     rawDni.end());
        if (rawDni.length() > 9)
            rawDni = rawDni.substr(0, 9);

        cout << setw(2) << p.getId() << " | "
             << setw(12) << p.getNombre() << " | "
             << setw(12) << p.getApellido() << " | "
             << setw(9) << rawDni << " | "
             << "Activo"
             << "\n";
    }

    if (!huboActivos) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "| AVISO: No se encontraron profesores activos. |\n"
            << "+-----------------------------------------------+\n\n";
    } else {
        cout << "\n";
    }
}

void GestionarProfesor::bajaProfesor()
{
    std::string dni;
    do
    {
        cout << "Ingrese el DNI del profesor a dar de baja (8 digitos) o (0 para cancelar): ";
        cin >> dni;

        if (dni == "0") {
            std::cout << "Baja del profesor cancelada exitosamente.\n";
            system("pause");
            return;
    }

        if (!Validaciones::esDNIValido(dni))
            cout << "DNI invalido. Debe ser 8 digitos numericos.\n";

    } while (!Validaciones::esDNIValido(dni));

    int pos = archivoProfesores.buscarPosPorDni(dni);
    if (pos >= 0)
    {
        Profe profesor = archivoProfesores.leerRegistro(pos);
        profesor.setEstado(false);
        if (archivoProfesores.modificarRegistro(profesor, pos))
            cout << "Profesor dado de baja exitosamente.\n";
        else
            cout << "Error al dar de baja el profesor.\n";
            system("pause");
    }
    else
        cout << "Profesor no encontrado.\n";
}

void GestionarProfesor::buscarProfesor()
{
    std::string dni;
    do
    {
        cout << "Ingrese el DNI del profesor a buscar (8 digitos) o (0 para cancelar): ";
        cin >> dni;

        if (dni == "0") {
            std::cout << "Busqueda del profesor cancelada exitosamente.\n";
            system("pause");
            return;
    }

        if (!Validaciones::esDNIValido(dni))
            cout << "DNI invalido. Debe ser 8 digitos numericos.\n";

    } while (!Validaciones::esDNIValido(dni));

    int pos = archivoProfesores.buscarPosPorDni(dni);
    if (pos >= 0)
        archivoProfesores.leerRegistro(pos).mostrar();
    else
        cout << "Profesor no encontrado.\n";
        system("pause");
}

void GestionarProfesor::modificarProfesor()
{
    std::string dni;
    do {
        std::cout << "Ingrese el DNI del profesor a modificar (8 digitos) o (0 para cancelar): ";
        std::cin >> dni;

        if (dni == "0") {
        std::cout << "Modificacion del profesor cancelada exitosamente.\n";
        system("pause");
        return;
    }

        if (!Validaciones::esDNIValido(dni)) {
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
        }
    } while (!Validaciones::esDNIValido(dni));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pos = archivoProfesores.buscarPosPorDni(dni);
    if (pos < 0)
    {
        std::cout << "No se encontro un profesor con ese DNI.\n";
        system("pause");
        return;
    }

    Profe profe = archivoProfesores.leerRegistro(pos);
    std::cout << "Datos actuales del profesor:\n";
    profe.mostrar();

    bool seguirModificando;
    do {
        std::cout << "\nQue campo desea modificar?\n";
        std::cout << "1. Nombre\n";
        std::cout << "2. Apellido\n";
        std::cout << "3. Correo Electronico\n";
        std::cout << "4. Telefono\n";
        std::cout << "5. CUIT\n";
        std::cout << "0. Cancelar\n";
        int opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        std::string nuevoValor;

        switch (opcion)
        {
        case 1:
            do {
                std::cout << "Ingrese el nuevo nombre: ";
                std::getline(std::cin, nuevoValor);
                if (!Validaciones::esSoloLetras(nuevoValor)) {
                    std::cout << "Nombre invalido. Solo letras y espacios.\n";
                }
            } while (!Validaciones::esSoloLetras(nuevoValor));
            profe.setNombre(nuevoValor);
            break;

        case 2:
            do {
                std::cout << "Ingrese el nuevo apellido: ";
                std::getline(std::cin, nuevoValor);
                if (!Validaciones::esSoloLetras(nuevoValor)) {
                    std::cout << "Apellido invalido. Solo letras y espacios.\n";
                }
            } while (!Validaciones::esSoloLetras(nuevoValor));
            profe.setApellido(nuevoValor);
            break;

        case 3:
            do {
                std::cout << "Ingrese el nuevo correo electronico: ";
                std::getline(std::cin, nuevoValor);
                if (!Validaciones::esEmailValido(nuevoValor)) {
                    std::cout << "Email invalido. El formato debe ser: usuario@dominio.ext\n";
                }
            } while (!Validaciones::esEmailValido(nuevoValor));
            profe.setCorreoElectronico(nuevoValor);
            break;

        case 4:
            do {
                std::cout << "Ingrese el nuevo telefono (10 digitos): ";
                std::getline(std::cin, nuevoValor);
                if (!Validaciones::esTelefonoValido(nuevoValor)) {
                    std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
                }
            } while (!Validaciones::esTelefonoValido(nuevoValor));
            profe.setTelefono(nuevoValor);
            break;

        case 5:
            do {
                std::cout << "Ingrese el nuevo CUIT (11 digitos): ";
                std::getline(std::cin, nuevoValor);
                if (!Validaciones::esCUITValido(nuevoValor)) {
                    std::cout << "CUIT invalido. Debe ser 11 digitos numericos.\n";
                }
            } while (!Validaciones::esCUITValido(nuevoValor));
            profe.setCUIT(nuevoValor);
            break;

        case 0:
            std::cout << "Modificacion cancelada.\n";
            system("pause");
            return;

        default:
            std::cout << "Opcion no valida.\n";
            system("pause");
            continue;
        }

        seguirModificando = Validaciones::pedirEntero("Desea modificar otro campo? (1 = SI, 0 = NO): ", 0, 1) == 1;

    } while (seguirModificando);

    if (archivoProfesores.modificarRegistro(profe, pos))
    {
        std::cout << "Modificacion realizada exitosamente.\n";
    }
    else
    {
        std::cout << "Error al modificar el profesor.\n";
    }

    system("pause");
}

int GestionarProfesor::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ProfesArchivo, Profe>(archivoProfesores);
}
