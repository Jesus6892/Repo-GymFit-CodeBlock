#pragma once
#include "Persona.h"
#include "Fecha.h"
#include <cstring>
#include <string>
#include <iostream>


class Empleado : public Persona {
private:
    char _CUIT[15];
    Fecha _fechaAlta;

public:
    Empleado();
    Empleado(const string nombre, const string apellido, const string dni,
             int diaNasc, int mesNasc, int anioNasc,
             const string correoElectronico,
             const string direccion,
             const string telefono,
             const string CUIT,
             int diaAlta, int mesAlta, int anioAlta);

    // Getters
    const string getCUIT() const;
    Fecha getFechaAlta() const;

    // Setters
    void setCUIT(const string cuit);
    void setFechaAlta(int dia, int mes, int anio);

    // Mostrar
    void mostrar() const;

    ~Empleado();
};
