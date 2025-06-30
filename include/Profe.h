#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "Empleado.h"

using namespace std;

class Profe : public Empleado
{
private:
    int _idProfe;

public:
    Profe();
    Profe(const string nombre, const string apellido, const string dni,
          int diaNasc, int mesNasc, int anioNasc,
          const string correoElectronico, const string direccion, const string telefono,
          const string CUIT,
          int diaAlta, int mesAlta, int anioAlta,
          const std::string& observaciones,
          int idProfe);

    // setters
    void setId(int idProfe);

    // getters
    int getId() const;

    // interfaz
    void mostrar() const;

    ~Profe();
};
