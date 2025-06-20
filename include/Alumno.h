#pragma once
#include <cstring>
#include "Persona.h"
#include "Fecha.h"

class Alumno : public Persona
{
private:
    int _idAlumno;
    Fecha _fechaInscripcion;
    bool _estado;

public:
    // Constructores
    Alumno();
    Alumno(const string nombre, const string apellido, const string dni,
           int diaNasc, int mesNasc, int anioNasc,
           const string correoElectronico,
           const string direccion,
           const string telefono,
           int idAlumno,
           int diaInsc, int mesInsc, int anioInsc,
           bool estado);

    // Setters
    void setIdAlumno(int idAlumno);
    void setFechaInscripcion(int dia, int mes, int anio);
    void setEstadoAlta(bool estado);

    // Getters
    int getId() const;
    Fecha getFechaInscripcion() const;
    bool getEstado() const;

    // Interfaz
    void mostrar() const;

    // Destructor
    ~Alumno();
};
