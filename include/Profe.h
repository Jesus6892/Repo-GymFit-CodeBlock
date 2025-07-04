#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "Empleado.h"

using namespace std;

class Profe : public Empleado
{
private:
    int _id;

public:
    Profe();
    Profe(const string nombre, const string apellido, const string dni,
          int diaNasc, int mesNasc, int anioNasc,
          const string correoElectronico, const string direccion, const string telefono,
          const string CUIT,
          int diaAlta, int mesAlta, int anioAlta,
          const std::string& observaciones,
          int id);

    // setter
    void setId(int id);

    // getter
    int getId() const;

    // interfaz
    void mostrar() const;

    ~Profe();
};
