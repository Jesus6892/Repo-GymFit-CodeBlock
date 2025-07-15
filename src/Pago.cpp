#include "Pago.h"
#include <iostream>

Pago::Pago()
    : _id(-1), _idAlumno(-1), _idActividad(-1),
      _fechaPago(1, 1, 2001), _monto(0.0f), _estado(false) {}

Pago::Pago(int id, int idAlumno, int idActividad, int dia, int mes, int anio, float monto, bool estado)
    : _id(id), _idAlumno(idAlumno), _idActividad(idActividad),_fechaPago(dia, mes, anio), _monto(monto), _estado(estado){}

int Pago::getId() const { return _id; }
int Pago::getIdAlumno() const { return _idAlumno; }
int Pago::getIdActividad() const { return _idActividad; }
std::string Pago::getFechaPago() const { return _fechaPago.toString(); }
float Pago::getMonto() const { return _monto; }
bool Pago::getEstado() const { return _estado; }

void Pago::setEstado(bool estado) {
    _estado = estado;
}

void Pago::mostrar() const {
    std::cout << "Pago [ID: " << getId()
              << ", AlumnoID: " << getIdAlumno()
              << ", ActividadID: " << getIdActividad()
              << ", Fecha: " << getFechaPago()
              << ", Monto: " << getMonto()
              << ", Estado: " << (getEstado() ? "Activo" : "Anulado")
              << "]" << std::endl;
}

void Pago::anular() {
    _estado = false;
}
