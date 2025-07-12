#include "Empleado.h"

// Constructor por defecto
Empleado::Empleado() : Persona()
{
    _fechaAlta = Fecha();
    strcpy(_CUIT, "no registrado");
}

//constructor
Empleado::Empleado(const string& nombre,
                   const string& apellido,
                   const string& dni,
                   const string& correoElectronico,
                   const string& telefono,
                   const string& CUIT,
                   int diaAlta, int mesAlta, int anioAlta)
    : Persona(nombre,
              apellido,
              dni,
              correoElectronico,
              telefono)
{
    _fechaAlta = Fecha(diaAlta, mesAlta, anioAlta);
    setCUIT(CUIT);
}


// Getters
const string Empleado::getCUIT() const
{
    return _CUIT;
}


Fecha Empleado::getFechaAlta() const
{
    return _fechaAlta;
}


// Setters
void Empleado::setCUIT(const std::string& cuit)
{
    strcpy(_CUIT, cuit.c_str());
}

void Empleado::setFechaAlta(int dia, int mes, int anio)
{
    _fechaAlta = Fecha(dia, mes, anio);
}

// Mostrar
void Empleado::mostrar() const
{
    mostrarPersona();
    std::cout << "CUIT: " << getCUIT() << std::endl;
    std::cout << "Fecha de alta: " << getFechaAlta().toString() << std::endl;
}

Empleado::~Empleado() {}
