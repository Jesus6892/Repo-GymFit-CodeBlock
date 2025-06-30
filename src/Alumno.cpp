#include "Alumno.h"
#include <iostream>
#include <stdexcept>

// constructores
Alumno::Alumno() : Persona()
{
    _idAlumno = -1;
}

Alumno::Alumno(const string& nombre,
               const string& apellido,
               const string& dni,
               int diaNasc,
               int mesNasc,
               int anioNasc,
               const string& correoElectronico,
               const string& direccion,
               const string& telefono,
               int idAlumno,
               int diaInsc,
               int mesInsc,
               int anioInsc)
    : Persona(nombre, apellido, dni, diaNasc, mesNasc, anioNasc,
              correoElectronico, direccion, telefono)
{
    if (idAlumno <= 0) throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
    else _idAlumno = idAlumno;
}
// setters
void Alumno::setIdAlumno(int idAlumno)
{
    if (idAlumno <= 0) throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
    else _idAlumno = idAlumno;
}

// getters
int Alumno::getId() const
{
    return _idAlumno;
}

// mostrar
void Alumno::mostrar() const
{
        std::cout << "------------------------" << std::endl;
        Persona::mostrarPersona();
        std::cout << "ID ALUMNO: " << getId() << std::endl;
        std::cout << std::endl;
}

// destructor
Alumno::~Alumno() {}
