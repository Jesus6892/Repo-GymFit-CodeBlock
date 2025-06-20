#pragma once

#include "Alumno.h"
#include "AlumnosArchivo.h"
#include "GestionarAlumno.h"
#include <iostream>
#include "Utilidades.h"

GestionarAlumno::GestionarAlumno() : archivoAlumnos(sizeof(Alumno)) {}


//Funcion para validar si una cadena contiene solo letras
bool soloLetras(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) return false;
    }
    return true;
}

//Funcion para validar si una cadena contiene solo numeros
bool soloNumeros(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

//Funcion para validar la longitud
bool tienelongitud(const std::string& str, int longitud) {
    return str.length() == longitud;
}



Alumno GestionarAlumno::cargarAlumno()
{

    std::string nombre, apellido, dni, correoElectronico, direccion, telefono;
    int diaNasc, mesNasc, anioNasc;
    int diaInsc, mesInsc, anioInsc;
    bool estado = true; // Un nuevo alumno siempre está activo

    // --- Captura de datos ---


    do {
        std::cout << "Ingrese nombre: ";
        std::cin >> nombre;
        if (!soloLetras(nombre)) std::cout << "Nombre Invalido. El nombre debe contener solo letras" << std::endl;
    } while (!soloLetras(nombre));

    do {
        std::cout << "Ingrese apellido: ";
        std::cin >> apellido;
        if (!soloLetras(apellido)) std::cout << "Apellido Invalido. El apellido debe contener solo letras" << std::endl;
    } while (!soloLetras(apellido));


    do {
        std::cout << "Ingrese DNI (8 digitos): ";
        std::cin >> dni;
        if (!soloNumeros(dni) || !tienelongitud(dni, 8)) std::cout << "DNI Invalido. Debe ser 8 digitos numericos" << std::endl;
    } while (!soloNumeros(dni) || !tienelongitud(dni, 8));

    std::cout << "Ingrese fecha de nacimiento (dia mes anio): ";
    std::cin >> diaNasc >> mesNasc >> anioNasc;

    std::cout << "Ingrese correo electronico: ";
    std::cin >> correoElectronico;

    std::cout << "Ingrese direccion: ";
    std::cin.ignore();
    std::getline(std::cin, direccion);

    do {
        std::cout << "Ingrese telefono (10 digitos): ";
        std::cin >> telefono;
        if (!soloNumeros(telefono) || !tienelongitud(telefono, 10)) std::cout << "Telefono Invalido. Debe ser 10 digitos numericos" << std::endl;
    } while (!soloNumeros(telefono) || !tienelongitud(telefono, 10));

    std::cout << "Ingrese fecha de inscripcion (dia mes anio): ";
    std::cin >> diaInsc >> mesInsc >> anioInsc;

    int idAlumno = obtenerIdNuevo();


    return Alumno(
        nombre.c_str(),
        apellido.c_str(),
        dni.c_str(),
        diaNasc,
        mesNasc,
        anioNasc,
        correoElectronico.c_str(),
        direccion.c_str(),
        telefono.c_str(),
        idAlumno,
        diaInsc,
        mesInsc,
        anioInsc,
        estado
    );
}

void GestionarAlumno::altaAlumno() {
    Alumno nuevoAlumno = cargarAlumno(); // Llama a cargarAlumno para obtener un Alumno con datos

    if (archivoAlumnos.guardar(nuevoAlumno)) {
        std::cout << "Alumno agregado exitosamente.\n";
    }
    else {
        std::cout << "Error al guardar el alumno.\n";
    }
}

void GestionarAlumno::bajaAlumno() {
    int id;
    std::cout << "Ingrese el ID del alumno a dar de baja: ";
    std::cin >> id;

    int pos = archivoAlumnos.buscar(id);
    if (pos >= 0) {
        Alumno alumno = archivoAlumnos.leerRegistro(pos);
        alumno.setEstadoAlta(false);
        if (archivoAlumnos.modificarRegistro(alumno, pos)) {
            std::cout << "Alumno dado de baja exitosamente.\n";
        }
        else {
            std::cout << "Error al dar de baja al alumno.\n";
        }
    }
    else {
        std::cout << "Alumno no encontrado.\n";
    }
}

void GestionarAlumno::listarAlumnos() {
    int totalRegistros = archivoAlumnos.contarRegistros();

    if (totalRegistros == 0) {
            std::cout << "\n+------------------------------------------+\n";
            std::cout << "|       No hay alumnos registrados.        |\n";
            std::cout << "+------------------------------------------+\n";
        return;
    }

    bool seMostroAlguno = false;

    for (int i = 0; i < totalRegistros; ++i) {
        Alumno alumno = archivoAlumnos.leerRegistro(i);

        if (alumno.getEstado()) {
            if (!seMostroAlguno) {
                std::cout << "\n===== LISTA DE ALUMNOS ACTIVOS =====\n";
                seMostroAlguno = true;
            }

            alumno.mostrar();
        }
    }


    if (!seMostroAlguno) {
        std::cout << "\n+------------------------------------------+\n";
        std::cout << "|                                          |\n";
        std::cout << "|   AVISO: No se encontraron alumnos       |\n";
        std::cout << "|          activos en el sistema.          |\n";
        std::cout << "|                                          |\n";
        std::cout << "+------------------------------------------+\n";
    }

}

void GestionarAlumno::buscarAlumno() {
    int id;
    std::cout << "Ingrese el ID del alumno a buscar: ";
    std::cin >> id;

    int pos = archivoAlumnos.buscar(id);
    if (pos >= 0) {
        Alumno alumno = archivoAlumnos.leerRegistro(pos);
        alumno.mostrar();
    }
    else {
        std::cout << "Alumno no encontrado.\n";
    }
}

int GestionarAlumno::obtenerIdNuevo() {
    return Utilidades::obtenerIdNuevo<ArchivoAlumnos, Alumno>(archivoAlumnos);
}
