#include "Clase.h"

// Constructor por defecto
Clase::Clase() {
    _idClase = 0;
    _idHorario = 0;
    _idProfe = 0;
    _estado = true;
}

// Constructor con parámetros
Clase::Clase(const int idClase,
             const int idHorario,
             const int idProfe,
             const bool estado) {
    _idClase = idClase;
    _idHorario = idHorario;
    _idProfe = idProfe;
    _estado = estado;
}

// Setters
void Clase::setEstado(const bool estado) {
    _estado = estado;
}

void Clase::setIdClase(int idClase) {
    _idClase = idClase;
}

void Clase::setIdHorario(int idHorario) {
    _idHorario = idHorario;
}

void Clase::setIdProfe(int idProfe) {
    _idProfe = idProfe;
}

// Getters
bool Clase::getEstado() const {
    return _estado;
}

int Clase::getIdClase() const {
    return _idClase;
}

int Clase::getIdHorario() const {
    return _idHorario;
}

int Clase::getIdProfe() const {
    return _idProfe;
}
