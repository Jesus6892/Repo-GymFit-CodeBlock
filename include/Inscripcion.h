#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include "Fecha.h"

class Inscripcion {
private:
    int _id;
    int _idAlumno;
    int _idClase;
    Fecha _fechaInscripcion;
    bool _estado;

public:
    // Constructores
    Inscripcion();
    Inscripcion(int id, int idAlumno, int idClase, const Fecha& fecha, bool estado = true);

    // Getters
    int getId() const;
    int getIdAlumno() const;
    int getIdClase() const;
    Fecha getFechaInscripcion() const;
    bool getEstado() const;

    // Setters
    void setId(int id);
    void setIdAlumno(int idAlumno);
    void setIdClase(int idClase);
    void setFechaInscripcion(const Fecha& fecha);
    void setEstado(bool estado);

    // Interfaz
    void mostrar() const;
};

#endif // INSCRIPCION_H 