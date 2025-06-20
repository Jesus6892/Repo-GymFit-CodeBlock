#include "Alumno.h"
#include <iostream>
#include <stdexcept>

// constructores
Alumno::Alumno() : Persona()
{
    _idAlumno = -1;
    _fechaInscripcion = Fecha(1, 1, 1);
    _estado = false;
}

Alumno::Alumno(const string nombre, const string apellido, const string dni,
               int diaNasc, int mesNasc, int anioNasc,
               const string correoElectronico,
               const string direccion,
               const string telefono,
               int idAlumno,
               int diaInsc, int mesInsc, int anioInsc,
               bool estado)
    : Persona(nombre, apellido, dni, diaNasc, mesNasc, anioNasc, correoElectronico, direccion, telefono),
      _idAlumno(idAlumno),
      _fechaInscripcion(diaInsc, mesInsc, anioInsc),
      _estado(estado)
{
    if (idAlumno <= 0)
        throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
}

// setters
void Alumno::setIdAlumno(int idAlumno)
{
    if (idAlumno <= 0)
        throw std::invalid_argument("El ID del Alumno debe ser un número positivo");
    _idAlumno = idAlumno;
}

void Alumno::setFechaInscripcion(int dia, int mes, int anio)
{
    _fechaInscripcion = Fecha(dia, mes, anio);
}

void Alumno::setEstadoAlta(bool estado)
{
    _estado = estado;
}

// getters
int Alumno::getId() const
{
    return _idAlumno;
}

Fecha Alumno::getFechaInscripcion() const
{
    return _fechaInscripcion;
}

bool Alumno::getEstado() const
{
    return _estado;
}

// mostrar
void Alumno::mostrar() const
{
    if (_estado)
    {
        std::cout << "------------ ALUMNO: " << getId() << " ------------" << std::endl;
        Persona::mostrarPersona();
        std::cout << "ID ALUMNO: " << getId() << std::endl;
        std::cout << "FECHA DE INSCRIPCIÓN: " << getFechaInscripcion() << std::endl;
        std::string infoEstado = getEstado() ? "ACTIVO" : "INACTIVO";
        std::cout << "Estado regular: " << infoEstado << std::endl;
        std::cout << std::endl;
    }
}

// destructor
Alumno::~Alumno() {}
