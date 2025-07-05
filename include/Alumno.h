#pragma once
#include <cstring>
#include "Persona.h"

class Alumno : public Persona
{
private:
    int _id;

public:
    // Constructores
    Alumno();
    Alumno(const string& nombre,
           const string& apellido,
           const string& dni,
           const string& correoElectronico,
           const string& telefono,
           int id);

    // Setter
    void setId(int id);

    // Getters
    int getId() const;

    // Interfaz
    void mostrar() const;

    // Destructor
    ~Alumno();
};
