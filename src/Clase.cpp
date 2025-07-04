#include "Clase.h"

// Constructor por defecto
Clase::Clase() {
    _id = 0;
    _idHorario = 0;
    _idActividad = 0;
    _idProfe = 0;
    _estado = true;
}

// Constructor con parmetros
Clase::Clase(const int id,
             const int idHorario,
             const int idActividad,
             const int idProfe,
             const bool estado) {
    _id = id;
    _idHorario = idHorario;
    _idActividad = idActividad;
    _idProfe = idProfe;
    _estado = estado;
}

// Setters
void Clase::setEstado(const bool estado) {
    _estado = estado;
}

void Clase::setId(int id) {
    _id = id;
}

void Clase::setIdHorario(int idHorario) {
    _idHorario = idHorario;
}

void Clase::setIdActividad(int idActividad) {
    _idActividad = idActividad;
}

void Clase::setIdProfe(int idProfe) {
    _idProfe = idProfe;
}

// Getters
bool Clase::getEstado() const {
    return _estado;
}

int Clase::getId() const {
    return _id;
}

int Clase::getIdHorario() const {
    return _idHorario;
}

int Clase::getIdActividad() const {
    return _idActividad;
}

int Clase::getIdProfe() const {
    return _idProfe;
}
