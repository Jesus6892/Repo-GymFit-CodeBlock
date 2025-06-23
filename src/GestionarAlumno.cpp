#include "GestionarAlumno.h"
#include "AlumnosArchivo.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Utilidades.h"

GestionarAlumno::GestionarAlumno() : archivoAlumnos(sizeof(Alumno)) {}

bool soloLetras(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && c != ' ') return false;
    }
    return true;
}

bool soloNumeros(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

bool tienelongitud(const std::string& str, int longitud) {
    return static_cast<int>(str.length()) == longitud;
}

Alumno GestionarAlumno::cargarAlumno()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nombre, apellido, dni, correoElectronico, direccion, telefono;
    int diaNasc, mesNasc, anioNasc;
    bool estado = true;

    do {
        std::cout << "Ingrese nombre: ";
        std::getline(std::cin, nombre);
        if (!soloLetras(nombre))
            std::cout << "Nombre invalido. Solo letras y espacios.\n";
    } while (!soloLetras(nombre));

    do {
        std::cout << "Ingrese apellido: ";
        std::getline(std::cin, apellido);
        if (!soloLetras(apellido))
            std::cout << "Apellido invalido. Solo letras y espacios.\n";
    } while (!soloLetras(apellido));

    do {
        std::cout << "Ingrese DNI (8 digitos): ";
        std::cin >> dni;
        if (!soloNumeros(dni) || !tienelongitud(dni, 8))
            std::cout << "DNI invalido. Debe ser 8 digitos numericos.\n";
    } while (!soloNumeros(dni) || !tienelongitud(dni, 8));

    std::cout << "Ingrese fecha de nacimiento (dia mes anio): ";
    std::cin >> diaNasc >> mesNasc >> anioNasc;

    std::cout << "Ingrese correo electronico: ";
    std::cin >> correoElectronico;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ingrese direccion: ";
    std::getline(std::cin, direccion);

    do {
        std::cout << "Ingrese telefono (10 digitos): ";
        std::cin >> telefono;
        if (!soloNumeros(telefono) || !tienelongitud(telefono, 10))
            std::cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
    } while (!soloNumeros(telefono) || !tienelongitud(telefono, 10));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    int diaInsc = local->tm_mday;
    int mesInsc = local->tm_mon + 1;
    int anioInsc = local->tm_year + 1900;

    int idAlumno = obtenerIdNuevo();

    return Alumno(
        nombre,
        apellido,
        dni,
        diaNasc, mesNasc, anioNasc,
        correoElectronico,
        direccion,
        telefono,
        idAlumno,
        diaInsc, mesInsc, anioInsc,
        estado
    );
}

void GestionarAlumno::altaAlumno() {
    Alumno nuevoAlumno = cargarAlumno();
    if (archivoAlumnos.guardar(nuevoAlumno))
        std::cout << "Alumno agregado exitosamente.\n";
    else
        std::cout << "Error al guardar el alumno.\n";
}

void GestionarAlumno::bajaAlumno() {
    int id;
    std::cout << "Ingrese el ID del alumno a dar de baja: ";
    std::cin >> id;
    int pos = archivoAlumnos.buscar(id);
    if (pos >= 0) {
        Alumno a = archivoAlumnos.leerRegistro(pos);
        a.setEstadoAlta(false);
        if (archivoAlumnos.modificarRegistro(a, pos))
            std::cout << "Alumno dado de baja exitosamente.\n";
        else
            std::cout << "Error al dar de baja al alumno.\n";
    } else
        std::cout << "Alumno no encontrado.\n";
}

void GestionarAlumno::listarAlumnos() {
    int total = archivoAlumnos.contarRegistros();
    if (total == 0) {
        std::cout << "\n+------------------------------------------+\n"
                  << "|       No hay alumnos registrados.        |\n"
                  << "+------------------------------------------+\n\n";
        return;
    }
    bool huboActivos = false;
    for (int i = 0; i < total; ++i) {
        Alumno a = archivoAlumnos.leerRegistro(i);
        if (!a.getEstado()) continue;
        if (!huboActivos) {
            std::cout << "=== GESTION DE ALUMNOS ===\n\n"
                      << "ID | Nombre       | Apellido     | DNI       | Estado\n"
                      << "-------------------------------------------------------\n";
            huboActivos = true;
        }
        std::string rawDni = a.getDni();
        rawDni.erase(std::remove_if(rawDni.begin(), rawDni.end(),
            [](char c){ return !std::isdigit(static_cast<unsigned char>(c)); }), rawDni.end());
        if (rawDni.length() > 9) rawDni.resize(9);
        std::cout << std::setw(2)  << a.getId()     << " | "
                  << std::setw(12) << a.getNombre() << " | "
                  << std::setw(12) << a.getApellido() << " | "
                  << std::setw(9)  << rawDni       << " | Activo\n";
    }
    if (!huboActivos) {
        std::cout << "\n+------------------------------------------+\n"
                  << "|   AVISO: No se encontraron alumnos       |\n"
                  << "|          activos en el sistema.          |\n"
                  << "+------------------------------------------+\n\n";
    } else
        std::cout << "\n";
}

void GestionarAlumno::buscarAlumno() {
    int id;
    std::cout << "Ingrese el ID del alumno a buscar: ";
    std::cin >> id;
    int pos = archivoAlumnos.buscar(id);
    if (pos >= 0)
        archivoAlumnos.leerRegistro(pos).mostrar();
    else
        std::cout << "Alumno no encontrado.\n";
}

int GestionarAlumno::obtenerIdNuevo() {
    return Utilidades::obtenerIdNuevo<ArchivoAlumnos, Alumno>(archivoAlumnos);
}
