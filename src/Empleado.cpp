#include "Empleado.h"

// Constructor por defecto
Empleado::Empleado() : Persona()
{
    _fechaAlta = Fecha();
    strcpy(_CUIT, "no registrado");
}

// Constructor con parámetros
Empleado::Empleado(const string nombre, const string apellido, const string dni,
                   int diaNasc, int mesNasc, int anioNasc,
                   const string correoElectronico,
                   const string direccion,
                   const string telefono,
                   const string CUIT,
                   int diaAlta, int mesAlta, int anioAlta)
    : Persona(nombre, apellido, dni, diaNasc, mesNasc, anioNasc, correoElectronico, direccion, telefono),
      _fechaAlta(diaAlta, mesAlta, anioAlta)
{
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
void Empleado::setCUIT(const string cuit)
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
