#include "Inscripcion.h"
#include <iostream>

// Constructores
Inscripcion::Inscripcion()
    : _id(-1), _idAlumno(-1), _idClase(-1), _fechaInscripcion(), _estado(false) {}

Inscripcion::Inscripcion(int id, int idAlumno, int idClase, const Fecha& fecha, bool estado)
    : _id(id), _idAlumno(idAlumno), _idClase(idClase), _fechaInscripcion(fecha), _estado(estado) {}

// Getters
int Inscripcion::getId() const { return _id; }
int Inscripcion::getIdAlumno() const { return _idAlumno; }
int Inscripcion::getIdClase() const { return _idClase; }
Fecha Inscripcion::getFechaInscripcion() const { return _fechaInscripcion; }
bool Inscripcion::getEstado() const { return _estado; }

// Setters
void Inscripcion::setId(int id) { _id = id; }
void Inscripcion::setIdAlumno(int idAlumno) { _idAlumno = idAlumno; }
void Inscripcion::setIdClase(int idClase) { _idClase = idClase; }
void Inscripcion::setFechaInscripcion(const Fecha& fecha) { _fechaInscripcion = fecha; }
void Inscripcion::setEstado(bool estado) { _estado = estado; }

// Interfaz
void Inscripcion::mostrar() const {
    std::cout << "--- Inscripcion ID #" << _id << " ---" << std::endl;
    std::cout << "ID Alumno: " << _idAlumno << std::endl;
    std::cout << "ID Clase:  " << _idClase << std::endl;
    std::cout << "Fecha:     " << _fechaInscripcion.toString() << std::endl;
    std::cout << "Estado:    " << (_estado ? "Activa" : "Anulada") << std::endl;
}
