#include "GestionarAlumno.h"
#include "AlumnosArchivo.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Utilidades.h"
#include <Validaciones.h>

GestionarAlumno::GestionarAlumno() : archivoAlumnos(sizeof(Alumno)) {}


Alumno GestionarAlumno::cargarAlumno()
{
    std::string nombre, apellido, dni, correoElectronico, telefono;
    bool estado = true;

    // Nombre
    do {
        std::cout << "Ingrese nombre (0 para cancelar): ";
        std::getline(std::cin, nombre);
        if (nombre == "0") {
            std::cout << "\nCarga de alumno cancelada exitosamente.\n";
            system("pause");
            return Alumno();
        }
        if (!Validaciones::esSoloLetras(nombre))
            std::cout << "Nombre invalido. Solo letras y espacios.\n";
    } while (!Validaciones::esSoloLetras(nombre));

    // Apellido
    do {
        std::cout << "Ingrese apellido (0 para cancelar): ";
        std::getline(std::cin, apellido);
        if (apellido == "0"){
            std::cout << "\nCarga de alumno cancelada exitosamente.\n";
            system("pause");
            return Alumno();
        }

        if (!Validaciones::esSoloLetras(apellido))
            std::cout << "Apellido invalido. Solo letras y espacios.\n";
    } while (!Validaciones::esSoloLetras(apellido));

    // DNI
    ArchivoAlumnos archivoAlumnos(sizeof(Alumno));
    do {
        std::cout << "Ingrese DNI (8 digitos, 0 para cancelar): ";
        std::cin >> dni;
        if (dni == "0"){
            std::cout << "\nCarga de alumno cancelada exitosamente.\n";
            system("pause");
            return Alumno();
        }

        if (!Validaciones::esDNIValido(dni)) {
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
            continue;
        }

        int pos = archivoAlumnos.buscarPosPorDni(dni);
        if (pos >= 0) {
            std::cout << "PEDAZO DE ERROR: DNI ya registrado. Intente nuevamente.\n";
        }

    } while (!Validaciones::esDNIValido(dni) || archivoAlumnos.buscarPosPorDni(dni) >= 0);

    // Correo electrónico
    do {
        std::cout << "Ingrese correo electronico (0 para cancelar): ";
        std::cin >> correoElectronico;
        if (correoElectronico == "0"){
            std::cout << "\nCarga de alumno cancelada exitosamente.\n";
            system("pause");
            return Alumno();
        }

        if (!Validaciones::esEmailValido(correoElectronico))
            std::cout << "Email invalido. El formato debe ser: usuario@dominio.ext\n";

    } while (!Validaciones::esEmailValido(correoElectronico));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Teléfono
    do {
        std::cout << "Ingrese telefono (10 digitos, 0 para cancelar): ";
        std::cin >> telefono;
        if (telefono == "0"){
            std::cout << "\nCarga de alumno cancelada exitosamente.\n";
            system("pause");
            return Alumno();
        }

        if (!Validaciones::esTelefonoValido(telefono))
            std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
    } while (!Validaciones::esTelefonoValido(telefono));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int idAlumno = obtenerIdNuevo();

    return Alumno(nombre,
                  apellido,
                  dni,
                  correoElectronico,
                  telefono,
                  idAlumno);
}

void GestionarAlumno::altaAlumno()
{
    Alumno nuevoAlumno = cargarAlumno();

    if (nuevoAlumno.getDni().empty()) {
        std::cout << "Alta de alumno cancelada por el usuario.\n";
        return;
    }

    if (archivoAlumnos.guardar(nuevoAlumno))
        std::cout << "Alumno agregado exitosamente.\n";
    else
        std::cout << "Error al guardar el alumno.\n";
}

void GestionarAlumno::bajaAlumno()
{
    std::string dni;
    do
    {
        std::cout << "Ingrese el DNI del alumno a dar de baja (8 digitos) o 0 para cancelar: ";
        std::getline(std::cin, dni);

        if (dni == "0")
            return;

        if (!Validaciones::esDNIValido(dni))
        {
            std::cout << "DNI invalido. Deben ser 8 digitos numericos.\n";
        }

    } while (!Validaciones::esDNIValido(dni));


    int pos = archivoAlumnos.buscarPosPorDni(dni);
    if (pos >= 0)
    {
        Alumno a = archivoAlumnos.leerRegistro(pos);
        a.setEstado(false);
        if (archivoAlumnos.modificarRegistro(a, pos))
            std::cout << "Alumno dado de baja exitosamente.\n";
        else
            std::cout << "Error al dar de baja al alumno.\n";
    }
    else
    {
        std::cout << "Alumno no encontrado.\n";
    }
}

void GestionarAlumno::listarAlumnos()
{
    int total = archivoAlumnos.contarRegistros();
    if (total == 0)
    {
        std::cout << "\n+------------------------------------------+\n"
                  << "|       No hay alumnos registrados.        |\n"
                  << "+------------------------------------------+\n\n";
        return;
    }
    bool huboActivos = false;
    for (int i = 0; i < total; ++i)
    {
        Alumno a = archivoAlumnos.leerRegistro(i);
        if (!a.getEstado())
            continue;
        if (!huboActivos)
        {
            std::cout << "=== GESTION DE ALUMNOS ===\n\n"
                      << "ID | Nombre       | Apellido     | DNI       | Estado\n"
                      << "-------------------------------------------------------\n";
            huboActivos = true;
        }
        std::string rawDni = a.getDni();
        rawDni.erase(std::remove_if(rawDni.begin(), rawDni.end(),
                                    [](char c)
                                    { return !std::isdigit(static_cast<unsigned char>(c)); }),
                     rawDni.end());
        if (rawDni.length() > 9)
            rawDni.resize(9);
        std::cout << std::setw(2) << a.getId() << " | "
                  << std::setw(12) << a.getNombre() << " | "
                  << std::setw(12) << a.getApellido() << " | "
                  << std::setw(9) << rawDni << " | Activo\n";
    }
    if (!huboActivos)
    {
        std::cout << "\n+------------------------------------------+\n"
                  << "|   AVISO: No se encontraron alumnos       |\n"
                  << "|          activos en el sistema.          |\n"
                  << "+------------------------------------------+\n\n";
    }
    else
        std::cout << "\n";
}

void GestionarAlumno::buscarAlumno()
{
    std::string dni;
    do {
        std::cout << "Ingrese el DNI del alumno a buscar (8 digitos) o 0 para cancelar: ";
        std::cin >> dni;

        if (dni == "0") {
            std::cout << "Modificacion de alumno cancelada exitosamente.\n";
            system("pause");
            return;
    }

    if (!Validaciones::esDNIValido(dni)) {
        std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
        }
    } while (!Validaciones::esDNIValido(dni));

    int pos = archivoAlumnos.buscarPosPorDni(dni);
    if (pos >= 0)
        archivoAlumnos.leerRegistro(pos).mostrar();
    else
        std::cout << "Alumno no encontrado.\n";
}

int GestionarAlumno::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ArchivoAlumnos, Alumno>(archivoAlumnos);
}

void GestionarAlumno::modificarAlumno()
{
    std::string dni;
    do {
        std::cout << "Ingrese el DNI del alumno a modificar (8 digitos) o 0 para cancelar: ";
        std::cin >> dni;

        if (dni == "0") {
        std::cout << "Modificacion de alumno cancelada exitosamente.\n";
        system("pause");
        return;
    }

        if (!Validaciones::esDNIValido(dni)) {
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
        }
    } while (!Validaciones::esDNIValido(dni));

    int pos = archivoAlumnos.buscarPosPorDni(dni);
    if (pos < 0)
    {
        std::cout << "No se encontro un alumno con ese DNI.\n";
        system("pause");
        return;
    }

    Alumno alumno = archivoAlumnos.leerRegistro(pos);
    std::cout << "Datos actuales del alumno:\n";
    alumno.mostrar();

bool seguirModificando;
do {
    std::cout << "\nQue campo desea modificar?\n";
    std::cout << "1. Nombre\n";
    std::cout << "2. Apellido\n";
    std::cout << "3. Correo Electronico\n";
    std::cout << "4. Telefono\n";
    std::cout << "0. Cancelar\n";
    int opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 4);

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
        alumno.setNombre(nuevoValor);
        break;

    case 2:
        do {
            std::cout << "Ingrese el nuevo apellido: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esSoloLetras(nuevoValor)) {
                std::cout << "Apellido invalido. Solo letras y espacios.\n";
            }
        } while (!Validaciones::esSoloLetras(nuevoValor));
        alumno.setApellido(nuevoValor);
        break;

    case 3:
        do {
            std::cout << "Ingrese el nuevo correo electronico: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esEmailValido(nuevoValor)) {
                std::cout << "Email invalido. El formato debe ser: usuario@dominio.ext\n";
            }
        } while (!Validaciones::esEmailValido(nuevoValor));
        alumno.setCorreoElectronico(nuevoValor);
        break;

    case 4:
        do {
            std::cout << "Ingrese el nuevo telefono (10 digitos): ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esTelefonoValido(nuevoValor)) {
                std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
            }
        } while (!Validaciones::esTelefonoValido(nuevoValor));
        alumno.setTelefono(nuevoValor);
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

    std::cout << "Modificacion realizada exitosamente.\n";
    system("pause");

}

    /*int opcion;
    std::string nuevoValor;

    std::cout << "\nQue campo desea modificar?\n";
    std::cout << "1. Nombre\n";
    std::cout << "2. Apellido\n";
    std::cout << "3. Correo Electronico\n";
    std::cout << "4. Telefono\n";
    std::cout << "0. Cancelar\n";

    opcion = Validaciones::pedirEntero("Seleccione una opcion: ", 0,4);

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
        alumno.setNombre(nuevoValor);
        break;

    case 2:
        do {
            std::cout << "Ingrese el nuevo apellido: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esSoloLetras(nuevoValor)) {
                std::cout << "Apellido invalido. Solo letras y espacios.\n";
            }
        } while (!Validaciones::esSoloLetras(nuevoValor));
        alumno.setApellido(nuevoValor);
        break;

    case 3:
        do {
            std::cout << "Ingrese el nuevo correo electronico: ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esEmailValido(nuevoValor)) {
                std::cout << "Email invalido. El formato debe ser: usuario@dominio.ext\n";
            }
        } while (!Validaciones::esEmailValido(nuevoValor));
        alumno.setCorreoElectronico(nuevoValor);
        break;

    case 4:
        do {
            std::cout << "Ingrese el nuevo telefono (10 digitos): ";
            std::getline(std::cin, nuevoValor);
            if (!Validaciones::esTelefonoValido(nuevoValor)) {
                std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
            }
        } while (!Validaciones::esTelefonoValido(nuevoValor));
        alumno.setTelefono(nuevoValor);
        system("pause");
        break;

    case 0:
        std::cout << "Modificacion cancelada.\n";
        return;

    default:
        std::cout << "Opcion no valida.\n";
        return;
    }

    if (archivoAlumnos.modificarRegistro(alumno, pos))
    {
        std::cout << "Alumno modificado exitosamente.\n";
    }
    else
    {
        std::cout << "Error al modificar el alumno.\n";
    }*/

