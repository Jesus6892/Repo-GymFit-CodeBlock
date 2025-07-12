#include "Pago.h"
#include <iostream>

Pago::Pago()
    : _id(-1), _idAlumno(-1), _idActividad(-1),
      _fechaPago(""), _monto(0.0f), _estado(false) {}

Pago::Pago(int id, int idAlumno, int idActividad, const std::string& fechaPago, float monto, bool estado)
    : _id(id), _idAlumno(idAlumno), _idActividad(idActividad),
      _fechaPago(fechaPago), _monto(monto), _estado(estado) {}

int Pago::getId() const { return _id; }
int Pago::getIdAlumno() const { return _idAlumno; }
int Pago::getIdActividad() const { return _idActividad; }
std::string Pago::getFechaPago() const { return _fechaPago; }
float Pago::getMonto() const { return _monto; }
bool Pago::getEstado() const { return _estado; }

void Pago::setEstado(bool estado) {
    _estado = estado;
}

void Pago::mostrar() const {
    std::cout << "Pago [ID: " << _id
              << ", AlumnoID: " << _idAlumno
              << ", ActividadID: " << _idActividad
              << ", Fecha: " << _fechaPago
              << ", Monto: " << _monto
              << ", Estado: " << (_estado ? "Activo" : "Anulado")
              << "]" << std::endl;
}

void Pago::anular() {
    _estado = false;
}
