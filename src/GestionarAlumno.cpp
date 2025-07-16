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
    do
    {
        std::cout << "Ingrese nombre: ";
        std::getline(std::cin, nombre);
        if (!Validaciones::esSoloLetras(nombre))
            std::cout << "Nombre invalido. Solo letras y espacios.\n";
    } while (!Validaciones::esSoloLetras(nombre));

    // Apellido
    do
    {
        std::cout << "Ingrese apellido: ";
        std::getline(std::cin, apellido);
        if (!Validaciones::esSoloLetras(apellido))
            std::cout << "Apellido invalido. Solo letras y espacios.\n";
    } while (!Validaciones::esSoloLetras(apellido));

    // DNI
    ArchivoAlumnos archivoAlumnos(sizeof(Alumno));
    do
    {
        std::cout << "Ingrese DNI (8 digitos): ";
        std::cin >> dni;

        if (!Validaciones::esDNIValido(dni)) {
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
            continue;
        }

        int pos = archivoAlumnos.buscarPosPorDni(dni);
        if (pos >= 0) {
            std::cout << "PEDAZO DE ERROR: DNI ya registrado. Intente nuevamente.\n";
            dni.clear();
        }

    } while (!Validaciones::esDNIValido(dni) || archivoAlumnos.buscarPosPorDni(dni) >= 0);

    // Correo electronico

    do
    {
        std::cout << "Ingrese correo electronico: ";
        std::cin >> correoElectronico;

        if (!Validaciones::esEmailValido(correoElectronico))
            std::cout << "Email invalido. El formato debe ser: usuario@dominio.ext\n";

    } while (!Validaciones::esEmailValido(correoElectronico));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Telefono
    do
    {
        std::cout << "Ingrese telefono (10 digitos): ";
        std::cin >> telefono;
        if (!Validaciones::esTelefonoValido(telefono))
            std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
    } while (!Validaciones::esTelefonoValido(telefono));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int idAlumno = obtenerIdNuevo();

    return Alumno(
        nombre,
        apellido,
        dni,
        correoElectronico,
        telefono,
        idAlumno
    );
}



void GestionarAlumno::altaAlumno()
{
    Alumno nuevoAlumno = cargarAlumno();
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
        std::cout << "Ingrese el DNI del alumno a dar de baja (8 digitos): ";
        std::cin >> dni;

        if (!Validaciones::esDNIValido(dni))
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";

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
    std::cout << "Ingrese el DNI del alumno a buscar: ";
    std::cin >> dni;
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
    std::cout << "Ingrese el DNI del alumno a modificar: ";
    std::cin >> dni;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pos = archivoAlumnos.buscarPosPorDni(dni);
    if (pos < 0)
    {
        std::cout << "No se encontró un alumno con ese DNI." << std::endl;
        return;
    }

    Alumno alumno = archivoAlumnos.leerRegistro(pos);
    std::cout << "Datos actuales del alumno:" << std::endl;
    alumno.mostrar();

    int opcion;
    std::string nuevoValor;

    std::cout << "\n¿Qué campo desea modificar?" << std::endl;
    std::cout << "1. Nombre" << std::endl;
    std::cout << "2. Apellido" << std::endl;
    std::cout << "3. Correo Electronico" << std::endl;
    std::cout << "4. Telefono" << std::endl;
    std::cout << "0. Cancelar" << std::endl;
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion)
    {
    case 1:
        std::cout << "Ingrese el nuevo nombre: ";
        std::getline(std::cin, nuevoValor);
        alumno.setNombre(nuevoValor);
        break;
    case 2:
        std::cout << "Ingrese el nuevo apellido: ";
        std::getline(std::cin, nuevoValor);
        alumno.setApellido(nuevoValor);
        break;
    case 3:
        std::cout << "Ingrese el nuevo correo electronico: ";
        std::getline(std::cin, nuevoValor);
        while (!Validaciones::esEmailValido(nuevoValor)) {
            std::cout << "Email invalido. Ingrese nuevamente: ";
            std::getline(std::cin, nuevoValor);
        }
        alumno.setCorreoElectronico(nuevoValor);
        break;
    case 4:
        std::cout << "Ingrese el nuevo telefono: ";
        std::getline(std::cin, nuevoValor);
         while (!Validaciones::esTelefonoValido(nuevoValor)) {
            std::cout << "Telefono invalido. Ingrese nuevamente: ";
            std::getline(std::cin, nuevoValor);
        }
        alumno.setTelefono(nuevoValor);
        break;
    case 0:
        std::cout << "Modificacion cancelada." << std::endl;
        return;
    default:
        std::cout << "Opcion no valida." << std::endl;
        return;
    }

    if (archivoAlumnos.modificarRegistro(alumno, pos))
    {
        std::cout << "Alumno modificado exitosamente." << std::endl;
    }
    else
    {
        std::cout << "Error al modificar el alumno." << std::endl;
    }
}
