#include "Alumno.h"
#include <iostream>
#include <stdexcept>

// Constructores
Alumno::Alumno()
    : Persona(), _id(-1)
{
}

// Constructor parametrizado
Alumno::Alumno(const string& nombre,
               const string& apellido,
               const string& dni,
               const string& correoElectronico,
               const string& direccion,
               const string& telefono,
               int id)
    : Persona(nombre, apellido, dni,
              correoElectronico, direccion, telefono),
      _id(id)
{
    if (id <= 0)
        throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
}

// Setters
void Alumno::setId(int id)
{
    if (id <= 0)
        throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
    _id = id;
}

// Getters
int Alumno::getId() const
{
    return _id;
}

// Mostrar
void Alumno::mostrar() const
{
    std::cout << "------------------------" << std::endl;
    Persona::mostrarPersona();
    std::cout << "ID Alumno: " << getId() << std::endl;
    std::cout << std::endl;
}

// Destructor
Alumno::~Alumno() {}
